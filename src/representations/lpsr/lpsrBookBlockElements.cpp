/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include "lpsrBookBlockElements.h"

#include "version.h"

#include "enableTracingIfDesired.h"
#ifdef TRACING_IS_ENABLED
  #include "traceOah.h"
#endif

#include "oahOah.h"
#include "generalOah.h"

#include "lpsrOah.h"
#include "lpsr2lilypondOah.h"

using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
S_lpsrBookBlockElement lpsrBookBlockElement::create (
  int inputLineNumber)
{
  lpsrBookBlockElement* o = new lpsrBookBlockElement (
    inputLineNumber);
  assert (o!=0);
  return o;
}

lpsrBookBlockElement::lpsrBookBlockElement (
  int inputLineNumber)
    : lpsrElement (inputLineNumber)
{
  // create the book block element parallel music
  fBookBlockElementParallelMusicBlock =
    lpsrParallelMusicBLock::create (
      inputLineNumber,
      lpsrParallelMusicBLock::kEndOfLine);
}

lpsrBookBlockElement::~lpsrBookBlockElement ()
{}

void lpsrBookBlockElement::acceptIn (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrBookBlockElement::acceptIn ()" <<
      endl;
  }
#endif

  if (visitor<S_lpsrBookBlockElement>*
    p =
      dynamic_cast<visitor<S_lpsrBookBlockElement>*> (v)) {
        S_lpsrBookBlockElement elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
          gLogStream <<
            "% ==> Launching lpsrBookBlockElement::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void lpsrBookBlockElement::acceptOut (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrBookBlockElement::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_lpsrBookBlockElement>*
    p =
      dynamic_cast<visitor<S_lpsrBookBlockElement>*> (v)) {
        S_lpsrBookBlockElement elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
          gLogStream <<
            "% ==> Launching lpsrBookBlockElement::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void lpsrBookBlockElement::browseData (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrBookBlockElement::browseData ()" <<
      endl;
  }
#endif

  {
    // browse the book block element parallel music
    msrBrowser<lpsrParallelMusicBLock> browser (v);
    browser.browse (*fBookBlockElementParallelMusicBlock);
  }

/* JMI
  for (
    vector<S_msrElement>::const_iterator i = fBlockElements.begin ();
    i != fBlockElements.end ();
    i++
  ) {
    // browse the element
 //   msrBrowser<msrElement> browser (v);
 //   browser.browse (*(*i));
  } // for
*/

#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% <== lpsrBookBlockElement::browseData ()" <<
      endl;
  }
#endif
}

void lpsrBookBlockElement::print (ostream& os) const
{
  // will never be called since it is overridden in subclasses
}

ostream& operator<< (ostream& os, const S_lpsrBookBlockElement& scr)
{
  scr->print (os);
  return os;
}

//______________________________________________________________________________
S_lpsrScoreBlock lpsrScoreBlock::create (
  int inputLineNumber)
{
  lpsrScoreBlock* o = new lpsrScoreBlock (
    inputLineNumber);
  assert (o!=0);
  return o;
}

lpsrScoreBlock::lpsrScoreBlock (
  int inputLineNumber)
    : lpsrBookBlockElement (inputLineNumber)
{
  // create the score block parallel music block
  fBookBlockElementParallelMusicBlock =
    lpsrParallelMusicBLock::create (
      inputLineNumber,
      lpsrParallelMusicBLock::kEndOfLine);

  // create the score block layout?
  if (true || gGlobalLpsr2lilypondOahGroup->getCreateTopLevelLayoutBlock ()) {
    fScoreBlockLayout =
      lpsrLayout::create (
        inputLineNumber);
  }

  /*
  // create the score block midi tempo
  string midiTempoDuration  = gGlobalLpsr2lilypondOahGroup->getMidiTempo ().first; // BLARK JMI ???
  int    midiTempoPerSecond = gGlobalLpsr2lilypondOahGroup->getMidiTempo ().second;

  fScoreBlockMidiTempo =
    msrMidiTempo::create (
      inputLineNumber,
      midiTempoDuration,
      midiTempoPerSecond);
      */
  // create the score block midi tempo
  fScoreBlockMidiTempo = // options for this ???
    gGlobalLpsr2lilypondOahGroup->
      getMidiTempo ().
        createMsrMidiTempoNewbornClone ();
}

lpsrScoreBlock::~lpsrScoreBlock ()
{}

void lpsrScoreBlock::appendPartGroupBlockToScoreBlock (
  S_lpsrPartGroupBlock partGroupBlock)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTracePartGroups ()) {
    gLogStream <<
      "Appending part group block " <<
       partGroupBlock-> getPartGroup ()-> getPartGroupCombinedName () <<
       " to LPSR score block" <<
       endl;
  }
