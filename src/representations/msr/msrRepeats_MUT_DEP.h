/*
  This file is to be included only by msr_MUTUAL_DEPENDENCIES.h,
  to satisfy declarations mutual dependencies.
*/

#ifndef ___msrRepeats_MUT_DEP___
#define ___msrRepeats_MUT_DEP___

#include "msrElements.h"
#include "msrMeasuresRepeats_MUT_DEP.h"
#include "msrNotes_MUT_DEP.h"
#include "msrRestMeasures_MUT_DEP.h"
#include "msrVoiceElements.h"


namespace MusicXML2
{

//______________________________________________________________________________
// pre-declaration
class msrRepeat;
typedef SMARTP<msrRepeat> S_msrRepeat;

class msrRestMeasures;
typedef SMARTP<msrRestMeasures> S_msrRestMeasures;

class msrMeasuresRepeat;
typedef SMARTP<msrMeasuresRepeat> S_msrMeasuresRepeat;

class msrNote;
typedef SMARTP<msrNote> S_msrNote;

//______________________________________________________________________________
class EXP msrRepeatCommonPart : public msrElement
{
  public:

    // creation from MusicXML
    // ------------------------------------------------------

    static SMARTP<msrRepeatCommonPart> create (
      int         inputLineNumber,
      S_msrRepeat repeatUpLink);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

    msrRepeatCommonPart (
      int         inputLineNumber,
      S_msrRepeat repeatUpLink);

    virtual ~msrRepeatCommonPart ();

  public:

    // set and get
    // ------------------------------------------------------

    // upLinks
    S_msrRepeat           getRepeatCommonPartRepeatUpLink () const
                              { return fRepeatCommonPartRepeatUpLink; }

    // elements
    const list<S_msrVoiceElement>&
                          getRepeatCommonPartElementsList () const
                              { return fRepeatCommonPartElementsList; }

  public:

    // public services
    // ------------------------------------------------------

    void                  appendVoiceElementToRepeatCommonPart (
                            int               inputLineNumber,
                            S_msrVoiceElement voiceElement,
                            string            context);

    void                  appendSegmentToRepeatCommonPart (
                            int          inputLineNumber,
                            S_msrSegment segment,
                            string       context);

    void                  appendRepeatToRepeatCommonPart (
                            int          inputLineNumber,
                            S_msrRepeat  repeat,
                            string       context);

    void                  appendMeasuresRepeatToRepeatCommonPart (
                            int                 inputLineNumber,
                            S_msrMeasuresRepeat measuresRepeat,
                            string              context);

    void                  appendRestMeasuresToRepeatCommonPart (
                            int               inputLineNumber,
                            S_msrRestMeasures restMeasures,
                            string            context);

    S_msrNote             fetchRepeatCommonPartFirstNonGraceNote () const;

    void                  collectRepeatCommonPartMeasuresIntoFlatList (
                            int inputLineNumber);

  public:

    // visitors
    // ------------------------------------------------------

    virtual void          acceptIn  (basevisitor* v) override;
    virtual void          acceptOut (basevisitor* v) override;

    virtual void          browseData (basevisitor* v) override;

  public:

    // print
    // ------------------------------------------------------

    string                asString () const override;

    virtual void          print (ostream& os) const override;

    virtual void          printShort (ostream& os) const override;

  private:

    // private fields
    // ------------------------------------------------------

    // upLinks
    S_msrRepeat           fRepeatCommonPartRepeatUpLink;

    // elements list
    list<S_msrVoiceElement>
                          fRepeatCommonPartElementsList;
};
typedef SMARTP<msrRepeatCommonPart> S_msrRepeatCommonPart;
EXP ostream& operator<< (ostream& os, const S_msrRepeatCommonPart& elt);

//______________________________________________________________________________
class EXP msrRepeatEnding : public msrElement
{
  public:

    // creation from MusicXML
    // ------------------------------------------------------

    static SMARTP<msrRepeatEnding> create (
      int                 inputLineNumber,
      string              repeatEndingNumber, // may be "1, 2"
      msrRepeatEndingKind repeatEndingKind,
      S_msrRepeat         repeatUpLink);

    /* JMI
    SMARTP<msrRepeatEnding> createRepeatEndingNewbornClone (
      S_msrRepeat containingRepeat);
      */

  protected:

    // constructors/destructor
    // ------------------------------------------------------

    msrRepeatEnding (
      int                 inputLineNumber,
      string              repeatEndingNumber, // may be "1, 2"
      msrRepeatEndingKind repeatEndingKind,
      S_msrRepeat         repeatUpLink);

