/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <iomanip>      // setw, setprecision, ...

#include "enableExtraOahIfDesired.h"

#include "enableTracingIfDesired.h"
#ifdef TRACING_IS_ENABLED
  #include "traceOah.h"
#endif

#include "oahOah.h"

#include "generalOah.h"
#include "outputFileOah.h"
#include "extraOah.h"


// MSDL
#include "msdl.h"

#include "msdlInputOah.h"
#include "msdl2msrOah.h"


// MSR
#include "msrOah.h"
#include "msr2msrOah.h"


// Guido
#include "xml2gmnInsiderHandler.h"

#include "msdl2gmnInsiderHandler.h"


// MusicXML
#include "mxmlTreeOah.h"
#include "mxmlTreeOah.h"
#include "mxmltreeGenerationOah.h"
#include "mxmlTree2msrOah.h"

#include "msdl2xmlInsiderHandler.h"


// Lilypond
#include "lpsr.h"

#include "msr2lpsrOah.h"
#include "lpsrOah.h"
#include "lilypondGenerationOah.h"

#include "msdl2lyInsiderHandler.h"


// Braille music
#include "bsr.h"

#include "msr2bsrOah.h"
#include "bsrOah.h"
#include "brailleGenerationOah.h"

#include "msdl2brlInsiderHandler.h"


// generation
#include "msrGenerationOah.h"
#include "guidoGenerationOah.h"

#include "version.h"

#include "msdlCompilerInsiderHandler.h"


using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
S_msdlCompilerInsiderHandler msdlCompilerInsiderHandler::create (
  const string&            executableName,
  const string&            handlerHeader,
  multiGeneratorOutputKind generatorOutputKind)
{
  // create the insider handler
  msdlCompilerInsiderHandler* o = new
    msdlCompilerInsiderHandler (
      executableName,
      handlerHeader,
      generatorOutputKind);
  assert (o != nullptr);

  return o;
}

msdlCompilerInsiderHandler::msdlCompilerInsiderHandler (
  const string&            executableName,
  const string&            handlerHeader,
  multiGeneratorOutputKind generatorOutputKind)
  : oahInsiderHandler (
      executableName,
      handlerHeader,
R"(                Welcome to the MSDL compiler,
     a generator of Guido, MusicXML, LilyPond or braille music
          delivered as part of the libmusicxml2 library.
      https://github.com/grame-cncm/libmusicxml/tree/lilypond
)",
    usageInformation (
      generatorOutputKind)),
    fGeneratorOutputKind (
      generatorOutputKind)
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream <<
      "Initializing \"" <<
      fHandlerHeader <<
      "\" regular options handler" <<
      endl;
  }
#endif

  // create the msdlCompiler prefixes
  createTheMsdlCompilerPrefixes ();

  // create the msdlCompiler option groups
  createTheMsdlCompilerOptionGroups (
    executableName,
    generatorOutputKind);
}

msdlCompilerInsiderHandler::~msdlCompilerInsiderHandler ()
{}

string msdlCompilerInsiderHandler::usageInformation (
  multiGeneratorOutputKind generatorOutputKind)
{
  stringstream s;

  s <<
R"(Usage: msdl [option]*
)" <<
    endl;

  switch (generatorOutputKind) {
    case multiGeneratorOutputKind::k_NoOutput:
      s <<
        "The help below is available whichever output is produced";
      break;

    default:
      s <<
        "The help below is available when generating " <<
        multiGeneratorOutputKindAsString (generatorOutputKind) <<
        " output";
  } // switch

  return s.str ();
}

void msdlCompilerInsiderHandler::handlerOahError (
  const string& errorMessage)
{
  stringstream s;

  s <<
    errorMessage  <<
    " when generating " <<
    multiGeneratorOutputKindAsString (fGeneratorOutputKind) <<
    " output";

  oahError (s.str ());
}

string msdlCompilerInsiderHandler::handlerExecutableAboutInformation () const
{
  return
    msdlCompilerAboutInformation (
      fGeneratorOutputKind);
}

