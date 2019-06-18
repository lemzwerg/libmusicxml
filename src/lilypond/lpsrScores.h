/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef ___lpsrScores___
#define ___lpsrScores___

/*
#include <sstream>
#include <vector>
#include <string>
#include <list>


#include "exports.h"
#include "typedefs.h"

#include "msrBasicTypes.h"


#include "lpsrVarValAssocs.h"

#include "lpsrScheme.h"
*/

#include "lpsrComments.h"

#include "lpsrScheme.h"

#include "lpsrHeaders.h"
#include "lpsrPapers.h"
#include "lpsrLayouts.h"

#include "lpsrParallelMusic.h"
#include "lpsrVarValAssocs.h"

#include "lpsrBookBlockElements.h"

#include "msrScores.h"

#include "msrMidi.h"


namespace MusicXML2
{


//______________________________________________________________________________
class lpsrScore : public lpsrElement
{
  public:

    // creation from MusicXML
    // ------------------------------------------------------

    static SMARTP<lpsrScore> create (
      int        inputLineNumber,
      S_msrScore mScore);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

    lpsrScore (
      int        inputLineNumber,
      S_msrScore mScore);

    virtual ~lpsrScore ();

  public:

    // set and get
    // ------------------------------------------------------

    S_msrScore            getMsrScore () const
                              { return fMsrScore; }

    S_lpsrVarValAssoc
                          getLilypondVersion () const
                              { return fLilypondVersion; }

    S_lpsrSchemeVariable
                          getScoreGlobalStaffSizeVariable () const
                              { return fScoreGlobalStaffSizeVariable; }

    S_lpsrHeader          getScoreHeader () const
                              { return fScoreHeader; }

    S_lpsrPaper           getScorePaper () const
                              { return fScorePaper; }

    S_lpsrLayout          getScoreLayout () const
                              { return fScoreLayout; }

    const list<S_msrElement>&
                          getScoreElementsList () const
                              { return fScoreElementsList; }

    const list<S_lpsrBookBlock>&
                          getScoreBookBlocksList () const
                              { return fScoreBookBlocksList; }

    S_lpsrScoreBlock      getScoreScoreBlock () const
                              { return fScoreScoreBlock; }

    void                  setGlobalStaffSize (float size);

    // files includes
    // ---------------------

    void                  setJianpuFileIncludeIsNeeded ();

    bool                  getJianpuFileIncludeIsNeeded () const
                              { return fJianpuFileIncludeIsNeeded; }

    // Scheme modules
    // ---------------------

    void                  setScmAndAccregSchemeModulesAreNeeded ();

    bool                  getScmAndAccregSchemeModulesAreNeeded () const
                              { return fScmAndAccregSchemeModulesAreNeeded; }

    // Scheme functions
    // ---------------------

    // custom short bar lines
    void                  setCustomShortBarLineSchemeFunctionIsNeeded ();

    bool                  getCustomShortBarLineSchemeFunctionIsNeeded () const
                              { return fCustomShortBarLineSchemeFunctionIsNeeded; }

    // tongue
    void                  setTongueSchemeFunctionIsNeeded ();

    bool                  getTongueSchemeFunctionIsNeeded () const
                              { return fTongueSchemeFunctionIsNeeded; }


    // editorial accidentals
    void                  setEditorialAccidentalSchemeFunctionIsNeeded ();

    bool                  getEditorialAccidentalSchemeFunctionIsNeeded () const
                              {
                                return
                                  fEditorialAccidentalSchemeFunctionIsNeeded;
                              }

    // dynamics
    void                  setDynamicsSchemeFunctionIsNeeded ();

    bool                  getDynamicsSchemeFunctionIsNeeded () const
                              {
                                return
                                  fDynamicsSchemeFunctionIsNeeded;
                              }

    // tuplets curved brackets
    void                  setTupletsCurvedBracketsSchemeFunctionIsNeeded ();

    bool                  getTupletsCurvedBracketsSchemeFunctionIsNeeded () const
                              {
                                return
                                  fTupletsCurvedBracketsSchemeFunctionIsNeeded;
                              }

    // after
    void                  setAfterSchemeFunctionIsNeeded ();

    bool                  getAfterSchemeFunctionIsNeeded () const
                              {
                                return
                                  fAfterSchemeFunctionIsNeeded;
                              }

    // tempo relationships
    void                  setTempoRelationshipSchemeFunctionIsNeeded ();

    // glissando with text
    void                  setGlissandoWithTextSchemeFunctionIsNeeded ();

    // damps
    void                  setDampMarkupIsNeeded ();

    void                  setDampAllMarkupIsNeeded ();

    // white note heads
    void                  setWhiteNoteHeadsIsNeeded ();

    // jazz chords display
    void                  setJazzChordsDisplayIsNeeded ();