    virtual ~msrRepeatEnding ();

  public:

    // set and get
    // ------------------------------------------------------

    // upLinks
    S_msrRepeat           getRepeatEndingRepeatUpLink () const
                              { return fRepeatEndingRepeatUpLink; }

    // numbers
    string                getRepeatEndingNumber () const
                              { return fRepeatEndingNumber; }

    void                  setRepeatEndingNumber (int repeatEndingNumber)
                              { fRepeatEndingNumber = repeatEndingNumber; }

    void                  setRepeatEndingInternalNumber (
                            int repeatEndingInternalNumber)
                              {
                                fRepeatEndingInternalNumber =
                                  repeatEndingInternalNumber;
                              }

    int                   getRepeatEndingInternalNumber () const
                              { return fRepeatEndingInternalNumber; }

    // kind
    msrRepeatEndingKind   getRepeatEndingKind () const
                              { return fRepeatEndingKind; }

    // elements
    const list<S_msrVoiceElement>&
                          getRepeatEndingElementsList () const
                              { return fRepeatEndingElementsList; }

  public:

    // public services
    // ------------------------------------------------------

    void                  appendVoiceElementToRepeatEnding ( // JMI
                            int               inputLineNumber,
                            S_msrVoiceElement voiceElement,
                            string            context);

    void                  appendSegmentToRepeatEnding (
                            int          inputLineNumber,
                            S_msrSegment segment,
                            string       context);

    void                  appendRepeatToRepeatEnding (
                            int          inputLineNumber,
                            S_msrRepeat  repeat,
                            string       context);

    void                  appendMeasuresRepeatToRepeatEnding (
                            int                 inputLineNumber,
                            S_msrMeasuresRepeat measuresRepeat,
                            string              context);

    void                  appendRestMeasuresToRepeatEnding (
                            int                       inputLineNumber,
                            S_msrRestMeasures restMeasures,
                            string                    context);

    void                  collectRepeatEndingMeasuresIntoFlatList (
                            int inputLineNumber);

  public:

    // visitors
    // ------------------------------------------------------

    virtual void          acceptIn  (basevisitor* v) override;
    virtual void          acceptOut (basevisitor* v) override;

    virtual void          browseData (basevisitor* v) override;

  public:

    // print
    // ------------------------------------------------------

    string                asString () const override;

    virtual void          print (ostream& os) const override;

    virtual void          printShort (ostream& os) const override;

  private:

    // private fields
    // ------------------------------------------------------

    // upLinks
    S_msrRepeat           fRepeatEndingRepeatUpLink;

    // numbers
    string                fRepeatEndingNumber; // may be "1, 2"
    int                   fRepeatEndingInternalNumber; // internally assigned

    // kind
    msrRepeatEndingKind   fRepeatEndingKind;

    // elements list
    list<S_msrVoiceElement>
                          fRepeatEndingElementsList;
};
typedef SMARTP<msrRepeatEnding> S_msrRepeatEnding;
EXP ostream& operator<< (ostream& os, const S_msrRepeatEnding& elt);

//______________________________________________________________________________
class EXP msrRepeat : public msrVoiceElement
{
  public:

    // data types
    // ------------------------------------------------------

    enum msrRepeatExplicitStartKind {
      kRepeatExplicitStartNo,
      kRepeatExplicitStartYes
    };

    static string repeatExplicitStartKindAsString (
      msrRepeatExplicitStartKind repeatExplicitStartKind);

    enum msrRepeatBuildPhaseKind {
      kRepeatBuildPhaseJustCreated,
      kRepeatBuildPhaseInCommonPart,
      kRepeatBuildPhaseInEndings,
      kRepeatBuildPhaseCompleted
    };

    static string repeatBuildPhaseKindAsString (
      msrRepeatBuildPhaseKind repeatBuildPhaseKind);

    // creation from MusicXML
    // ------------------------------------------------------

    static SMARTP<msrRepeat> create (
      int        inputLineNumber,
      int        repeatTimes,
      S_msrVoice voiceUpLink);

    SMARTP<msrRepeat> createRepeatNewbornClone (
      S_msrVoice containingVoice);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

    msrRepeat (
      int        inputLineNumber,
      int        repeatTimes,
      S_msrVoice voiceUpLink);

    virtual ~msrRepeat ();

  public:

    // set and get
    // ------------------------------------------------------