string msdlCompilerInsiderHandler::msdlCompilerAboutInformation (
  multiGeneratorOutputKind generatorOutputKind) const
{
  string result;

  unsigned int passesNumber = 0;

  switch (generatorOutputKind) {
    case multiGeneratorOutputKind::k_NoOutput:
      // should not occur
      break;

    case multiGeneratorOutputKind::kGuidoOutput:
      passesNumber = 4;
      break;

    case multiGeneratorOutputKind::kLilyPondOutput:
      passesNumber = 3;
      break;

    case multiGeneratorOutputKind::kBrailleOutput:
      passesNumber = 4;
      break;

    case multiGeneratorOutputKind::kMusicXMLOutput:
      passesNumber = 4;
      break;

    case multiGeneratorOutputKind::kMidiOutput:
      passesNumber = 0;
      break;
  } // switch

  string headPart;

  switch (generatorOutputKind) {
    case multiGeneratorOutputKind::k_NoOutput:
      // should only occur if the run is a pure help one
      {
        stringstream headPartStream;

        headPartStream <<
R"(What msdlCompiler does:

    This multi-pass compiler performs various passes depending on the output generated)";

        headPart = headPartStream.str ();
      }
      break;

    default:
      {
        stringstream headPartStream;

        headPartStream <<
R"(What msdlCompiler does:

    This multi-pass compiler basically performs )" <<
          passesNumber <<
          " passes when generating " <<
          multiGeneratorOutputKindAsString (generatorOutputKind) <<
          " output:" <<
          endl <<
R"(
        Pass 1:  converts the MSDL input into a first MSR)";

        headPart = headPartStream.str ();
      }
  } // switch

  string specificPart;

  switch (generatorOutputKind) {
    case multiGeneratorOutputKind::k_NoOutput:
      // should not occur, unless the run is a pure help one
      break;

    case multiGeneratorOutputKind::kGuidoOutput:
      specificPart =
R"(
        Pass 2:  converts the first MSR into a second MSR;
        Pass 3:  converts the second MSR into an MusicXML tree;
        Pass 4:  converts the MusicXML tree to Guido code
                 and writes it to standard output.)";
      break;

    case multiGeneratorOutputKind::kLilyPondOutput:
      specificPart =
R"(
        Pass 2:  converts the first MSR into a second MSR;
        Pass 3:  converts the second MSR into a
                 LilyPond Score Representation (LPSR);
        Pass 4:  converts the LPSR to LilyPond code
                 and writes it to standard output.)";
      break;

    case multiGeneratorOutputKind::kBrailleOutput:
      specificPart =
R"(
        Pass 2:  converts the first MSR into a second MSR;
        Pass 3a: converts the second MSR into a
                 Braille Score Representation (BSR)
                 containing one Braille page per MusicXML page;
        Pass 3b: converts the BSRinto another BSR
                 with as many Braille pages as needed
                 to fit the line and page lengthes;
        Pass 4:  converts the BSR to braille music text
                 and writes it to standard output.)

    In this preliminary version, pass 2b merely clones the BSR it receives.)";
      break;

    case multiGeneratorOutputKind::kMusicXMLOutput:
      specificPart =
R"(
        Pass 2:  converts the first MSR into a second MSR;
        Pass 3:  converts the second MSR into an MusicXML tree;
        Pass 4:  converts the MusicXML tree to MusicXML code
                 and writes it to standard output.)";
      break;

    case multiGeneratorOutputKind::kMidiOutput:
      break;
  } // switch

   string commonTailPart =
R"(

    Other passes are performed according to the options, such as
    printing views of the internal data or printing a summary of the score.

    The activity log and warning/error messages go to standard error.)";

 return
   headPart + specificPart + commonTailPart;
}

//______________________________________________________________________________
void msdlCompilerInsiderHandler::createTheMsdlCompilerPrefixes ()
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream <<
      "Creating the msdlCompiler prefixes in \"" <<
      fHandlerHeader <<
      "\"" <<
      endl;
  }
