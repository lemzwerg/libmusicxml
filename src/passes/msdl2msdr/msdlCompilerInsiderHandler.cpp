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

#include "msdl.h"

#include "generatorsOah.h"

#include "msdlOah.h"

#include "msdl2msdrOah.h"

#include "musicxmlOah.h"
#include "mxmlTreeOah.h"
#include "msr2mxmlTreeOah.h"

#include "msrOah.h"
#include "msr2msrOah.h"

#include "msr2mxmlTreeOah.h"
#include "mxmlTree2msrOah.h"

#include "lpsr.h"

#include "msr2lpsrOah.h"
#include "lpsrOah.h"
#include "lpsr2lilypondOah.h"
#include "lilypondOah.h"

#include "bsr.h"

#include "msr2bsrOah.h"
#include "bsrOah.h"
#include "bsr2brailleOah.h"
#include "brailleOah.h"

#include "xml2gmnInsiderHandler.h"

#include "version.h"

#include "msdlCompilerInsiderHandler.h"


using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
S_msdlCompilerInsiderHandler msdlCompilerInsiderHandler::create (
  const string&       executableName,
  const string&       handlerHeader,
  generatorOutputKind generatorOutputKind)
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
  const string&       executableName,
  const string&       handlerHeader,
  generatorOutputKind generatorOutputKind)
  : oahInsiderHandler (
      executableName,
      handlerHeader,
R"(                  Welcome to the MSDL compiler,
     that generates Guido, MusicXML, LilyPond or braille music
          from MSDL (Music Scores Description Language)
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
  generatorOutputKind generatorOutputKind)
{
  stringstream s;

  s <<
R"(Usage: msdl ([options] | [MSDMLFile|-])+
)" <<
    endl <<
    "The help below is available when generating " <<
    generatorOutputKindAsString (generatorOutputKind) <<
    " output";

  return s.str ();
}

void msdlCompilerInsiderHandler::handlerOahError (
  const string& errorMessage)
{
  stringstream s;

  s <<
    errorMessage  <<
    " when generating " <<
    generatorOutputKindAsString (fGeneratorOutputKind) <<
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
  generatorOutputKind theGeneratorOutputKind) const
{
  string result;

  unsigned int passesNumber = 0;

  switch (theGeneratorOutputKind) {
    case k_NoOutput:
      // should not occur
      break;

    case kGuidoOutput:
      passesNumber = 4;
      break;

    case kLilyPondOutput:
      passesNumber = 3;
      break;

    case kBrailleOutput:
      passesNumber = 4;
      break;

    case kMusicXMLOutput:
      passesNumber = 4;
      break;

    case kMidiOutput:
      passesNumber = 0;
      break;
  } // switch

  stringstream commonHeadPartStream;

  commonHeadPartStream <<
R"(What msdl does:

    This multi-pass MSDL compiler basically performs )" <<
    passesNumber <<
    " passes when generating " <<
    generatorOutputKindAsString (theGeneratorOutputKind) <<
    " output:" <<
    endl <<
R"(
        Pass 1:  convert the MSDL data to an MSR)";

  string specificPart;

  switch (theGeneratorOutputKind) {
    case k_NoOutput:
      // should not occur, unless the run is a pure help one
      break;

    case kGuidoOutput:
      specificPart =
R"(
        Pass 2:  converts the MSR into a second MSR;
        Pass 3:  converts the second MSR into an MusicXML tree;
        Pass 4:  converts the MusicXML tree to Guido code
                 and writes it to standard output.)";
      break;

    case kLilyPondOutput:
      specificPart =
R"(
        Pass 2:  converts the MSR into a
                 LilyPond Score Representation (LPSR);
        Pass 3:  converts the LPSR to LilyPond code
                 and writes it to standard output.)";
      break;

    case kBrailleOutput:
      specificPart =
R"(
        Pass 2a: converts the MSR into a
                 Braille Score Representation (BSR)
                 containing one Braille page per MusicXML page;
        Pass 2b: converts the BSRinto another BSR
                 with as many Braille pages as needed
                 to fit the line and page lengthes;
        Pass 3:  converts the BSR to braille music text
                 and writes it to standard output.)

    In this preliminary version, pass 2b merely clones the BSR it receives.)";
      break;

    case kMusicXMLOutput:
      specificPart =
R"(
        Pass 2:  converts the MSR into a second MSR;
        Pass 3:  converts the second MSR into an MusicXML tree;
        Pass 4:  converts the MusicXML tree to MusicXML code
                 and writes it to standard output.)";
      break;

    case kMidiOutput:
      break;
  } // switch

   string commonTailPart =
