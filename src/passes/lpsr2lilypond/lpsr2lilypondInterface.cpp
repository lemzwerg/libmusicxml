/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <fstream>      // ofstream, ofstream::open(), ofstream::close()

#include "messagesHandling.h"

#include "generalOah.h"

#include "enableTracingIfDesired.h"
#ifdef TRACING_IS_ENABLED
  #include "traceOah.h"
#endif

#include "lpsr2lilypondOah.h"

#include "lpsr2lilypondTranslator.h"

#include "lpsr2lilypondInterface.h"


using namespace std;

namespace MusicXML2
{

//_______________________________________________________________________________
void convertLpsrScoreToLilypondCode (
  const S_lpsrScore originalLpsrScore,
  S_msrOahGroup     msrOpts,
  S_lpsrOahGroup    lpsrOpts,
  string            passNumber,
  ostream&          lilypondCodeStream)
{
  // sanity check
  msgAssert (
    originalLpsrScore != nullptr,
    "originalLpsrScore is null");

  // start the clock
  clock_t startClock = clock ();

  string separator =
    "%--------------------------------------------------------------";

#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTracePasses ()) {
    gLogStream <<
      endl <<
      separator <<
      endl <<
      gTab <<
      passNumber << ": writing the LPSR as LilyPond code" <<
      endl <<
      separator <<
      endl;
  }
#endif

  // create an lpsr2lilypondTranslator
  lpsr2lilypondTranslator
    translator (
      originalLpsrScore,
      msrOpts,
      lpsrOpts,
      lilypondCodeStream);

  // generate the LilyPond code
  translator.generateLilypondCodeFromLpsrScore ();

  // register time spent
  clock_t endClock = clock ();

  timing::gGlobalTiming.appendTimingItem (
    passNumber,
    "Translate the LPSR into LilyPond code",
    timingItem::kMandatory,
    startClock,
    endClock);

  // check indentation
  if (gIndenter != 0) {
    gLogStream <<
      "### convertLpsrScoreToLilypondCode gIndenter final value: " <<
      gIndenter.getIndent () <<
      " ###" <<
      endl;

    gIndenter.resetToZero ();
  }
}


}