#endif

  createTheCommonPrefixes ();
}

//______________________________________________________________________________
void msdlCompilerInsiderHandler::createTheMsdlCompilerOptionGroups (
  const string&       executableName,
  multiGeneratorOutputKind multiGeneratorOutputKind)
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream <<
      "Creating the prefixes in \"" <<
      fHandlerHeader <<
      "\" insider option groups" <<
      endl;
  }
#endif

  // initialize options handling, phase 1
  // ------------------------------------------------------

#ifdef TRACING_IS_ENABLED
  // create the trace OAH group
  appendGroupToHandler (
    createGlobalTraceOahGroup (
      this));
#endif

  // create the OAH OAH group
  appendGroupToHandler (
    createGlobalOahOahGroup (
      executableName));

  // create the general OAH group
  appendGroupToHandler (
    createGlobalGeneralOahGroup ());

  // create the MSR generator OAH group
  appendGroupToHandler (
    createGlobalMsrGeneratorsOahGroup ());

  // create the output file OAH group
  appendGroupToHandler (
    createGlobalOutputFileOahGroup ());

  // initialize the library
  // ------------------------------------------------------

  initializeMSR (); // used whatever the output kind

  initializeMSDL (); // used whatever the output kind

  // initialize options handling, phase 2
  // ------------------------------------------------------

  // create the MSDR OAH group
  appendGroupToHandler (
    createGlobalMsdlInputOahGroup (
      executableName));

  // create the multi generator OAH group
  appendGroupToHandler (
    createGlobalMultiGeneratorOahGroup ());

  // create the msdlCompiler OAH group
  appendGroupToHandler (
    createGlobalMsdlCompilerOahGroup ());

  // create the msdlCompiler insider OAH group
  appendGroupToHandler (
    createGlobalmsdlCompilerInsiderOahGroup ());

  // create the msdl2msr OAH group
  appendGroupToHandler (
    createGlobalMsdl2msrOahGroup ());

  // create the MSR OAH group
  appendGroupToHandler (
    createGlobalMsrOahGroup ());

  // create the msr2msr OAH group
  appendGroupToHandler (
    createGlobalMsr2msrOahGroup ());

  // create the groups needed according to the generated output kind
  /*
    CAUTION:
      some option names are identical in OAH groups
      that are not meant to be used at the same time,
      such as gGlobalMsr2msrOahGroup and gGlobalMsr2lpsrOahGroup
  */

  switch (multiGeneratorOutputKind) {
    case multiGeneratorOutputKind::k_NoOutput:
      // should not occur, unless the run is a pure help one
      break;

    case multiGeneratorOutputKind::kGuidoOutput:
      // create the msr2mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMxmltreeGenerationOahGroup ());

      // create the mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMxmlTreeOahGroup ());

      // create the xml2gmn OAH group
      appendGroupToHandler (
        createGlobalXml2gmnOahGroup ());

      // create the Guido generators OAH group
      appendGroupToHandler (
        createGlobalGuidoGenerationOahGroup ());

      // create the msdl2gmn OAH group
      appendGroupToHandler (
        createGlobalMsdl2gmnInsiderOahGroup ());
      break;

    case multiGeneratorOutputKind::kLilyPondOutput:
      // initialize the library
      initializeLPSR ();

      // create the msr2lpsr OAH group
      appendGroupToHandler (
        createGlobalMsr2lpsrOahGroup ());

      // create the LPSR OAH group
      appendGroupToHandler (
        createGlobalLpsrOahGroup ());

      // create the LilyPond generation OAH group
      appendGroupToHandler (
        createGlobalLilypondGenerationOahGroup ());

      // create the msdl2ly OAH group
      appendGroupToHandler (
        createGlobalMsdl2lyInsiderOahGroup ());

      break;

    case multiGeneratorOutputKind::kBrailleOutput:
      // initialize the library
      initializeBSR ();

      // create the msr2bsr OAH group
      appendGroupToHandler (
        createGlobalMsr2bsrOahGroup ());

      // create the BSR OAH group
      appendGroupToHandler (
        createGlobalBsrOahGroup ());

      // create the braille generation OAH group
      appendGroupToHandler (
        createGlobalBrailleGenerationOahGroup ());

      // create the msdl2brl OAH group
      appendGroupToHandler (
        createGlobalMsdl2brlOahGroup (
          executableName,
          fHandlerHeader));
      break;

    case multiGeneratorOutputKind::kMusicXMLOutput:
      // create the msr2mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMxmltreeGenerationOahGroup ());

      // create the mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMxmlTreeOahGroup ());

      // create the msdl2xml OAH group
      appendGroupToHandler (
        createGlobalMsdl2xmlOahGroup ());
      break;

    case multiGeneratorOutputKind::kMidiOutput:
      break;
  } // switch

