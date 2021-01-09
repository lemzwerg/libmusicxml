#ifndef ___msrGraceNotes___
#define ___msrGraceNotes___

#include "msrElements.h"
#include "msrMeasures.h"
#include "msrMeasureElements.h"
#include "msrNotes.h"
#include "msrVoices.h"


namespace MusicXML2
{

//______________________________________________________________________________
class msrChord;
typedef SMARTP<msrChord> S_msrChord;

class msrMeasure;
typedef SMARTP<msrMeasure> S_msrMeasure;

class msrVoice;
typedef SMARTP<msrVoice> S_msrVoice;

class msrPart;
typedef SMARTP<msrPart> S_msrPart;

class msrNote;
typedef SMARTP<msrNote> S_msrNote;

//______________________________________________________________________________
class EXP msrGraceNotesGroup : public msrElement
{
  public:

    // data types
    // ------------------------------------------------------

    enum msrGraceNotesGroupKind {
      kGraceNotesGroupBefore,
      kGraceNotesGroupAfter
    };

    static string graceNotesGroupKindAsString (
      msrGraceNotesGroupKind graceNotesGroupKind);

    // creation from MusicXML
    // ------------------------------------------------------

    static SMARTP<msrGraceNotesGroup> create (
      int                    inputLineNumber,
      msrGraceNotesGroupKind graceNotesGroupKind,
      bool                   graceNotesGroupIsSlashed,
      bool                   graceNotesGroupIsBeamed,
      string                 graceNotesGroupMeasureNumber,
      S_msrVoice             graceNotesGroupVoiceUpLink);

    SMARTP<msrGraceNotesGroup> createGraceNotesGroupNewbornClone (
      S_msrVoice containingVoice);

    SMARTP<msrGraceNotesGroup> createSkipGraceNotesGroupClone (
      S_msrVoice containingVoice);

    SMARTP<msrGraceNotesGroup> createGraceNotesGroupDeepCopy (
      S_msrVoice containingVoice);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

    msrGraceNotesGroup (
      int                    inputLineNumber,
      msrGraceNotesGroupKind graceNotesGroupKind,
      bool                   graceNotesGroupIsSlashed,
      bool                   graceNotesGroupIsBeamed,
      string                 graceNotesGroupMeasureNumber,
      S_msrVoice             graceNotesGroupVoiceUpLink);

    virtual ~msrGraceNotesGroup ();

  public:

    // set and get
    // ------------------------------------------------------

    void                  setGraceNotesGroupNoteUpLink (
                            S_msrNote note)
                              { fGraceNotesGroupNoteUpLink = note; }

    S_msrNote             getGraceNotesGroupNoteUpLink () const
                              { return fGraceNotesGroupNoteUpLink; }

    S_msrVoice            getGraceNotesGroupVoiceUpLink () const
                              { return fGraceNotesGroupVoiceUpLink; }

    msrGraceNotesGroupKind
                          getGraceNotesGroupKind () const
                              { return fGraceNotesGroupKind; }

    void                  setGraceNotesGroupKind (
                            msrGraceNotesGroupKind graceNotesGroupKind)
                              { fGraceNotesGroupKind = graceNotesGroupKind; }

    const list<S_msrMeasureElement>&
                          getGraceNotesGroupElementsList () const
                              { return fGraceNotesGroupElementsList; }

    bool                  getGraceNotesGroupIsSlashed () const
                              { return fGraceNotesGroupIsSlashed; }

    void                  setGraceNotesGroupIsTied ()
                              { fGraceNotesGroupIsTied = true; }

    bool                  getGraceNotesGroupIsTied () const
                              { return fGraceNotesGroupIsTied; }

    void                  setGraceNotesGroupIsBeamed ()
                              { fGraceNotesGroupIsBeamed = true; }

    bool                  getGraceNotesGroupIsBeamed () const
                              { return fGraceNotesGroupIsBeamed; }

    void                  setGraceNotesGroupIsFollowedByNotes (bool value)
                              { fGraceNotesGroupIsFollowedByNotes = value; }

    bool                  getGraceNotesGroupIsFollowedByNotes () const
                              { return fGraceNotesGroupIsFollowedByNotes; }

    void                  setGraceNotesGroupMeasureNumber (
                            string measureNumber)
                              {
                                fGraceNotesGroupMeasureNumber = measureNumber;
                              }

    string                getGraceNotesGroupMeasureNumber () const
                              { return fGraceNotesGroupMeasureNumber; }

    // positions in measures
    void                  setGraceNotesGroupElementsPositionInMeasure (
                            S_msrMeasure measure,
                            rational     positionInMeasure);

  public:

    // public services
    // ------------------------------------------------------

    S_msrPart             fetchGraceNotesGroupPartUpLink () const;

    void                  appendNoteToGraceNotesGroup (S_msrNote note);
    void                  appendChordToGraceNotesGroup (S_msrChord chord);

    S_msrNote             removeLastNoteFromGraceNotesGroup (
                            int inputLineNumber);


  public:

    // visitors
    // ------------------------------------------------------

    void                  acceptIn  (basevisitor* v) override;
    void                  acceptOut (basevisitor* v) override;

    void                  browseData (basevisitor* v) override;

  public:

    // print
    // ------------------------------------------------------

    string                asShortString () const override;
    string                asString () const override;

    void                  print (ostream& os) const override;

    void                  printShort (ostream& os) const override;

  private:

    // private fields
    // ------------------------------------------------------

    // upLinks
    S_msrNote             fGraceNotesGroupNoteUpLink;
    S_msrVoice            fGraceNotesGroupVoiceUpLink;

    msrGraceNotesGroupKind
                          fGraceNotesGroupKind;

    list<S_msrMeasureElement>
                          fGraceNotesGroupElementsList;

    bool                  fGraceNotesGroupIsSlashed;
    bool                  fGraceNotesGroupIsTied;
    bool                  fGraceNotesGroupIsBeamed;

    bool                  fGraceNotesGroupIsFollowedByNotes;

    // LilyPond issue #34 may lead to add skip grace notes to voices
    // other than the one containing these grace notes:
    // the measure number is needed to create the first measure
    // in case the grace notes are at the beginning of the voice
    string                fGraceNotesGroupMeasureNumber; // JMI ???
};
typedef SMARTP<msrGraceNotesGroup> S_msrGraceNotesGroup;
EXP ostream& operator<< (ostream& os, const S_msrGraceNotesGroup& elt);


}


#endif