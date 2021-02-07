/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef ___msrScores___
#define ___msrScores___

#include <iostream>

#include <list>
#include <set>

#include "msrElements.h"

#include "msrCredits.h"
#include "msrIdentification.h"
#include "msrScaling.h"
#include "msrMusicXMLSpecifics.h"
#include "msrPartGroups.h"
#include "msrVoices.h"


namespace MusicXML2
{

//______________________________________________________________________________
class msrPart;
typedef SMARTP<msrPart> S_msrPart;

class msrPartGroup;
typedef SMARTP<msrPartGroup> S_msrPartGroup;

class msrVoice;
typedef SMARTP<msrVoice> S_msrVoice;

//______________________________________________________________________________
class EXP msrScore : public msrElement
{
  public:

    // creation from MusicXML
    // ------------------------------------------------------

    static SMARTP<msrScore> create (
                            int inputLineNumber);

    SMARTP<msrScore> createScoreNewbornClone ();

  protected:

    // constructors/destructor
    // ------------------------------------------------------

                          msrScore (
                            int inputLineNumber);

    virtual               ~msrScore ();

  public:

    // set and get
    // ------------------------------------------------------

    // identification
    void                  setIdentification (
                            S_msrIdentification identification)
                              { fIdentification = identification; }
    S_msrIdentification   getIdentification () const
                              { return fIdentification; }

    // scaling
    void                  setScaling (
                            S_msrScaling scaling)
                              { fScaling = scaling; }

    S_msrScaling          getScaling () const
                              { return fScaling; }

    // page layout
    void                  setPageLayout (
                            S_msrPageLayout pageLayout)
                              { fPageLayout = pageLayout; }

    S_msrPageLayout       getPageLayout () const
                              { return fPageLayout; }

    // system layout
    void                  setSystemLayout (
                            S_msrSystemLayout systemLayout)
                              { fSystemLayout = systemLayout; }

    S_msrSystemLayout     getSystemLayout () const
                              { return fSystemLayout; }

    // staff layout

    void                  setStaffLayout (
                            S_msrStaffLayout staffLayout)
                              { fStaffLayout = staffLayout; }

    S_msrStaffLayout      getStaffLayout () const
                              { return fStaffLayout; }

    // appearance

    void                  setAppearance (
                            S_msrAppearance appearance)
                              { fAppearance = appearance; }

    S_msrAppearance       getAppearance () const
                              { return fAppearance; }

    // part groups
    const list<S_msrPartGroup>&
                          getPartGroupsList () const
                              { return fPartGroupsList; }

//* JMI
    // master voice
    void                  setScoreMasterVoice (
                            S_msrVoice masterVoice);

    S_msrVoice            getScoreMasterVoice () const;

/* JMI
    void                  setScoreMasterVoice (
                            S_msrVoice masterVoice)
                              { fScoreMasterVoice = masterVoice; }

    S_msrVoice            getScoreMasterVoice () const
                              { return fScoreMasterVoice; }
*/

    // credits
    const list<S_msrCredit>&
                          getCreditsList () const
                              { return fCreditsList; }

    // measures
    void                  setScoreNumberOfMeasures (
                            int scoreNumberOfMeasures)
                              {
                                fScoreNumberOfMeasures =
                                  scoreNumberOfMeasures;
                              }

    unsigned int          getScoreNumberOfMeasures () const
                              { return fScoreNumberOfMeasures; }

    void                  setStaffContainsRestMeasures (
                            bool staffContainsRestMeasures)
                              {
                                fStaffContainsRestMeasures =
                                  staffContainsRestMeasures;
                              }

    bool                  getStaffContainsRestMeasures () const
                              { return fStaffContainsRestMeasures; }

    // part group names max length
    void                  setScorePartGroupNamesMaxLength (int value)
                              { fScorePartGroupNamesMaxLength = value; }

    unsigned int          getScorePartGroupNamesMaxLength () const
                              { return fScorePartGroupNamesMaxLength; }

    // part names max length
    void                  setScorePartNamesMaxLength (int value)
                              { fScorePartNamesMaxLength = value; }

    unsigned int          getScorePartNamesMaxLength () const
                              { return fScorePartNamesMaxLength; }

    // instrument names max lengthes
    void                  setScoreInstrumentNamesMaxLength (int value)
                              { fScoreInstrumentNamesMaxLength = value; }

    unsigned int          getScoreInstrumentNamesMaxLength () const
                              { return fScoreInstrumentNamesMaxLength; }

    void                  setScoreInstrumentAbbreviationsMaxLength (int value)
                              { fScoreInstrumentAbbreviationsMaxLength = value; }

    unsigned int          getScoreInstrumentAbbreviationsMaxLength () const
                              { return fScoreInstrumentAbbreviationsMaxLength; }

    // inhibiting browsing
    void                  setInhibitGraceNotesGroupsBeforeBrowsing ()
                              {
                                fInhibitGraceNotesGroupsBeforeBrowsing = true;
                              }

    bool                  getInhibitGraceNotesGroupsBeforeBrowsing () const
                              {
                                return
                                  fInhibitGraceNotesGroupsBeforeBrowsing;
                              };