#ifdef EXTRA_OAH_IS_ENABLED
  // create the extra OAH group
  appendGroupToHandler (
    createGlobalExtraOahGroup ());
#endif
}

//______________________________________________________________________________
void msdlCompilerInsiderHandler::checkOptionsAndArgumentsFromArgcAndArgv () const
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream <<
      "checking options and arguments from argc/argv in \"" <<
      fHandlerHeader <<
      "\"" <<
      endl;
  }
#endif

  if (MSDR_STANDARD_INPUT_NAME == string ("-")) {
    checkSingleInputSourceInArgumentsVector ();
  }
  else if (MSDR_STANDARD_INPUT_NAME == string ("")) {
    checkNoOrOneInputSourceInArgumentsVector ();
  }
  else {
    oahInternalError (
      "MSDR_STANDARD_INPUT_NAME should be empty or contain a single '-'");
  }
}

//______________________________________________________________________________
string msdlCompilerInsiderHandler::fetchOutputFileNameFromTheOptions () const
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream <<
      "Fetching the output file name from the options in OAH handler \"" <<
      fHandlerHeader <<
      "\"" <<
      endl;
  }
#endif

  S_oahStringAtom
    outputFileNameStringAtom =
      gGlobalOutputFileOahGroup->
        getOutputFileNameStringAtom ();

  S_oahBooleanAtom
    autoOutputFileNameAtom =
      gGlobalOutputFileOahGroup->
        getAutoOutputFileNameAtom ();

  bool
    outputFileNameHasBeenSet =
      outputFileNameStringAtom->
        getVariableHasBeenSet ();

  bool
    autoOutputFileNameHasBeenSet =
      autoOutputFileNameAtom->
        getVariableHasBeenSet ();

#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream <<
      "msdlCompilerInsiderHandler::fetchOutputFileNameFromTheOptions()" <<
      " outputFileNameHasBeenSet: " <<
      booleanAsString (outputFileNameHasBeenSet) <<
      " autoOutputFileNameHasBeenSet: " <<
      booleanAsString (autoOutputFileNameHasBeenSet) <<
      endl;
  }
