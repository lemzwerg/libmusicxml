/*

  Copyright (C) 2003-2008  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
*/

#ifdef VC6
# pragma warning (disable : 4786)
#endif

#include <iomanip>      // setw()), set::precision(), ...

#include <fstream>      // ofstream, ofstream::open(), ofstream::close()

#include "libmusicxml.h"
#include "version.h"

#include "utilities.h"

#include "musicXMLOptions.h"
#include "lilypondOptions.h"

#include "xml2lilypondOptionsHandling.h"

#include "musicXMLTree2MsrInterface.h"
#include "msr2LpsrInterface.h"
#include "lpsr2LilypondInterface.h"


using namespace std;

using namespace MusicXML2;


// useful shortcut macros
#define idtr indenter::gIndenter
#define tab  indenter::gIndenter.getSpacer ()

#define TRACE_OPTIONS 0

//_______________________________________________________________________________
vector<string> analyzeOptionsAndArguments (
S_xml2lilypondOptionsHandler
                 optionsHandler,
  int            argc,
  char*          argv[],
  string&        inputFileName,
  string&        outputFileName)
{
  // analyse the options
  vector<string>
    argumentsVector =
      optionsHandler->
        analyzeOptions (argc, argv);

  if (TRACE_OPTIONS) {
    // print the options values
    cerr <<
      "Options values:" <<
      endl;

    idtr++;
    
    optionsHandler->
      printOptionsValues (cerr);
        
    cerr <<
      endl;

    idtr--;
  }
  
  return argumentsVector;
}