    void                  setInhibitGraceNotesGroupsAfterBrowsing ()
                              {
                                fInhibitGraceNotesGroupsAfterBrowsing = true;
                              }

    bool                  getInhibitGraceNotesGroupsAfterBrowsing () const
                              {
                                return
                                  fInhibitGraceNotesGroupsAfterBrowsing;
                              };

    void                  setInhibitChordsInGraceNotesGroupsBrowsing ()
                              {
                                fInhibitChordsInGraceNotesGroupsBrowsing = true;
                              }

    bool                  getInhibitChordsInGraceNotesGroupsBrowsing () const
                              {
                                return
                                  fInhibitChordsInGraceNotesGroupsBrowsing;
                              };

    void                  setInhibitTupletsInGraceNotesGroupsBrowsing ()
                              {
                                fInhibitTupletsInGraceNotesGroupsBrowsing = true;
                              }

    bool                  getInhibitTupletsInGraceNotesGroupsBrowsing () const
                              {
                                return
                                  fInhibitTupletsInGraceNotesGroupsBrowsing;
                              };

    void                  setInhibitMeasuresRepeatReplicasBrowsing ()
                              {
                                fInhibitMeasuresRepeatReplicasBrowsing = true;
                              }

    bool                  getInhibitMeasuresRepeatReplicasBrowsing () const
                              {
                                return
                                  fInhibitMeasuresRepeatReplicasBrowsing;
                              };

    void                  setInhibitRestMeasuresBrowsing ()
                              {
                                fInhibitRestMeasuresBrowsing = true;
                              }

    bool                  getInhibitRestMeasuresBrowsing () const
                              {
                                return
                                  fInhibitRestMeasuresBrowsing;
                              };

    // voices

    void                  registerVoiceInScoreAllVoicesList (
                            S_msrVoice voice);

  public:

    // public services
    // ------------------------------------------------------

    void                  addPartGroupToScore (
                            S_msrPartGroup partGroup);

    void                  appendCreditToScore (
                            S_msrCredit credit);

    S_msrPart             fetchPartFromScoreByItsPartID (
                            int    inputLineNumber,
                            string partID);

    void                  fetchIdentificationFromCreditsIfAny (
                            int inputLineNumber);

/* JMI
    void                  setHeaderFromOptionsIfAny (
                            int inputLineNumber);
*/

    void                  collectScorePartsList (
                            int    inputLineNumber,
                            list<S_msrPart>& partsList);

  public:

    // visitors
    // ------------------------------------------------------

    void                  acceptIn  (basevisitor* v) override;
    void                  acceptOut (basevisitor* v) override;

    void                  browseData (basevisitor* v) override;

  public:

    // print
    // ------------------------------------------------------

    void                  print (ostream& os) const override;

    void                  printShort (ostream& os) const override;

    void                  printSummary (ostream& os) const override;

  private:

    // private fields
    // ------------------------------------------------------

    // identification
    S_msrIdentification   fIdentification;

    // scaling
    S_msrScaling          fScaling;

    // layout
    S_msrPageLayout       fPageLayout;

    S_msrSystemLayout     fSystemLayout;

    S_msrStaffLayout      fStaffLayout;

    // appearance
    S_msrAppearance       fAppearance;

    // credits
    list<S_msrCredit>     fCreditsList;

    // part groups
    set<S_msrPartGroup>   fScorePartGroupsSet;

    list<S_msrPartGroup>  fPartGroupsList;

    // master voice

// JMI
    S_msrVoice            fScoreMasterVoice;

    // number of measures

    unsigned int          fScoreNumberOfMeasures;

    // rest measures

    bool                  fStaffContainsRestMeasures;

    // part group names max length

    unsigned int          fScorePartGroupNamesMaxLength;

    // part names max length

    unsigned int          fScorePartNamesMaxLength;

    // instrument names max lengthes

    unsigned int          fScoreInstrumentNamesMaxLength;
    unsigned int          fScoreInstrumentAbbreviationsMaxLength;

    // inhibiting browsing

    // grace notes groups before are handled at the note level,
    // and should be not be browsed afterwards
    bool                  fInhibitGraceNotesGroupsBeforeBrowsing;
    bool                  fInhibitGraceNotesGroupsAfterBrowsing;

    bool                  fInhibitChordsInGraceNotesGroupsBrowsing;

    // not relevant, since there are not tuplets in grace notes groups ??? JMI
    bool                  fInhibitTupletsInGraceNotesGroupsBrowsing;

    // in <measure-repeat/>, the measure replicas are explicit,
    // whereas LilyPond only needs the repeated measure
    bool                  fInhibitMeasuresRepeatReplicasBrowsing;

    // in <multiple-rest/>, the rest measures are explicit,
    // whereas LilyPond only needs the number of rest measures
    bool                  fInhibitRestMeasuresBrowsing;

    // voices

    list<S_msrVoice>      fScoreAllVoicesList;
};
typedef SMARTP<msrScore> S_msrScore;
EXP ostream& operator<< (ostream& os, const S_msrScore& elt);


}

#endif
