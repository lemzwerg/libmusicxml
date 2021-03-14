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

#include <regex>

#include "enableExtraOahIfDesired.h"

#include "enableTracingIfDesired.h"
#ifdef TRACING_IS_ENABLED
  #include "traceOah.h"
#endif

#include "oahOah.h"

#include "generalOah.h"
#include "outputFileOah.h"
#include "extraOah.h"

// Guido
#include "guidoGenerationOah.h"

// MusicXML
#include "mxmlTreeOah.h"
#include "mxmlTreeOah.h"
#include "mxmltreeGenerationOah.h"

// MSR
#include "msrOah.h"
#include "msr2msrOah.h"

// mxmltree
#include "mxmltreeGenerationOah.h"
#include "mxmlTree2msrOah.h"

// Lilypond
#include "lpsr.h"

#include "msr2lpsrOah.h"
#include "lpsrOah.h"
#include "lilypondGenerationOah.h"

// Braille music
#include "bsr.h"

#include "msr2bsrOah.h"
#include "bsrOah.h"
#include "brailleGenerationOah.h"

// generation
#include "msrGenerationOah.h"


#include "version.h"

#include "Mikrokosmos3WanderingOah.h"
#include "Mikrokosmos3WanderingInsiderHandler.h"


using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
S_Mikrokosmos3WanderingInsiderHandler Mikrokosmos3WanderingInsiderHandler::create (
  const string&       executableName,
  const string&       handlerHeader,
  multiGeneratorOutputKind
                      generatorOutputKind)
{
  // create the insider handler
  Mikrokosmos3WanderingInsiderHandler* o = new
    Mikrokosmos3WanderingInsiderHandler (
      executableName,
      handlerHeader,
      generatorOutputKind);
  assert (o != nullptr);

  return o;
}

Mikrokosmos3WanderingInsiderHandler::Mikrokosmos3WanderingInsiderHandler (
  const string&       executableName,
  const string&       handlerHeader,
  multiGeneratorOutputKind
                      generatorOutputKind)
  : oahInsiderHandler (
      executableName,
      handlerHeader,
R"(                Welcome to Mikrokosmos3Wandering,
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

  // create the Mikrokosmos3Wandering prefixes
  createTheMikrokosmos3WanderingPrefixes ();

  // create the Mikrokosmos3Wandering option groups
  createTheMikrokosmos3WanderingOptionGroups (
    executableName,
    generatorOutputKind);
}

Mikrokosmos3WanderingInsiderHandler::~Mikrokosmos3WanderingInsiderHandler ()
{}

string Mikrokosmos3WanderingInsiderHandler::usageInformation (
  multiGeneratorOutputKind generatorOutputKind)
{
  stringstream s;

  s <<
R"(Usage: Mikrokosmos3Wandering [option]*
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

void Mikrokosmos3WanderingInsiderHandler::handlerOahError (
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

string Mikrokosmos3WanderingInsiderHandler::handlerExecutableAboutInformation () const
{
  return
    Mikrokosmos3WanderingAboutInformation (
      fGeneratorOutputKind);
}

string Mikrokosmos3WanderingInsiderHandler::Mikrokosmos3WanderingAboutInformation (
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
      headPart =
R"(What msdlCompiler does:

    This multi-pass generator performs various passes depending on the output generated)";
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
        Pass 1:  generate an MSR from the MSDL input)";

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
        Pass 2:  converts the MSR into a second MSR;
        Pass 3:  converts the second MSR into an MusicXML tree;
        Pass 4:  converts the MusicXML tree to Guido code
                 and writes it to standard output.)";
      break;

    case multiGeneratorOutputKind::kLilyPondOutput:
      specificPart =
R"(
        Pass 2:  converts the MSR into a second MSR;
        Pass 3:  converts the second MSR into a
                 LilyPond Score Representation (LPSR);
        Pass 4:  converts the LPSR to LilyPond code
                 and writes it to standard output.)";
      break;

    case multiGeneratorOutputKind::kBrailleOutput:
      specificPart =