#endif

  string
    inputSourceName =
      gGlobalOahOahGroup->getInputSourceName ();

  string outputFileName;

  if (outputFileNameHasBeenSet) {
    if (autoOutputFileNameHasBeenSet) {
      // '-o, -output-file-name' has been chosen
      // '-aofn, -auto-output-file-name' has been chosen
      stringstream s;

      s <<
        "options' " <<
        outputFileNameStringAtom->fetchNames () <<
        "' and '" <<
        autoOutputFileNameAtom->fetchNames () <<
        "' cannot be chosen simultaneously" <<
        "\")";

      oahError (s.str ());
    }
    else {
      // '-o, -output-file-name' has been chosen
      // '-aofn, -auto-output-file-name' has NOT been chosen
      outputFileName =
        outputFileNameStringAtom->
          getStringVariable ();
    }
  }

  else {
    if (autoOutputFileNameHasBeenSet) {
      // '-o, -output-file-name' has NOT been chosen
      // '-aofn, -auto-output-file-name' has been chosen
      // determine output file base name
      if (inputSourceName == "-") {
        outputFileName = "stdin";
      }

      else {
        // determine output file name,
        outputFileName =
          baseName (inputSourceName);

        size_t
          posInString =
            outputFileName.rfind ('.');

        // remove file extension
        if (posInString != string::npos) {
          outputFileName.replace (
            posInString,
            outputFileName.size () - posInString,
            "");
        }
      }

#ifdef TRACING_IS_ENABLED
      if (getTraceOah ()) {
        gLogStream <<
          "msdlCompilerInsiderHandler::fetchOutputFileNameFromTheOptions(): outputFileName 1 = \"" <<
          outputFileName <<
          "\"" <<
          endl;
      }
#endif

#ifdef TRACING_IS_ENABLED
      if (getTraceOah ()) {
        gLogStream <<
          "msdlCompilerInsiderHandler::fetchOutputFileNameFromTheOptions(): outputFileName 2 = " <<
          outputFileName <<
          "\"" <<
          endl;
      }
#endif
    }

    else {
      // '-o, -output-file-name' has NOT been chosen
      // '-aofn, -auto-output-file-name' has NOT been chosen
      outputFileName = inputSourceName; // will augmented below
    }
  }

  // complement the output file name if relevant,
  // and add the output file name suffix
  if (! outputFileNameHasBeenSet) {
    switch (fGeneratorOutputKind) {
      case multiGeneratorOutputKind::k_NoOutput:
        // should not occur
        outputFileName = "___k_NoOutput___";
        break;

      case multiGeneratorOutputKind::kGuidoOutput:
        outputFileName += ".gmn";
        break;

      case multiGeneratorOutputKind::kLilyPondOutput:
        outputFileName += ".ly";
        break;

      case multiGeneratorOutputKind::kBrailleOutput:
        {
          S_oahStringAtom
            outputFileNameStringAtom =
              gGlobalOutputFileOahGroup->
                getOutputFileNameStringAtom ();

          // should encoding be used by the output file name?
          bsrBrailleOutputKind
            brailleOutputKind =
              gGlobalBrailleGenerationOahGroup->
                getBrailleOutputKind ();

          if (gGlobalBrailleGenerationOahGroup->getUseEncodingInFileName ()) {
            switch (brailleOutputKind) {
              case bsrBrailleOutputKind::kBrailleOutputAscii:
                outputFileName += "_ASCII";
                break;

              case bsrBrailleOutputKind::kBrailleOutputUTF8:
                outputFileName += "_UTF8";
                  /* JMI
                switch (gGlobalBrailleGenerationOahGroup->getByteOrderingKind ()) {
                  case kByteOrderingNone:
                    break;
                  case kByteOrderingBigEndian:
                    outputFileName += "_BE";
                    break;
                  case kByteOrderingSmallEndian:
                    // should not occur JMI
                    break;
                } // switch
                */
                break;

              case bsrBrailleOutputKind::kBrailleOutputUTF8Debug:
                outputFileName += "_UTF8Debug";
                break;

              case bsrBrailleOutputKind::kBrailleOutputUTF16:
                outputFileName += "_UTF16";
                switch (gGlobalBrailleGenerationOahGroup->getByteOrderingKind ()) {
                  case kByteOrderingNone:
                    break;

                  case kByteOrderingBigEndian:
                    outputFileName += "_BE";
                    break;

                  case kByteOrderingSmallEndian:
                    outputFileName += "_SE";
                    break;
                } // switch
                break;
            } // switch
          }

          outputFileName += ".brf";
        }
        break;

      case multiGeneratorOutputKind::kMusicXMLOutput:
        outputFileName += ".xml";
        break;

      case multiGeneratorOutputKind::kMidiOutput:
        outputFileName += ".midi";
        break;
    } // switch
  }