#endif

  fBookBlockElementParallelMusicBlock->
    appendPartGroupBlockToParallelMusicBLock (
      partGroupBlock);

//               fBlockElements.push_back(partGroupBlock);
}

/* JMI
void lpsrScoreBlock::appendVoiceUseToParallelMusicBLock (
  S_lpsrUseVoiceCommand voiceUse)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceVoices ()) {
    gLogStream <<
      "Appending the use of voice \"" <<
       voiceUse-> getVoice ()-> getVoiceName () <<
       "\" to LPSR score" <<
       endl;
  }
#endif

  fBookBlockElementParallelMusicBlock->
    addElementToParallelMusicBLock (voiceUse);

//     JMI             fBlockElements.push_back(voiceUse);
}

void lpsrScoreBlock::appendLyricsUseToParallelMusicBLock (
  S_lpsrNewLyricsBlock lyricsUse)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceLyrics ()) {
    gLogStream <<
      "Appending the use of stanza " <<
       lyricsUse-> getStanza ()-> getStanzaName () <<
       " to LPSR score" <<
       endl;
  }
#endif

  fBookBlockElementParallelMusicBlock->
    addElementToParallelMusicBLock (lyricsUse);
}
*/

void lpsrScoreBlock::acceptIn (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrScoreBlock::acceptIn ()" <<
      endl;
  }
#endif

  if (visitor<S_lpsrScoreBlock>*
    p =
      dynamic_cast<visitor<S_lpsrScoreBlock>*> (v)) {
        S_lpsrScoreBlock elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
          gLogStream <<
            "% ==> Launching lpsrScoreBlock::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void lpsrScoreBlock::acceptOut (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrScoreBlock::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_lpsrScoreBlock>*
    p =
      dynamic_cast<visitor<S_lpsrScoreBlock>*> (v)) {
        S_lpsrScoreBlock elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
          gLogStream <<
            "% ==> Launching lpsrScoreBlock::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void lpsrScoreBlock::browseData (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrScoreBlock::browseData ()" <<
      endl;
  }
#endif

  {
    // browse the score block parallel music
    msrBrowser<lpsrParallelMusicBLock> browser (v);
    browser.browse (*fBookBlockElementParallelMusicBlock);
  }

/* JMI
  for (
    vector<S_msrElement>::const_iterator i = fBlockElements.begin ();
    i != fBlockElements.end ();
    i++
  ) {
    // browse the element
 //   msrBrowser<msrElement> browser (v);
 //   browser.browse (*(*i));
  } // for
*/

  if (fScoreBlockLayout) {
    // browse the score block layout
    msrBrowser<lpsrLayout> browser (v);
    browser.browse (*fScoreBlockLayout);
  }

  if (fScoreBlockMidiTempo) {
    msrBrowser<msrMidiTempo> browser (v);
    browser.browse (*fScoreBlockMidiTempo);
  }

#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% <== lpsrScoreBlock::browseData ()" <<
      endl;
  }
#endif
}

void lpsrScoreBlock::print (ostream& os) const
{
  os << "ScoreBlock" << endl << endl;

  gIndenter++;

  os <<
    fBookBlockElementParallelMusicBlock <<
    endl;

  if (fScoreBlockLayout) {
    os <<
      fScoreBlockLayout <<
      endl;
  }

  os <<
    fScoreBlockMidiTempo <<
    endl;

  gIndenter--;
}

ostream& operator<< (ostream& os, const S_lpsrScoreBlock& scr)
{
  scr->print (os);
  return os;
}

//______________________________________________________________________________
S_lpsrBookPartBlock lpsrBookPartBlock::create (
  int inputLineNumber)
{
  lpsrBookPartBlock* o = new lpsrBookPartBlock (
    inputLineNumber);
  assert (o!=0);
  return o;
}

lpsrBookPartBlock::lpsrBookPartBlock (
  int            inputLineNumber)
    : lpsrBookBlockElement (inputLineNumber)
{
  // create the bookpart block parallel music
  fBookBlockElementParallelMusicBlock =
    lpsrParallelMusicBLock::create (
      inputLineNumber,
      lpsrParallelMusicBLock::kEndOfLine);
}

lpsrBookPartBlock::~lpsrBookPartBlock ()
{}

void lpsrBookPartBlock::appendPartGroupBlockToBookPartBlock (
  S_lpsrPartGroupBlock partGroupBlock)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTracePartGroups ()) {
    gLogStream <<
      "Appending part group block " <<
       partGroupBlock-> getPartGroup ()-> getPartGroupCombinedName () <<
       " to LPSR book part block" <<
       endl;
  }