R"(
        Pass 2:  converts the MSR into a second MSR;
        Pass 3a: converts the second MSR into a
                 Braille Score Representation (BSR)
                 containing one Braille page per MusicXML page;
        Pass 3b: converts the BSRinto another BSR
                 with as many Braille pages as needed
                 to fit the line and page lengthes;
        Pass 4:  converts the BSR to braille music text
                 and writes it to standard output.)

    In this preliminary version, pass 3b merely clones the BSR it receives.)";
      break;

    case multiGeneratorOutputKind::kMusicXMLOutput:
      specificPart =
R"(
        Pass 2:  converts the MSR into a second MSR;
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
void Mikrokosmos3WanderingInsiderHandler::createTheMikrokosmos3WanderingPrefixes ()
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream <<
      "Creating the Mikrokosmos3Wandering prefixes in \"" <<
      fHandlerHeader <<
      "\"" <<
      endl;
  }
#endif

  createTheCommonPrefixes ();
}

//______________________________________________________________________________
void Mikrokosmos3WanderingInsiderHandler::createTheMikrokosmos3WanderingOptionGroups (
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

  // initialize options handling, phase 2
  // ------------------------------------------------------

  // create the MSR OAH group
  appendGroupToHandler (
    createGlobalMsrOahGroup ());

  // create the Mikrokosmos3Wandering OAH group
  appendGroupToHandler (
    createGlobalMikrokosmos3WanderingOahGroup ());

  // create the Mikrokosmos3Wandering insider OAH group
  appendGroupToHandler (
    createGlobalMikrokosmos3WanderingInsiderOahGroup ());

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
      // create the msr2msr OAH group
      appendGroupToHandler (
        createGlobalMsr2msrOahGroup ());

      // create the msr2mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMxmltreeGenerationOahGroup ());

      // create the mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMxmlTreeOahGroup ());

      // create the Guido generation OAH group
      appendGroupToHandler (
        createGlobalGuidoGenerationOahGroup ());
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
      break;

    case multiGeneratorOutputKind::kMusicXMLOutput:
      // create the msr2msr OAH group
      appendGroupToHandler (
        createGlobalMsr2msrOahGroup ());

      // create the msr2mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMxmltreeGenerationOahGroup ());

      // create the mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMxmlTreeOahGroup ());
      break;

    case multiGeneratorOutputKind::kMidiOutput:
      break;
  } // switch

  // create the multi generator OAH group
  appendGroupToHandler (
    createGlobalMultiGeneratorOahGroup ());

#ifdef EXTRA_OAH_IS_ENABLED
  // create the extra OAH group
  appendGroupToHandler (
    createGlobalExtraOahGroup ());
#endif
}

//______________________________________________________________________________
void Mikrokosmos3WanderingInsiderHandler::checkOptionsAndArgumentsFromArgcAndArgv () const
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

  checkNoInputSourceInArgumentsVector ();
}

//______________________________________________________________________________
string Mikrokosmos3WanderingInsiderHandler::fetchOutputFileNameFromTheOptions () const
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
      "Mikrokosmos3WanderingInsiderHandler::fetchOutputFileNameFromTheOptions()" <<
      " outputFileNameHasBeenSet: " <<
      booleanAsString (outputFileNameHasBeenSet) <<
      " autoOutputFileNameHasBeenSet: " <<
      booleanAsString (autoOutputFileNameHasBeenSet) <<
      endl;
  }