#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream <<
      "outputFileName: " <<
      outputFileName <<
      endl;
  }
#endif

  return outputFileName;
}

//______________________________________________________________________________
void msdlCompilerInsiderHandler::checkHandlerOptionsConsistency ()
{}

//______________________________________________________________________________
void msdlCompilerInsiderHandler::enforceHandlerQuietness ()
{
#ifdef TRACING_IS_ENABLED
  gGlobalTraceOahGroup->
    enforceGroupQuietness ();
#endif

  gGlobalmsdlCompilerInsiderOahGroup->
    enforceGroupQuietness ();

  gGlobalGeneralOahGroup->
    enforceGroupQuietness ();

  gGlobalMxmltreeGenerationOahGroup->
    enforceGroupQuietness ();

  gGlobalMxmlTreeOahGroup->
    enforceGroupQuietness ();

  gGlobalMxmlTree2msrOahGroup->
    enforceGroupQuietness ();

  gGlobalMsrOahGroup->
    enforceGroupQuietness ();

  gGlobalMxmltreeGenerationOahGroup->
    enforceGroupQuietness ();

#ifdef EXTRA_OAH_IS_ENABLED
  gGlobalExtraOahGroup->
    enforceGroupQuietness ();
#endif
}

//______________________________________________________________________________
void msdlCompilerInsiderOahGroup::enforceGroupQuietness ()
{}

//______________________________________________________________________________
void msdlCompilerInsiderOahGroup::checkGroupOptionsConsistency ()
{
/* JMI

  if (inputSourceName.size () > 0 && inputSourceName == outputFileName) {
    stringstream s;

    s <<
      "\"" << inputSourceName << "\" is both the input and output file name";;

    oahError (s.str ());
  }




  if (! fOutputFileName.size ()) {
    stringstream s;

    s <<
      "msdlCompilerInsiderOahGroup: a MusicXML output file name must be chosen with '-o, -output-file-name";

    oahError (s.str ());
  }

  else if (fOutputFileName == gGlobalOahOahGroup->getInputSourceName ()) {
    stringstream s;

    s <<
      "\"" << fOutputFileName << "\" is both the input and output file name";

    oahError (s.str ());
  }
  */
}

//______________________________________________________________________________
void msdlCompilerInsiderOahGroup::acceptIn (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalOahOahGroup->getTraceOahVisitors ()) {
    gLogStream <<
      ".\\\" ==> msdlCompilerInsiderOahGroup::acceptIn ()" <<
      endl;
  }
#endif

  if (visitor<S_msdlCompilerInsiderOahGroup>*
    p =
      dynamic_cast<visitor<S_msdlCompilerInsiderOahGroup>*> (v)) {
        S_msdlCompilerInsiderOahGroup elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalOahOahGroup->getTraceOahVisitors ()) {
          gLogStream <<
            ".\\\" ==> Launching msdlCompilerInsiderOahGroup::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void msdlCompilerInsiderOahGroup::acceptOut (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalOahOahGroup->getTraceOahVisitors ()) {
    gLogStream <<
      ".\\\" ==> msdlCompilerInsiderOahGroup::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_msdlCompilerInsiderOahGroup>*
    p =
      dynamic_cast<visitor<S_msdlCompilerInsiderOahGroup>*> (v)) {
        S_msdlCompilerInsiderOahGroup elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalOahOahGroup->getTraceOahVisitors ()) {
          gLogStream <<
            ".\\\" ==> Launching msdlCompilerInsiderOahGroup::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void msdlCompilerInsiderOahGroup::browseData (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalOahOahGroup->getTraceOahVisitors ()) {
    gLogStream <<
      ".\\\" ==> msdlCompilerInsiderOahGroup::browseData ()" <<
      endl;
  }
#endif

  oahGroup::browseData (v);
}