//_______________________________________________________________________________
int main (int argc, char *argv[]) 
{
  // initialize the components of MSR that we'll use
  initializeMSR ();
  initializeLPSR ();
  
  /*
  cerr << "argc = " << argc << endl;
  for (int i = 0; i < argc ; i++ ) {
    cerr << "argv[ " << i << "] = " << argv[i] << endl;
  }
  */

  // create the options handler
  // ------------------------------------------------------

  S_xml2lilypondOptionsHandler
    optionsHandler =
      xml2lilypondOptionsHandler::create ();

  // analyze the command line options and arguments
  // ------------------------------------------------------

  string    inputFileName;
  string    outputFileName;

  vector<string>
    argumentsVector =
      analyzeOptionsAndArguments (
        optionsHandler,
        argc, argv,
        inputFileName, outputFileName);

  // print the resulting options
  if (TRACE_OPTIONS) {
    cerr <<
      optionsHandler <<
      endl <<
      endl;
  }

  // program name
  // ------------------------------------------------------
  
  gGeneralOptions->fProgramName =
    optionsHandler->getProgramName ();
  
  // input source name
  // ------------------------------------------------------

  switch (argumentsVector.size ()) {
    case 1:
      gGeneralOptions->fInputSourceName =
        argumentsVector [0]; // inputFileName; // JMI
      break;
      
    default:
      {
        cerr <<
          "Input file name or '-' for standard input expected" <<
          endl;
        exit (3);
      }
  } // switch
  
  // translation date
  // ------------------------------------------------------

  time_t      translationRawtime;
  struct tm*  translationTimeinfo;
  char buffer [80];

  time (&translationRawtime);
  translationTimeinfo = localtime (&translationRawtime);

  strftime (buffer, 80, "%A %F @ %T %Z", translationTimeinfo);
  gGeneralOptions->fTranslationDate = buffer;

  // welcome message
  // ------------------------------------------------------

  if (gGeneralOptions->fTraceGeneral) {
    cerr <<  idtr <<
      "This is xml2Lilypond v" << currentVersionNumber () << 
      " from libmusicxml2 v" << musicxmllibVersionStr () <<
      endl;

    cerr << idtr <<
      "Launching conversion of ";

    if (gGeneralOptions->fInputSourceName == "-")
      cerr << "standard input";
    else
      cerr << "\"" << gGeneralOptions->fInputSourceName << "\"";

    cerr <<
      " to LilyPond" <<
      endl;

    cerr << idtr <<
      "Time is " << gGeneralOptions->fTranslationDate <<
      endl;      

    cerr << idtr <<
      "LilyPond code will be written to ";
    if (outputFileName.size ())
      cerr << outputFileName;
    else
      cerr << "standard output";
    cerr <<
      endl <<
      endl;
    
    cerr << idtr <<
      "The command line is:" <<
      endl;

    idtr++;
    
    cerr <<
      idtr <<
        optionsHandler->getCommandLineWithLongOptions () <<
      endl;

    idtr--;
    cerr <<
      idtr <<
        "or:" <<
        endl;
    idtr++;
    
    cerr <<
      idtr <<
        optionsHandler->getCommandLineWithShortOptions () <<
        endl <<
      endl;

    idtr--;
  }

  // print the chosen LilyPond options
  // ------------------------------------------------------

  optionsHandler->
    printOptionsValues (cerr);

  // acknoledge end of command line analysis
  // ------------------------------------------------------

  if (gGeneralOptions->fTraceGeneral)
    cerr <<
      endl <<
      idtr <<
        "The command line options and arguments have been analyzed" <<
        endl;

  // open output file if need be
  // ------------------------------------------------------

  ofstream outStream;

  if (outputFileName.size ()) {
    if (gGeneralOptions->fTraceGeneral)
      cerr << idtr <<
        "Opening file '" << outputFileName << "' for writing" <<
        endl;
        
    outStream.open (outputFileName.c_str(), ofstream::out);
  }
      
  // create MSR from MusicXML contents
  // ------------------------------------------------------

  S_msrScore mScore;

  if (inputFileName == "-") {
    // input comes from standard input
    if (outputFileName.size ())
      mScore =
        musicxmlFd2Msr (stdin, gMsrOptions, outStream);
    else
      mScore =
        musicxmlFd2Msr (stdin, gMsrOptions, cout);
  }
  
  else {
    // input comes from a file
    if (outputFileName.size ())
      mScore =
        musicxmlFile2Msr (
          inputFileName.c_str(), gMsrOptions, outStream);
    else
      mScore =
        musicxmlFile2Msr (
          inputFileName.c_str(), gMsrOptions, cout);
  }
    
  if (! mScore) {
    cerr <<
      "### Conversion from MusicCML to MSR failed ###" <<
      endl <<
      endl;
    return 1;
  }

  // create LPSR from MSR
  // ------------------------------------------------------

  S_lpsrScore lpScore;
        
  if (! gLilypondOptions->fNoLilypondCode) {
    if (outputFileName.size()) // ??? JMI
      lpScore =
        msr2Lpsr (mScore, gMsrOptions, gLpsrOptions, outStream);
    else
      lpScore =
        msr2Lpsr (mScore, gMsrOptions, gLpsrOptions, cout);
    
    if (! lpScore) {
      cerr <<
        "### Conversion from MSR to LPSR failed ###" <<
        endl <<
        endl;
      return 1;
    }
  }

  // generate LilyPond code from LPSR
  // ------------------------------------------------------

  if (! gLilypondOptions->fNoLilypondCode) {
    if (outputFileName.size ())
      lpsr2Lilypond (
        lpScore, gMsrOptions, gLpsrOptions, outStream);
    else
      lpsr2Lilypond (
        lpScore, gMsrOptions, gLpsrOptions, cout);
    
    if (outputFileName.size ()) {
      if (gGeneralOptions->fTraceGeneral)
        cerr <<
          endl <<
          idtr <<
            "Closing file '" << outputFileName << "'" <<
            endl;
          
      outStream.close ();
    }
  }

  // print timing information
  // ------------------------------------------------------

  if (gGeneralOptions->fDisplayCPUusage)
    timing::gTiming.print (cerr);
  

  // over!
  // ------------------------------------------------------

  if (! true) { // JMI
    cerr <<
      "### Conversion from LPSR to LilyPond code failed ###" <<
      endl <<
      endl;
    return 1;
  }

  return 0;
}

