/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifdef MSVC
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <fstream>      // ofstream, ofstream::open(), ofstream::close()
                        // ifstream, ifstream::open(), ifstream::close()

#include "enableTracingIfDesired.h"
#ifdef TRACING_IS_ENABLED
  #include "traceOah.h"
#endif

#include "oahOah.h"

#include "msrOah.h"
#include "msr2msrOah.h"
#include "mxmlTreeOah.h"

#include "waeExceptions.h"
#include "waeMessagesHandling.h"

#include "msdlParser.h"

#include "msdl2gmnInsiderHandler.h"
#include "msdl2gmnRegularHandler.h"

#include "msr2msrInterface.h"
#include "msr2mxmlTreeInterface.h"
#include "mxmlTree2guidoTranlatorInterface.h"

#include "msdl2guido.h"


using namespace std;

namespace MusicXML2
{
/*
  ENFORCE_TRACE_OAH can be used to issue trace messages
  before gGlobalOahOahGroup->fTrace has been initialized
*/

//#define ENFORCE_TRACE_OAH

//_______________________________________________________________________________
xmlErr msdlStream2guidoWithHandler (
  string        inputSourceName,
  istream&      inputStream,
  S_oahHandler  handler,
  std::ostream& out,
  std::ostream& err)
{
  // has quiet mode been requested?
  // ------------------------------------------------------

  if (gGlobalGeneralOahGroup->getQuiet ()) {
    // disable all trace and display options
    handler->
      enforceHandlerQuietness ();
  }

  // the first MSR score
  // ------------------------------------------------------

  S_msrScore firstMsrScore;

  // translating the MSDL input into a first MSR (pass 1)
  // ------------------------------------------------------

  try {
    // start the clock
    clock_t startClock = clock ();

#ifdef TRACING_IS_ENABLED
    if (gGlobalTraceOahGroup->getTracePasses ()) {
      string separator =
        "%--------------------------------------------------------------";
      cerr <<
        endl <<
        separator <<
        endl <<
        gTab <<
        "Pass 1: Creating a first MSR from the MSDL input" <<
        endl <<
        separator <<
        endl;
    }
#endif

    // create the MSDL parser
    msdlParser
      parser (
        inputSourceName,
        inputStream);

    // parse the input
    parser.parse ();

    // get the resulting score
    // JMI an msrBook should also be handled
    firstMsrScore = parser.getCurrentScore ();

    // register time spent
    clock_t endClock = clock ();

    timing::gGlobalTiming.appendTimingItem (
      "Pass 1",
      "Create the MSR score from the MSDL input",
      timingItem::kMandatory,
      startClock,
      endClock);

    // sanity check
    if (! firstMsrScore) {
      stringstream s;

      s <<
        "Could not perform comversion of \"" <<
        inputSourceName <<
        "\" to MSR, quitting";

      string message = s.str ();

      err <<
        message <<
        endl;

      throw msgMsdlToMsrScoreException (message);
    }
  }
  catch (msgMsdlToMsrScoreException& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }
  catch (std::exception& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }

  // should we return now?
  // ------------------------------------------------------

  if (gGlobalMsdl2gmnInsiderOahGroup->getQuitAfterPass2a ()) {
    err <<
      endl <<
      "Quitting after pass 2a as requested" <<
      endl;

    return kNoErr;
  }

  // convert the first MSR into a second MSR (pass 2)
  // ------------------------------------------------------

  S_msrScore secondMsrScore;

  try {
    secondMsrScore =
      convertMsrScoreToMsrScore (
        firstMsrScore,
        gGlobalMsrOahGroup,
        gGlobalMsr2msrOahGroup,
        "Pass 2",
        "Convert the first MSR into a second MSR");
  }
  catch (msgMxmlTreeToMsrException& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }
  catch (std::exception& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }

  // convert the second MSR into a second mxmlTree (pass 3)
  // ------------------------------------------------------

  Sxmlelement secondMxmlTree;

  try {
    secondMxmlTree =
      convertMsrScoreToMxmltree (
        secondMsrScore,
        gGlobalMsrOahGroup,
        "Pass 3",
        "Convert the second MSR into an mxmlTree",
        timingItem::kMandatory);
  }
  catch (msgMxmlTreeToMsrException& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }
  catch (std::exception& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }

  // generate Guido from the second mxmlTree (pass 4)
  // ------------------------------------------------------

  string
    outputFileName =
      handler->
        fetchOutputFileNameFromTheOptions ();

  try {
    generateGuidoFromMxmlTree (
      secondMxmlTree,
      outputFileName,
      err,
      "Pass 4",
      "Convert  the mxmlTree into Guido text");
  }
  catch (msgMxmlTreeToMsrException& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }
  catch (std::exception& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }

  return kNoErr;
}

//_______________________________________________________________________________
xmlErr msdlStream2guidoWithOptionsVector (
  string               inputSourceName,
  istream&             inputStream,
  const optionsVector& options,
  std::ostream&        out,
  std::ostream&        err)
{
  // the fake executable name
  // ------------------------------------------------------

  string fakeExecutableName = "msdl2gmn";

  // reset the global indenter
  // ------------------------------------------------------

  gIndenter.resetToZero ();

  // create the global log indented output stream
  // ------------------------------------------------------

  createTheGlobalIndentedOstreams (out, err);

	// print the options vector
#ifdef TRACING_IS_ENABLED
#ifdef ENFORCE_TRACE_OAH
      displayOptionsVector (options, err);
#endif
#endif

  // are there 'insider' and/or 'regular' options present?
  // ------------------------------------------------------

  bool insiderOptions = false;
  bool regularOptions = false;

	for (unsigned int i = 1; i < options.size (); ++i) {
	  string optionName = options [i].first;

		if (optionName == K_INSIDER_OPTION_NAME) {
		  insiderOptions = true;
		}
		if (optionName == K_REGULAR_OPTION_NAME) {
		  regularOptions = true;
		}
	} // for

#ifdef TRACING_IS_ENABLED
#ifdef ENFORCE_TRACE_OAH
  gLogStream <<
    "msdlStream2guido()" <<
    ", insiderOptions: " << booleanAsString (insiderOptions) <<
    ", regularOptions: " << booleanAsString (regularOptions) <<
    endl;
#endif
#endif

  if (insiderOptions && regularOptions) {
    stringstream s;

    s <<
      "options '-insider' and '-regular' cannot be used together";

    oahError (s.str ());
  }

  // here, at most one of insiderOptions and regularOptions is true

  // create an msdl2gmn insider OAH handler
  // ------------------------------------------------------

  // create an insider msdl2gmn OAH handler
  S_msdl2gmnInsiderHandler
    insiderOahHandler =
      msdl2gmnInsiderHandler::create (
        fakeExecutableName,
        fakeExecutableName + " insider OAH handler with options vector");

  // the OAH handler to be used, a regular handler is the default
  // ------------------------------------------------------

  S_oahHandler handler;

  if (insiderOptions) {
    // use the insider msdl2gmn OAH handler
    handler = insiderOahHandler;
  }
  else {
    // create a regular msdl2gmn OAH handler
    handler =
      msdl2gmnRegularHandler::create (
        fakeExecutableName,
        fakeExecutableName + " regular OAH handler",
        insiderOahHandler);
  }

  // handle the command line options and arguments
  // ------------------------------------------------------

  try {
    // handle the options from the options vector
    oahElementHelpOnlyKind
      helpOnlyKind =
        handler->
          handleOptionsFromOptionsVector (
            fakeExecutableName,
            options);

    // have help options been used?
    switch (helpOnlyKind) {
      case oahElementHelpOnlyKind::kElementHelpOnlyYes:
        return kNoErr; // quit now
        break;
      case oahElementHelpOnlyKind::kElementHelpOnlyNo:
        // go ahead
        break;
    } // switch
  }
  catch (msgOahException& e) {
    displayException (e, gOutputStream);
    return kInvalidOption;
  }
  catch (std::exception& e) {
    displayException (e, gOutputStream);
    return kInvalidFile;
  }

  // check indentation
  if (gIndenter != 0) {
    gLogStream <<
      "### " <<
      fakeExecutableName <<
      " gIndenter value after options ands arguments checking: " <<
      gIndenter.getIndent () <<
      " ###" <<
      endl;

    gIndenter.resetToZero ();
  }

  // do the job
  // ------------------------------------------------------

  msdlStream2guidoWithHandler (
    inputSourceName,
    inputStream,
    handler,
    out,
    err);

  return kNoErr;
}

//_______________________________________________________________________________
EXP xmlErr msdlfile2guidoWithOptionsVector (
  string               fileName,
  const optionsVector& options,
  std::ostream&        out,
  std::ostream&        err)
{
  // open input file
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTracePasses ()) {
    err <<
      "Opening file \"" << fileName << "\" for writing" <<
      endl;
  }
#endif