    // upLinks
    S_msrVoice            getRepeatVoiceUpLink () const
                              { return fRepeatVoiceUpLink; }
    // times
    int                   getRepeatTimes () const
                              { return fRepeatTimes; }

    void                  setRepeatTimes (int repeatTimes) // JMI
                              { fRepeatTimes = repeatTimes; }

    // explicit start?
    void                  setRepeatExplicitStartKind (
                            msrRepeatExplicitStartKind repeatExplicitStartKind)
                              {
                                fRepeatExplicitStartKind =
                                  repeatExplicitStartKind;
                              }

    msrRepeatExplicitStartKind
                          getRepeatExplicitStartKind () const
                              { return fRepeatExplicitStartKind; }

    // common part
    void                  setRepeatCommonPart (
                            S_msrRepeatCommonPart repeatCommonPart);

    S_msrRepeatCommonPart getRepeatCommonPart () const
                              { return fRepeatCommonPart; }

    // endings
    const vector<S_msrRepeatEnding>&
                          getRepeatEndings () const
                              { return fRepeatEndings; }

    // immediately preceding and following repeats
    void                  setImmediatelyPrecedingRepeat (
                            S_msrRepeat precedingRepeat)
                              { fImmediatelyPrecedingRepeat = precedingRepeat; }

    S_msrRepeat           getImmediatelyPrecedingRepeat () const
                              { return fImmediatelyPrecedingRepeat; }

    void                  setImmediatelyFollowingRepeat (
                            S_msrRepeat followingRepeat)
                              { fImmediatelyFollowingRepeat = followingRepeat; }

    S_msrRepeat           getImmediatelyFollowingRepeat () const
                              { return fImmediatelyFollowingRepeat; }

  public:

    // public services
    // ------------------------------------------------------

    void                  addRepeatEndingToRepeat (
                            int               inputLineNumber,
                            S_msrRepeatEnding repeatEnding);

    void                  appendSegmentToRepeat (
                            int          inputLineNumber,
                            S_msrSegment segment,
                            string       context);

    void                  appendRepeatToRepeat (
                            int         inputLineNumber,
                            S_msrRepeat repeat,
                            string      context);

    void                  appendMeasuresRepeatToRepeat (
                            int                 inputLineNumber,
                            S_msrMeasuresRepeat measuresRepeat,
                            string              context);

    void                  appendRestMeasuresToRepeat (
                            int                       inputLineNumber,
                            S_msrRestMeasures restMeasures,
                            string                    context);

    S_msrNote             fetchRepeatFirstNonGraceNote () const;

    void                  collectRepeatMeasuresIntoFlatList (
                            int inputLineNumber);

  public:

    // visitors
    // ------------------------------------------------------

    virtual void          acceptIn  (basevisitor* v) override;
    virtual void          acceptOut (basevisitor* v) override;

    virtual void          browseData (basevisitor* v) override;

  public:

    // print
    // ------------------------------------------------------

    string                asShortString () const override;
    string                asString () const override;

    void                  displayRepeat (
                            int    inputLineNumber,
                            string context);

    virtual void          print (ostream& os) const override;

    virtual void          printShort (ostream& os) const override;

  private:

    // private fields
    // ------------------------------------------------------

    // upLinks
    S_msrVoice            fRepeatVoiceUpLink;

    // number of repetitions
    int                   fRepeatTimes;

    // explicit start?
    msrRepeatExplicitStartKind
                          fRepeatExplicitStartKind;

    // common part
    S_msrRepeatCommonPart fRepeatCommonPart;

    // repeat endings
    vector<S_msrRepeatEnding>
                          fRepeatEndings;
    int                   fRepeatEndingsInternalCounter;

    // immediately preceding and following repeats
    // detecting several repeats in a row helps LilyPond code generation
    // depending on the options JMI
    S_msrRepeat           fImmediatelyPrecedingRepeat;
    S_msrRepeat           fImmediatelyFollowingRepeat;

  public:

    // public work services
    // ------------------------------------------------------

    // repeat build phase
    void                  setCurrentRepeatBuildPhaseKind (
                            msrRepeatBuildPhaseKind repeatBuildPhaseKind)
                              {
                                fCurrentRepeatBuildPhaseKind =
                                  repeatBuildPhaseKind;
                              }

    msrRepeatBuildPhaseKind
                          getCurrentRepeatBuildPhaseKind () const
                            { return fCurrentRepeatBuildPhaseKind; }

  private:

    // private work services
    // ------------------------------------------------------

  private:

    // work fields
    // ------------------------------------------------------