//______________________________________________________________________________
void msdlCompilerInsiderHandler::print (ostream& os) const
{
  const unsigned int fieldWidth = 27;

  os <<
    "msdlCompilerInsiderHandler:" <<
    endl;

  ++gIndenter;

  printHandlerEssentials (
    os, fieldWidth);
  os << endl;

  os <<
    "Options groups (" <<
    singularOrPlural (
      fHandlerGroupsList.size (), "element",  "elements") <<
    "):" <<
    endl;

  if (fHandlerGroupsList.size ()) {
    os << endl;

    ++gIndenter;

    list<S_oahGroup>::const_iterator
      iBegin = fHandlerGroupsList.begin (),
      iEnd   = fHandlerGroupsList.end (),
      i      = iBegin;
    for ( ; ; ) {
      // print the element
      os << (*i);
      if (++i == iEnd) break;
      os << endl;
    } // for

    --gIndenter;
  }

  --gIndenter;

  os << endl;
}

ostream& operator<< (ostream& os, const S_msdlCompilerInsiderHandler& elt)
{
  elt->print (os);
  return os;
}

//_______________________________________________________________________________
S_msdlCompilerInsiderOahGroup gGlobalmsdlCompilerInsiderOahGroup;

S_msdlCompilerInsiderOahGroup msdlCompilerInsiderOahGroup::create ()
{
  msdlCompilerInsiderOahGroup* o = new msdlCompilerInsiderOahGroup ();
  assert (o != nullptr);

  return o;
}

msdlCompilerInsiderOahGroup::msdlCompilerInsiderOahGroup ()
  : oahGroup (
    "msdlCompiler",
    "hmkk", "help-msdlCompiler",
R"(Options that are used by msdlCompiler are grouped here.)",
    oahElementVisibilityKind::kElementVisibilityWhole)
{
  fGeneratorOutputKind = multiGeneratorOutputKind::k_NoOutput;

  initializemsdlCompilerInsiderOahGroup ();
}

msdlCompilerInsiderOahGroup::~msdlCompilerInsiderOahGroup ()
{}

//_______________________________________________________________________________
void msdlCompilerInsiderOahGroup::initializemsdlCompilerInsiderOahGroup ()
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream << left <<
      "Initializing \"" <<
      fGroupHeader <<
      "\" group" <<
      endl;
  }
#endif

  // JMI ???
}

//______________________________________________________________________________
void msdlCompilerInsiderOahGroup::printmsdlCompilerInsiderOahGroupValues (unsigned int fieldWidth)
{
  gLogStream <<
    "The msdlCompiler options are:" <<
    endl;

  ++gIndenter;

  // generate output kind
  // --------------------------------------

  gLogStream << left <<
    setw (fieldWidth) << "Generated output kind:" <<
    endl;

  ++gIndenter;

  gLogStream << left <<
    setw (fieldWidth) <<
    "multiGeneratorOutputKind" << " : " <<
    multiGeneratorOutputKindAsString (fGeneratorOutputKind) <<
    endl;

  --gIndenter;

  --gIndenter;
}

//______________________________________________________________________________
S_msdlCompilerInsiderOahGroup createGlobalmsdlCompilerInsiderOahGroup ()
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream <<
      "Creating global msdlCompiler insider OAH group" <<
      endl;
  }
#endif

  // protect library against multiple initializations
  if (! gGlobalmsdlCompilerInsiderOahGroup) {

    // create the global OAH group
    // ------------------------------------------------------

    gGlobalmsdlCompilerInsiderOahGroup =
      msdlCompilerInsiderOahGroup::create ();
    assert (gGlobalmsdlCompilerInsiderOahGroup != 0);

    // append versions information to list
    // ------------------------------------------------------

    appendVersionToVersionInfoList (
      "Initial",
      "December 2020",
      "Draft version");

    appendVersionToVersionInfoList (
      "1.001",
      "March 2021",
      "First version, compiles HelloWorld.msdl");

    appendVersionToVersionInfoList (
      "1.002",
      "March 2021",
      "Added keywords octaves, tab");
  }

  // return the global OAH group
  return gGlobalmsdlCompilerInsiderOahGroup;
}


}