#endif

  string outputFileName;

  if (outputFileNameHasBeenSet) {
    // '-o, -output-file-name' has been chosen
    outputFileName =
      outputFileNameStringAtom->
        getStringVariable ();
  }

  else if (autoOutputFileNameHasBeenSet) {
     // '-aofn, -auto-output-file-name' has been chosen

    // start with the executable name
    outputFileName = fHandlerExecutableName;

    // add the output file name suffix
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
              case kBrailleOutputAscii:
                outputFileName += "_ASCII";
                break;

              case kBrailleOutputUTF8:
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

              case kBrailleOutputUTF8Debug:
                outputFileName += "_UTF8Debug";
                break;

              case kBrailleOutputUTF16:
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

  else {
    // neither outputFileNameHasBeenSet nor autoOutputFileNameHasBeenSet
    // has been set:
    // return empty outputFileName to indicate that output goes to stdout
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
void Mikrokosmos3WanderingInsiderHandler::checkHandlerOptionsConsistency ()
{}

//______________________________________________________________________________
void Mikrokosmos3WanderingInsiderHandler::enforceHandlerQuietness ()
{
#ifdef TRACING_IS_ENABLED
  gGlobalTraceOahGroup->
    enforceGroupQuietness ();
#endif

  gGlobalMikrokosmos3WanderingInsiderOahGroup->
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
void Mikrokosmos3WanderingInsiderOahGroup::enforceGroupQuietness ()
{}

//______________________________________________________________________________
void Mikrokosmos3WanderingInsiderOahGroup::checkGroupOptionsConsistency ()
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
      "Mikrokosmos3WanderingInsiderOahGroup: a MusicXML output file name must be chosen with '-o, -output-file-name";

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
void Mikrokosmos3WanderingInsiderOahGroup::acceptIn (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalOahOahGroup->getTraceOahVisitors ()) {
    gLogStream <<
      ".\\\" ==> Mikrokosmos3WanderingInsiderOahGroup::acceptIn ()" <<
      endl;
  }
#endif

  if (visitor<S_Mikrokosmos3WanderingInsiderOahGroup>*
    p =
      dynamic_cast<visitor<S_Mikrokosmos3WanderingInsiderOahGroup>*> (v)) {
        S_Mikrokosmos3WanderingInsiderOahGroup elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalOahOahGroup->getTraceOahVisitors ()) {
          gLogStream <<
            ".\\\" ==> Launching Mikrokosmos3WanderingInsiderOahGroup::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void Mikrokosmos3WanderingInsiderOahGroup::acceptOut (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalOahOahGroup->getTraceOahVisitors ()) {
    gLogStream <<
      ".\\\" ==> Mikrokosmos3WanderingInsiderOahGroup::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_Mikrokosmos3WanderingInsiderOahGroup>*
    p =
      dynamic_cast<visitor<S_Mikrokosmos3WanderingInsiderOahGroup>*> (v)) {
        S_Mikrokosmos3WanderingInsiderOahGroup elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalOahOahGroup->getTraceOahVisitors ()) {
          gLogStream <<
            ".\\\" ==> Launching Mikrokosmos3WanderingInsiderOahGroup::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void Mikrokosmos3WanderingInsiderOahGroup::browseData (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalOahOahGroup->getTraceOahVisitors ()) {
    gLogStream <<
      ".\\\" ==> Mikrokosmos3WanderingInsiderOahGroup::browseData ()" <<
      endl;
  }
#endif

  oahGroup::browseData (v);
}

//______________________________________________________________________________
void Mikrokosmos3WanderingInsiderHandler::print (ostream& os) const
{
  const unsigned int fieldWidth = 27;

  os <<
    "Mikrokosmos3WanderingInsiderHandler:" <<
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

ostream& operator<< (ostream& os, const S_Mikrokosmos3WanderingInsiderHandler& elt)
{
  elt->print (os);
  return os;
}

//_______________________________________________________________________________
S_Mikrokosmos3WanderingInsiderOahGroup gGlobalMikrokosmos3WanderingInsiderOahGroup;

S_Mikrokosmos3WanderingInsiderOahGroup Mikrokosmos3WanderingInsiderOahGroup::create ()
{
  Mikrokosmos3WanderingInsiderOahGroup* o = new Mikrokosmos3WanderingInsiderOahGroup ();
  assert (o != nullptr);

  return o;
}

Mikrokosmos3WanderingInsiderOahGroup::Mikrokosmos3WanderingInsiderOahGroup ()
  : oahGroup (
    "Mikrokosmos3Wandering",
    "hmkk", "help-Mikrokosmos3Wandering",
R"(Options that are used by Mikrokosmos3Wandering are grouped here.)",
    oahElementVisibilityKind::kElementVisibilityWhole)
{
// JMI  fGenerationAPIKind = msrGenerationAPIKind::kMsrFunctionsAPIKind; // default value
  fGenerationAPIKind = msrGenerationAPIKind::kMsrStringsAPIKind; // default value

  fGeneratorOutputKind = multiGeneratorOutputKind::k_NoOutput;

  fQuitAfterPass2a = false;
  fQuitAfterPass2b = false;

  initializeMikrokosmos3WanderingInsiderOahGroup ();
}

Mikrokosmos3WanderingInsiderOahGroup::~Mikrokosmos3WanderingInsiderOahGroup ()
{}

//_______________________________________________________________________________
void Mikrokosmos3WanderingInsiderOahGroup::initializeMikrokosmos3WanderingInsiderOahGroup ()
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

  // quit after some passes
  // --------------------------------------

  createInsiderQuitSubGroup ();
}

//_______________________________________________________________________________
void Mikrokosmos3WanderingInsiderOahGroup::createInsiderQuitSubGroup ()
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream << left <<
      "Creating insider quit subgroup in \"" <<
      fGroupHeader <<
      "\"" <<
      endl;
  }
#endif

  S_oahSubGroup
    quitAfterSomePassesSubGroup =
      oahSubGroup::create (
        "Quit after some passes",
        "hm2xquit", "help-msr2gmn-quit",
R"()",
      oahElementVisibilityKind::kElementVisibilityWhole,
      this);

  appendSubGroupToGroup (quitAfterSomePassesSubGroup);

  // quit after pass 2a

  fQuitAfterPass2a = false;

  S_oahBooleanAtom
    quit2aOahBooleanAtom =
      oahBooleanAtom::create (
        "qap2a", "quitAfterPass-after-pass2a",
R"(Quit after pass 2a, i.e. after conversion
of the MusicXML tree to an MSR skeleton.)",
        "quitAfterPass2a",
        fQuitAfterPass2a);

  quitAfterSomePassesSubGroup->
    appendAtomToSubGroup (
      quit2aOahBooleanAtom);

  // quit after pass 2b

  fQuitAfterPass2b = false;

  S_oahBooleanAtom
    quit2bOahBooleanAtom =
      oahBooleanAtom::create (
        "qap2b", "quitAfterPass-after-pass2b",
R"(Quit after pass 2b, i.e. after conversion
of the MusicXML tree to MSR.)",
        "quitAfterPass2b",
        fQuitAfterPass2b);

  quitAfterSomePassesSubGroup->
    appendAtomToSubGroup (
      quit2bOahBooleanAtom);
}