R"(

    Other passes are performed according to the options, such as
    printing views of the internal data or printing a summary of the score.

    The activity log and warning/error messages go to standard error.)";

 return
   commonHeadPartStream.str () + specificPart + commonTailPart;
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
  generatorOutputKind generatorOutputKind)
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

  // create the generators OAH group
  appendGroupToHandler (
    createGlobalGeneratorsOahGroup ());

  // create the output file OAH group
  appendGroupToHandler (
    createGlobalOutputFileOahGroup ());

  // initialize the library
  // ------------------------------------------------------

  initializeMSR (); // used whatever the output kind

  initializeMSDL (); // used whatever the output kind

  // initialize options handling, phase 2
  // ------------------------------------------------------

  // create the msdl2msr OAH group
  createGlobalMsdl2msrOahGroup ();

  // create the MSR OAH group
  appendGroupToHandler (
    createGlobalMsrOahGroup ());

  // create the MSDR OAH group
  appendGroupToHandler (
    createGlobalMsdlOahGroup ());

  // create the groups needed according to the generated output kind
  /*
    CAUTION:
      some option names are identical in OAH groups
      that are not meant to be used at the same time,
      such as gGlobalMsr2msrOahGroup and gGlobalMsr2lpsrOahGroup
  */

  switch (generatorOutputKind) {
    case k_NoOutput:
      // should not occur, unless the run is a pure help one
      break;

    case kGuidoOutput:
      // create the msr2msr OAH group
      appendGroupToHandler (
        createGlobalMsr2msrOahGroup ());

      // create the msr2mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMsr2mxmlTreeOahGroup ());

      // create the mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMxmlTreeOahGroup ());

      // create the MusicXML OAH group
      appendGroupToHandler (
        createGlobalMusicxmlOahGroup ());

      // create the xml2gmn OAH group
      appendGroupToHandler (
        createGlobalXml2gmnOahGroup ());
      break;

    case kLilyPondOutput:
      // initialize the library
      initializeLPSR ();

      // create the msr2lpsr OAH group
      appendGroupToHandler (
        createGlobalMsr2lpsrOahGroup ());

      // create the LPSR OAH group
      appendGroupToHandler (
        createGlobalLpsrOahGroup ());

      // create the lpsr2lilypond OAH group
      appendGroupToHandler (
        createGlobalLpsr2lilypondOahGroup ());

      // create the LilyPond OAH group
      appendGroupToHandler (
        createGlobalLilypondOahGroup ());
      break;

    case kBrailleOutput:
      // initialize the library
      initializeBSR ();

      // create the msr2bsr OAH group
      appendGroupToHandler (
        createGlobalMsr2bsrOahGroup ());

      // create the BSR OAH group
      appendGroupToHandler (
        createGlobalBsrOahGroup ());

      // create the bsr2braille OAH group
      appendGroupToHandler (
        createGlobalBsr2brailleOahGroup ());

      // create the braille OAH group
      appendGroupToHandler (
        createGlobalBrailleOahGroup ());
      break;

    case kMusicXMLOutput:
      // create the msr2msr OAH group
      appendGroupToHandler (
        createGlobalMsr2msrOahGroup ());

      // create the msr2mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMsr2mxmlTreeOahGroup ());

      // create the mxmlTree OAH group
      appendGroupToHandler (
        createGlobalMxmlTreeOahGroup ());

      // create the MusicXML OAH group
      appendGroupToHandler (
        createGlobalMusicxmlOahGroup ());
      break;

    case kMidiOutput:
      break;
  } // switch

  // create the msdlCompiler OAH group
  appendGroupToHandler (
    createGlobalMsdl2msdrOahGroup ());

  appendGroupToHandler (
    createGlobalMsdlCompilerInsiderOahGroup ());

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
      case k_NoOutput:
        // should not occur
        outputFileName = "___k_NoOutput___";
        break;

      case kGuidoOutput:
        outputFileName += ".gmn";
        break;

      case kLilyPondOutput:
        outputFileName += ".ly";
        break;

      case kBrailleOutput:
        {
          S_oahStringAtom
            outputFileNameStringAtom =
              gGlobalOutputFileOahGroup->
                getOutputFileNameStringAtom ();

          // should encoding be used by the output file name?
          bsrBrailleOutputKind
            brailleOutputKind =
              gGlobalBsr2brailleOahGroup->
                getBrailleOutputKind ();

          if (gGlobalBsr2brailleOahGroup->getUseEncodingInFileName ()) {
            switch (brailleOutputKind) {
              case kBrailleOutputAscii:
                outputFileName += "_ASCII";
                break;

              case kBrailleOutputUTF8:
                outputFileName += "_UTF8";
                  /* JMI
                switch (gGlobalBsr2brailleOahGroup->getByteOrderingKind ()) {
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
                switch (gGlobalBsr2brailleOahGroup->getByteOrderingKind ()) {
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

      case kMusicXMLOutput:
        outputFileName += ".xml";
        break;

      case kMidiOutput:
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
void msdlCompilerInsiderHandler::checkHandlerOptionsConsistency ()
{}

//______________________________________________________________________________
void msdlCompilerInsiderHandler::enforceHandlerQuietness ()
{
#ifdef TRACING_IS_ENABLED
  gGlobalTraceOahGroup->
    enforceGroupQuietness ();
#endif

  gGlobalMsdlCompilerInsiderOahGroup->
    enforceGroupQuietness ();

  gGlobalGeneralOahGroup->
    enforceGroupQuietness ();

  gGlobalMusicxmlOahGroup->
    enforceGroupQuietness ();

  gGlobalMxmlTreeOahGroup->
    enforceGroupQuietness ();

  gGlobalMxmlTree2msrOahGroup->
    enforceGroupQuietness ();

  gGlobalMsrOahGroup->
    enforceGroupQuietness ();

  gGlobalMsr2mxmlTreeOahGroup->
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
S_msdlCompilerInsiderOahGroup gGlobalMsdlCompilerInsiderOahGroup;

S_msdlCompilerInsiderOahGroup msdlCompilerInsiderOahGroup::create ()
{
  msdlCompilerInsiderOahGroup* o = new msdlCompilerInsiderOahGroup ();
  assert (o != nullptr);

  return o;
}

msdlCompilerInsiderOahGroup::msdlCompilerInsiderOahGroup ()
  : oahGroup (
    "msdlCompiler",
    "hmsdlc", "help-msdl-compiler",
R"(Options that are used by MSDL ompiler are grouped here.)",
    kElementVisibilityWhole)
{
  fKeywordsInputLanguageKind       = kKeywordsEnglish; // MSDL default
  fKeywordsTranslationLanguageKind = kKeywordsEnglish; // MSDL default

  fGeneratorOutputKind = k_NoOutput;

  fGenerateComments = false;
  fGenerateStem = false;
  fGenerateBars = false;

  fQuitAfterPass2a = false;
  fQuitAfterPass2b = false;

  initializeMsdlCompilerInsiderOahGroup ();
}

msdlCompilerInsiderOahGroup::~msdlCompilerInsiderOahGroup ()
{}

//_______________________________________________________________________________
void msdlCompilerInsiderOahGroup::initializeMsdlCompilerInsiderOahGroup ()
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

  // Guido
  // --------------------------------------

  createInsiderGuidoSubGroup ();

  // quit after some passes
  // --------------------------------------

  createInsiderQuitSubGroup ();
}

void msdlCompilerInsiderOahGroup::createInsiderGuidoSubGroup ()
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream << left <<
      "Creating insider Guido subgroup in \"" <<
      fGroupHeader <<
      "\"" <<
      endl;
  }
#endif

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Guido",
        "mkk-guido", "help-mkk-guido",
R"()",
      kElementVisibilityWhole,
      this);

  appendSubGroupToGroup (subGroup);

/* JMI
  // keywords input language

  msdlKeywordsLanguageKind
    msrKeywordsInputLanguageKindDefaultValue = kKeywordsEnglish;

  subGroup->
    appendAtomToSubGroup (
      msdlKeywordsLanguageAtom::create (
        "mkil", "msl-keywords-input-language",
        regex_replace (
          regex_replace (
            regex_replace (
R"(Use language LANGUAGE as MSDL keywords input language.
The NUMBER MSDL keywords languages available are:
KEYWORDS_LANGUAGES.
The default is 'DEFAULT_VALUE'.)",
              regex ("NUMBER"),
              to_string (gGlobalQuarterTonesPitchesLanguageKindsMap.size ())),
            regex ("KEYWORDS_LANGUAGES"),
            gIndenter.indentMultiLineString (
              existingMsdlKeywordsLanguageKinds (K_NAMES_LIST_MAX_LENGTH))),
          regex ("DEFAULT_VALUE"),
          msdlKeywordsLanguageKindAsString (
            msrKeywordsInputLanguageKindDefaultValue)),
        "LANGUAGE",
        "keywordsInputLanguageKind",
        fKeywordsInputLanguageKind));

  // keywords translation language

  msdlKeywordsLanguageKind
    msrKeywordsTranslationLanguageKindDefaultValue = kKeywordsEnglish;

  subGroup->
    appendAtomToSubGroup (
      msdlKeywordsLanguageAtom::create (
        "mktl", "msl-keywords-translation-language",
        regex_replace (
          regex_replace (
            regex_replace (
R"(Use language LANGUAGE as MSDL keywords translation language.
The NUMBER MSDL keywords languages available are:
KEYWORDS_LANGUAGES.
The default is 'DEFAULT_VALUE'.)",
              regex ("NUMBER"),
              to_string (gGlobalQuarterTonesPitchesLanguageKindsMap.size ())),
            regex ("KEYWORDS_LANGUAGES"),
            gIndenter.indentMultiLineString (
              existingMsdlKeywordsLanguageKinds (K_NAMES_LIST_MAX_LENGTH))),
          regex ("DEFAULT_VALUE"),
          msdlKeywordsLanguageKindAsString (
            msrKeywordsTranslationLanguageKindDefaultValue)),
        "LANGUAGE",
        "keywordsTranslationLanguageKind",
        fKeywordsTranslationLanguageKind));
*/

  // generate comments

  subGroup->
    appendAtomToSubGroup (
      oahBooleanAtom::create (
        "generate-comments", "",
R"(Generate comments in the Guido output.)",
        "generateComments",
        fGenerateComments));

  // generate stem

  subGroup->
    appendAtomToSubGroup (
      oahBooleanAtom::create (
        "generate-stem", "",
R"(Generate stem in the Guido output.)",
        "generateStem",
        fGenerateStem));

  // generate bars

  subGroup->
    appendAtomToSubGroup (
      oahBooleanAtom::create (
        "generate-bars", "",
R"(Generate barlines in the Guido output.)",
        "generateBars",
        fGenerateBars));
}

//_______________________________________________________________________________
void msdlCompilerInsiderOahGroup::createInsiderQuitSubGroup ()
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
      kElementVisibilityWhole,
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
void msdlCompilerInsiderOahGroup::printMsdlCompilerInsiderOahGroupValues (unsigned int fieldWidth)
{
  gLogStream <<
    "The MSDL compiler options are:" <<
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
    "generatorOutputKind" << " : " <<
    generatorOutputKindAsString (fGeneratorOutputKind) <<
    endl;

  --gIndenter;

  // Guido
  // --------------------------------------

  gLogStream << left <<
    setw (fieldWidth) << "Guido:" <<
    endl;

  ++gIndenter;

  gLogStream << left <<
    setw (fieldWidth) <<
    "keywordsInputLanguageKind" << " : " <<
    msdlKeywordsLanguageKindAsString (fKeywordsInputLanguageKind) <<
    endl <<
    setw (fieldWidth) <<
    "keywordsTranslationLanguageKind" << " : " <<
    msdlKeywordsLanguageKindAsString (fKeywordsTranslationLanguageKind) <<
    endl <<

    setw (fieldWidth) <<
    "generateComments" << " : " << booleanAsString (fGenerateComments) <<
    endl <<
    setw (fieldWidth) <<
    "generateStem" << " : " << booleanAsString (fGenerateStem) <<
    endl <<
    setw (fieldWidth) <<
    "generateBars" << " : " << booleanAsString (fGenerateBars) <<
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
S_msdlCompilerInsiderOahGroup createGlobalMsdlCompilerInsiderOahGroup ()
{
#ifdef TRACING_IS_ENABLED
  if (getTraceOah ()) {
    gLogStream <<
      "Creating global msdlCompiler insider OAH group" <<
      endl;
  }
#endif

  // protect library against multiple initializations
  if (! gGlobalMsdlCompilerInsiderOahGroup) {

    // create the global OAH group
    // ------------------------------------------------------

    gGlobalMsdlCompilerInsiderOahGroup =
      msdlCompilerInsiderOahGroup::create ();
    assert (gGlobalMsdlCompilerInsiderOahGroup != 0);

    // append versions information to list
    // ------------------------------------------------------

    appendVersionToVersionInfoList (
      "Initial",
      "December 2020",
      "First draft version");
  }

  // return the global OAH group
  return gGlobalMsdlCompilerInsiderOahGroup;
}


}