    // repeat build phase, used when building the repeat JMI ???
    msrRepeatBuildPhaseKind
                          fCurrentRepeatBuildPhaseKind;
};
typedef SMARTP<msrRepeat> S_msrRepeat;
EXP ostream& operator<< (ostream& os, const S_msrRepeat& elt);

//________________________________________________________________________
class EXP msrRepeatDescr : public smartable
{
  public:

    // creation
    // ------------------------------------------------------

    static SMARTP<msrRepeatDescr> create (
      int         repeatDescrStartInputLineNumber,
      S_msrRepeat repeatDescrRepeat);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

    msrRepeatDescr (
      int         repeatDescrStartInputLineNumber,
      S_msrRepeat fRepeatDescrRepeat);

    virtual ~msrRepeatDescr ();

  public:

    // set and get
    // ------------------------------------------------------

    S_msrRepeat           getRepeatDescrRepeat () const
                              { return fRepeatDescrRepeat; }

    void                  setRepeatDescrStartInputLineNumber (
                            int inputLineNumber)
                              {
                                fRepeatDescrStartInputLineNumber =
                                  inputLineNumber;
                              }

    int                   getRepeatDescrStartInputLineNumber () const
                              {
                                return
                                  fRepeatDescrStartInputLineNumber;
                              }

  public:

    // public services
    // ------------------------------------------------------

    string                repeatDescrAsString () const;

    // print
    // ------------------------------------------------------

    virtual void          print (ostream& os) const;

  private:

    // private fields
    // ------------------------------------------------------

    // the repeat
    S_msrRepeat           fRepeatDescrRepeat;

    // its start input line number
    int                   fRepeatDescrStartInputLineNumber;
};
typedef SMARTP<msrRepeatDescr> S_msrRepeatDescr;
EXP ostream& operator<< (ostream& os, const S_msrRepeatDescr& elt);


}


#endif

//______________________________________________________________________________
/* JMI
class EXP msrRepeatElement : public msrElement
{
  public:

    // creation from MusicXML
    // ------------------------------------------------------

    static SMARTP<msrRepeatElement> create (
      int          inputLineNumber,
      S_msrRepeat  repeatUpLink);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

    msrRepeatElement (
      int          inputLineNumber,
      S_msrRepeat  repeatUpLink);

    virtual ~msrRepeatElement ();

  public:

    // set and get
    // ------------------------------------------------------

    // upLinks
    S_msrRepeat           getRepeatElementRepeatUpLink () const
                              { return fRepeatElementRepeatUpLink; }

    // elements
    const list<S_msrVoiceElement>&
                          getRepeatElementElementsList () const
                              { return fRepeatElementElementsList; }

  public:

    // public services
    // ------------------------------------------------------

    void                  appendSegmentToRepeatElementsList (
                            int          inputLineNumber,
                            S_msrSegment segment,
                            string       context);

    void                  appendRepeatToRepeatElementsList (
                            int          inputLineNumber,
                            S_msrRepeat  repeat,
                            string       context);

    void                  appendMeasuresRepeatToRepeatElementsList (
                            int                 inputLineNumber,
                            S_msrMeasuresRepeat measuresRepeat,
                            string              context);

    void                  appendRestMeasuresToRepeatElementsList (
                            int                 inputLineNumber,
                            S_msrMeasuresRepeat measuresRepeat,
                            string              context);

    S_msrNote             fetchRepeatElementFirstNonGraceNote () const;

    void                  collectRepeatElementMeasuresIntoFlatList (
                            int inputLineNumber);

  private:

    // private services
    // ------------------------------------------------------

    void                  appendVoiceElementToRepeatElementsList ( // JMI
                            int               inputLineNumber,
                            S_msrVoiceElement voiceElement,
                            string            context);

  public:

    // visitors
    // ------------------------------------------------------

    virtual void          acceptIn  (basevisitor* v) override;
    virtual void          acceptOut (basevisitor* v) override;

    virtual void          browseData (basevisitor* v) override;

  public:

    // print
    // ------------------------------------------------------

    string                asString () const override;

    virtual void          print (ostream& os) const override;

    virtual void          printShort (ostream& os) const override;

  private:

    // private fields
    // ------------------------------------------------------

    // upLinks
    S_msrRepeat           fRepeatElementRepeatUpLink;

    // elements list
    list<S_msrVoiceElement>
                          fRepeatElementElementsList;
};
typedef SMARTP<msrRepeatElement> S_msrRepeatElement;
EXP ostream& operator<< (ostream& os, const S_msrRepeatElement& elt);
*/