//______________________________________________________________________________
void Mikrokosmos3WanderingInsiderOahGroup::printMikrokosmos3WanderingInsiderOahGroupValues (unsigned int fieldWidth)
{
  gLogStream <<
    "The Mikrokosmos3Wandering options are:" <<
    endl;

  ++gIndenter;

  // generation API kind
  // --------------------------------------

  gLogStream << left <<
    setw (fieldWidth) << "Generation API kind:" <<
    endl;

  ++gIndenter;

  gLogStream << left <<
    setw (fieldWidth) <<
    "msrGenerationAPIKind" << " : " <<
    msrGenerationAPIKindAsString (fGenerationAPIKind) <<
    endl;

  --gIndenter;

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

  // quit after some passes
  // --------------------------------------

  gLogStream <<
    "Quit after some passes:" <<
    endl;

  ++gIndenter;

  gLogStream << left <<
    setw (fieldWidth) << "quitAfterPass2a" << " : " <<
    booleanAsString (fQuitAfterPass2a) <<
    endl <<
    setw (fieldWidth) << "quitAfterPass2b" << " : " <<
    booleanAsString (fQuitAfterPass2b) <<
    endl;

  --gIndenter;

  --gIndenter;
}

//______________________________________________________________________________
S_Mikrokosmos3WanderingInsiderOahGroup createGlobalMikrokosmos3WanderingInsiderOahGroup ()
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream <<
      "Creating global Mikrokosmos3Wandering insider OAH group" <<
      endl;
  }
#endif

  // protect library against multiple initializations
  if (! gGlobalMikrokosmos3WanderingInsiderOahGroup) {

    // create the global OAH group
    // ------------------------------------------------------

    gGlobalMikrokosmos3WanderingInsiderOahGroup =
      Mikrokosmos3WanderingInsiderOahGroup::create ();
    assert (gGlobalMikrokosmos3WanderingInsiderOahGroup != 0);

    // append versions information to list
    // ------------------------------------------------------

    appendVersionToVersionInfoList (
      "Initial",
      "December 2020",
      "First draft version");
  }

  // return the global OAH group
  return gGlobalMikrokosmos3WanderingInsiderOahGroup;
}


}