#endif

  fBookBlockElementParallelMusicBlock->
    appendPartGroupBlockToParallelMusicBLock (
      partGroupBlock);

//               fBlockElements.push_back(partGroupBlock);
}

/* JMI
void lpsrBookPartBlock::appendVoiceUseToParallelMusicBLock (
  S_lpsrUseVoiceCommand voiceUse)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceVoices ()) {
    gLogStream <<
      "Appending the use of voice \"" <<
       voiceUse-> getVoice ()-> getVoiceName () <<
       "\" to LPSR score" <<
       endl;
  }
#endif

  fBookBlockElementParallelMusicBlock->
    addElementToParallelMusicBLock (voiceUse);

//     JMI             fBlockElements.push_back(voiceUse);
}

void lpsrBookPartBlock::appendLyricsUseToParallelMusicBLock (
  S_lpsrNewLyricsBlock lyricsUse)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceLyrics ()) {
    gLogStream <<
      "Appending the use of stanza " <<
       lyricsUse-> getStanza ()-> getStanzaName () <<
       " to LPSR score" <<
       endl;
  }
#endif

  fBookBlockElementParallelMusicBlock->
    addElementToParallelMusicBLock (lyricsUse);
}
*/

void lpsrBookPartBlock::acceptIn (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrBookPartBlock::acceptIn ()" <<
      endl;
  }
#endif

  if (visitor<S_lpsrBookPartBlock>*
    p =
      dynamic_cast<visitor<S_lpsrBookPartBlock>*> (v)) {
        S_lpsrBookPartBlock elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
          gLogStream <<
            "% ==> Launching lpsrBookPartBlock::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void lpsrBookPartBlock::acceptOut (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrBookPartBlock::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_lpsrBookPartBlock>*
    p =
      dynamic_cast<visitor<S_lpsrBookPartBlock>*> (v)) {
        S_lpsrBookPartBlock elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
          gLogStream <<
            "% ==> Launching lpsrBookPartBlock::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void lpsrBookPartBlock::browseData (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrBookPartBlock::browseData ()" <<
      endl;
  }
#endif

  {
    // browse the bookpart block parallel music
    msrBrowser<lpsrParallelMusicBLock> browser (v);
    browser.browse (*fBookBlockElementParallelMusicBlock);
  }

#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% <== lpsrBookPartBlock::browseData ()" <<
      endl;
  }
#endif
}

void lpsrBookPartBlock::print (ostream& os) const
{
  os << "BookPartBlock" << endl << endl;

  gIndenter++;

  os <<
    fBookBlockElementParallelMusicBlock <<
    endl;

  gIndenter--;
}

ostream& operator<< (ostream& os, const S_lpsrBookPartBlock& scr)
{
  scr->print (os);
  return os;
}

//______________________________________________________________________________
S_lpsrBookBlock lpsrBookBlock::create (
  int inputLineNumber)
{
  lpsrBookBlock* o = new lpsrBookBlock (
    inputLineNumber);
  assert (o!=0);
  return o;
}

lpsrBookBlock::lpsrBookBlock (
  int inputLineNumber)
    : lpsrElement (inputLineNumber)
{
  /* JMI
  // create the score block element parallel music
  fBookBlockElementParallelMusicBlock =
    lpsrParallelMusicBLock::create (
      inputLineNumber,
      lpsrParallelMusicBLock::kEndOfLine);
*/

  // create the book block element header
  fBookBlockHeader =
    lpsrHeader::create (
      inputLineNumber);

  // don't create the book block element paper
  // it will be created as a new born clone of the the one in the lpsrScore
  // when the scaling is handled in visitStart (S_msrScaling&)
}

lpsrBookBlock::~lpsrBookBlock ()
{}

/* JMI
void lpsrBookBlock::appendPartGroupBlockToBlock (
  S_lpsrPartGroupBlock partGroupBlock)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTracePartGroups ()) {
    gLogStream <<
      "Appending part group block " <<
       partGroupBlock-> getPartGroup ()-> getPartGroupCombinedName () <<
       " to LPSR score" <<
       endl;
  }
#endif

  fBookBlockElementParallelMusicBlock->
    appendPartGroupBlockToParallelMusicBLock (
      partGroupBlock);

//               fBlockElements.push_back(partGroupBlock);
}
*/

void lpsrBookBlock::appendBookBlockElementToBookBlockElementsList (
  S_lpsrBookBlockElement bookBlockElement)
{
/* JMI
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrBlocks ()) {
    gLogStream <<
      "Appending book block element  " <<
       bookBlockElement-> asString () <<
       " to LPSR book block" <<
       endl;
  }
#endif
*/
  fBookBlockElementsList.push_back (
      bookBlockElement);
}