  public:

    // public services
    // ------------------------------------------------------

    void                  appendVoiceToScoreElementsList (
                            S_msrVoice voice)
                              { fScoreElementsList.push_back (voice); }

    void                  appendStanzaToScoreElementsList (
                            S_msrStanza stanza)
                              { fScoreElementsList.push_back (stanza); }

    void                  addGlissandoWithTextSchemeFunctionsToScore ();

    void                  appendBookBlockToBookBlocksList (
                            S_lpsrBookBlock bookBlock)
                              { fScoreBookBlocksList.push_back (bookBlock); }

  private:

    // private services
    // ------------------------------------------------------

    // files includes

    void                  addJianpuFileIncludeToScore ();

    // Scheme modules

    void                  addAccordionRegistrationSchemeModulesToScore ();

    // Scheme functions

    void                  addDateAndTimeSchemeFunctionsToScore ();

    void                  addPointAndClickOffSchemeFunctionsToScore ();

    void                  addCustomShortBarLineSchemeFunctionToScore ();

    void                  addTongueSchemeFunctionToScore ();

    void                  addEditorialAccidentalSchemeFunctionToScore ();

    void                  addDynamicsSchemeFunctionToScore ();

    void                  addTupletsCurvedBracketsSchemeFunctionToScore ();

    void                  addAfterSchemeFunctionToScore ();

    void                  addTempoRelationshipSchemeFunctionToScore ();

    // markups

    void                  addDampMarkupToScore ();
    void                  addDampAllMarkupToScore ();

    // white note heads

    void                  addWhiteNoteHeadsToScore ();

    // jazz chords display

    void                  addJazzChordsDisplayToScore ();

  public:

    // visitors
    // ------------------------------------------------------

    virtual void          acceptIn  (basevisitor* v);
    virtual void          acceptOut (basevisitor* v);

    virtual void          browseData (basevisitor* v);

  public:

    // print
    // ------------------------------------------------------

    virtual void          print (ostream& os);

  private:

    // fields
    // ------------------------------------------------------

    // MSR data
    S_msrScore            fMsrScore;

    // general information
    S_lpsrVarValAssoc     fLilypondVersion;

    S_lpsrComment         fInputSourceNameComment;
    S_lpsrComment         fTranslationDateComment;
    S_lpsrComment         fCommandLineLongOptionsComment;
    S_lpsrComment         fCommandLineShortOptionsComment;

    S_lpsrSchemeVariable  fScoreGlobalStaffSizeVariable;

    S_lpsrHeader          fScoreHeader;
    S_lpsrPaper           fScorePaper;
    S_lpsrLayout          fScoreLayout;

    // to keep the original line breaks
    S_lpsrVarValAssoc     fMyBreakIsBreakAssoc;
    S_lpsrVarValAssoc     fMyBreakIsEmptyAssoc;

    // to keep the original page breaks
    S_lpsrVarValAssoc     fMyPageBreakIsPageBreakAssoc;
    S_lpsrVarValAssoc     fMyPageBreakIsEmptyAssoc;

    // to generate 'global' variable
    S_lpsrVarValAssoc     fScoreGlobalAssoc;

    // variables, voices and stanzas
    list<S_msrElement>    fScoreElementsList;

    // score LPSR book blocks list
    list<S_lpsrBookBlock> fScoreBookBlocksList;
    S_lpsrScoreBlock      fScoreScoreBlock; // JMI ???

    // files includes
    bool                  fJianpuFileIncludeIsNeeded;

    // Scheme modules
    bool                  fScmAndAccregSchemeModulesAreNeeded;

    // Scheme functions
    bool                  fTongueSchemeFunctionIsNeeded;
    bool                  fCustomShortBarLineSchemeFunctionIsNeeded;
    bool                  fEditorialAccidentalSchemeFunctionIsNeeded;
    bool                  fDynamicsSchemeFunctionIsNeeded;
    bool                  fTupletsCurvedBracketsSchemeFunctionIsNeeded;
    bool                  fAfterSchemeFunctionIsNeeded;
    bool                  fTempoRelationshipSchemeFunctionIsNeeded;
    bool                  fGlissandoWithTextSchemeFunctionIsNeeded;

    // markups
    bool                  fDampMarkupIsNeeded;
    bool                  fDampAllMarkupIsNeeded;

    // white note heads
    bool                  fWhiteNoteHeadsIsNeeded;

    // jazz chords display
    bool                  fJazzChordsDisplayIsNeeded;

    map<string, S_lpsrSchemeFunction>
                          fScoreSchemeFunctionsMap;
};
typedef SMARTP<lpsrScore> S_lpsrScore;
EXP ostream& operator<< (ostream& os, const S_lpsrScore& elt);


}


#endif