  ifstream
    inputStream (
      fileName.c_str (),
      ifstream::in);

  if (! inputStream.is_open ()) {
    stringstream s;

    s <<
      "Could not open MSDL input file \"" <<
      fileName <<
      "\" for reading, quitting";

    string message = s.str ();

    err <<
      message <<
      endl;

    throw msgMsdlToGuidoException (message);
  }

  return
    msdlStream2guidoWithOptionsVector (
      fileName, inputStream, options, out, err);
}

xmlErr msdlFile2guidoWithHandler (
  string        fileName,
  S_oahHandler  handler,
  std::ostream& out,
  std::ostream& err)
{
  // open input file
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTracePasses ()) {
    err <<
      "Opening file \"" << fileName << "\" for writing" <<
      endl;
  }
#endif

  ifstream
    inputStream (
      fileName.c_str (),
      ifstream::in);

  if (! inputStream.is_open ()) {
    stringstream s;

    s <<
      "Could not open MSDL input file \"" <<
      fileName <<
      "\" for reading, quitting";

    string message = s.str ();

    err <<
      message <<
      endl;

    throw msgMsdlToGuidoException (message);
  }

  return
    msdlStream2guidoWithHandler (
      fileName, inputStream, handler, out, err);
}

//_______________________________________________________________________________
EXP xmlErr msdlstring2guidoWithOptionsVector (
  const char *         buffer,
  const optionsVector& options,
  std::ostream&        out,
  std::ostream&        err)
{
  stringstream
    inputStream (
      buffer,
      ios_base::in);

	// call msdlStream2guidoWithOptionsVector() even if buffer is empty,
	// to handle the help options if any
  return
    msdlStream2guidoWithOptionsVector (
      "buffer", inputStream, options, out, err);

	return kInvalidFile;
}

xmlErr msdlString2guidoWithHandler (
  const char *  buffer,
  S_oahHandler  handler,
  std::ostream& out,
  std::ostream& err)
{
  stringstream
    inputStream (
      buffer,
      ios_base::in);

	// call msdlStream2guidoWithOptionsVector() even if buffer is empty,
	// to handle the help options if any
  return
    msdlStream2guidoWithHandler (
      "buffer", inputStream, handler, out, err);

	return kInvalidFile;
}


}