void lpsrBookBlock::appendLpsrScoreBlockToBookBlockElementsList (
  S_lpsrScoreBlock scoreBlock)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrBlocks ()) {
    gLogStream <<
      "Appending score block element  " <<
       scoreBlock-> asString () <<
       " to LPSR book block elements list" <<
       endl;
  }
#endif

  appendBookBlockElementToBookBlockElementsList (
      scoreBlock);
}

void lpsrBookBlock::appendLpsrBookPartBlockToBookBlockElementsList (
  S_lpsrBookPartBlock bookPartBlock)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrBlocks ()) {
    gLogStream <<
      "Appending book part block element  " <<
       bookPartBlock-> asString () <<
       " to LPSR book block elements list" <<
       endl;
  }
#endif

  appendBookBlockElementToBookBlockElementsList (
      bookPartBlock);
}

/* JMI
void lpsrBookBlock::appendVoiceUseToParallelMusicBLock (
  S_lpsrUseVoiceCommand voiceUse)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceVoices ()) {
    gLogStream <<
      "Appending the use of voice \"" <<
       voiceUse-> getVoice ()-> getVoiceName () <<
       "\" to LPSR score" <<
       endl;
  }
#endif

  fBookBlockElementParallelMusicBlock->
    addElementToParallelMusicBLock (voiceUse);

//     JMI             fBlockElements.push_back(voiceUse);
}

void lpsrBookBlock::appendLyricsUseToParallelMusicBLock (
  S_lpsrNewLyricsBlock lyricsUse)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalTraceOahGroup->getTraceLyrics ()) {
    gLogStream <<
      "Appending the use of stanza " <<
       lyricsUse-> getStanza ()-> getStanzaName () <<
       " to LPSR score" <<
       endl;
  }
#endif

  fBookBlockElementParallelMusicBlock->
    addElementToParallelMusicBLock (lyricsUse);
}
*/

void lpsrBookBlock::acceptIn (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrBookBlock::acceptIn ()" <<
      endl;
  }
#endif

  if (visitor<S_lpsrBookBlock>*
    p =
      dynamic_cast<visitor<S_lpsrBookBlock>*> (v)) {
        S_lpsrBookBlock elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
          gLogStream <<
            "% ==> Launching lpsrBookBlock::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void lpsrBookBlock::acceptOut (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrBookBlock::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_lpsrBookBlock>*
    p =
      dynamic_cast<visitor<S_lpsrBookBlock>*> (v)) {
        S_lpsrBookBlock elem = this;

#ifdef TRACING_IS_ENABLED
        if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
          gLogStream <<
            "% ==> Launching lpsrBookBlock::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void lpsrBookBlock::browseData (basevisitor* v)
{
#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% ==> lpsrBookBlock::browseData ()" <<
      endl;
  }
#endif

  if (fBookBlockHeader) {
    // browse the book block header
    msrBrowser<lpsrHeader> browser (v);
    browser.browse (*fBookBlockHeader);
  }

  for (
    list<S_lpsrBookBlockElement>::const_iterator i = fBookBlockElementsList.begin ();
    i != fBookBlockElementsList.end ();
    i++
  ) {
    // browse block the element
    msrBrowser<lpsrBookBlockElement> browser (v);
    browser.browse (*(*i));
  } // for

  if (fBookBlockPaper) {
    // browse the book block paper
    msrBrowser<lpsrPaper> browser (v);
    browser.browse (*fBookBlockPaper);
  }

#ifdef TRACING_IS_ENABLED
  if (gGlobalLpsrOahGroup->getTraceLpsrVisitors ()) {
    gLogStream <<
      "% <== lpsrBookBlock::browseData ()" <<
      endl;
  }
#endif
}

void lpsrBookBlock::print (ostream& os) const
{
  os << "BookBlock" << endl << endl;

  gIndenter++;

  if (fBookBlockHeader) {
    os <<
      fBookBlockHeader <<
      endl;
  }

  os <<
    "BookBlockElements";

  if (fBookBlockElementsList.size ()) {
    os << endl;

    gIndenter++;

    for (
      list<S_lpsrBookBlockElement>::const_iterator i = fBookBlockElementsList.begin ();
      i != fBookBlockElementsList.end ();
      i++
    ) {
      // print the book block element
      os << (*i);
    } // for

    gIndenter--;
  }
  else {
    os <<
      " : none" <<
      endl;
  }

  if (fBookBlockPaper) {
    os <<
      fBookBlockPaper <<
      endl;
  }

  gIndenter--;
}

ostream& operator<< (ostream& os, const S_lpsrBookBlock& scr)
{
  scr->print (os);
  return os;
}


}