#ifndef ___bsrNotes___
#define ___bsrNotes___

#include "bsrLineContentsElements.h"

#include "bsrCellsLists.h"


namespace MusicXML2
{

//______________________________________________________________________________
enum class bsrNoteOctaveKind {
  kNoteOctaveNone,
  kNoteOctaveBelow1,
  kNoteOctave1,
  kNoteOctave2,
  kNoteOctave3,
  kNoteOctave4,
  kNoteOctave5,
  kNoteOctave6,
  kNoteOctave7,
  kNoteOctaveAbove7
};

extern string noteOctaveKindAsString (
  bsrNoteOctaveKind noteOctaveKind);

extern string noteOctaveKindAsDebugString (
  bsrNoteOctaveKind noteOctaveKind);

extern S_bsrCellsList noteOctaveKindAsCellsList (
  int               inputLineNumber,
  bsrNoteOctaveKind noteOctaveKind);

//______________________________________________________________________________
class EXP bsrNote : public bsrLineContentsElement
{
  public:

    // data types
    // ------------------------------------------------------

    enum bsrNoteValueKind {
      kNoteValueNone,

      kNoteValueRestBreve,
      kNoteValueRestWhole,
      kNoteValueRestHalf,
      kNoteValueRestQuarter,
      kNoteValueRest8th,
      kNoteValueRest16th,
      kNoteValueRest32nd,
      kNoteValueRest64th,
      kNoteValueRest128th,
      kNoteValueRest256th,

      kNoteValueCBreve,
      kNoteValueCWhole,
      kNoteValueCHalf,
      kNoteValueCQuarter,
      kNoteValueC8th,
      kNoteValueC16th,
      kNoteValueC32nd,
      kNoteValueC64th,
      kNoteValueC128th,
      kNoteValueC256th,

      kNoteValueDBreve,
      kNoteValueDWhole,
      kNoteValueDHalf,
      kNoteValueDQuarter,
      kNoteValueD8th,
      kNoteValueD16th,
      kNoteValueD32nd,
      kNoteValueD64th,
      kNoteValueD128th,
      kNoteValueD256th,

      kNoteValueEBreve,
      kNoteValueEWhole,
      kNoteValueEHalf,
      kNoteValueEQuarter,
      kNoteValueE8th,
      kNoteValueE16th,
      kNoteValueE32nd,
      kNoteValueE64th,
      kNoteValueE128th,
      kNoteValueE256th,

      kNoteValueFBreve,
      kNoteValueFWhole,
      kNoteValueFHalf,
      kNoteValueFQuarter,
      kNoteValueF8th,
      kNoteValueF16th,
      kNoteValueF32nd,
      kNoteValueF64th,
      kNoteValueF128th,
      kNoteValueF256th,

      kNoteValueGBreve,
      kNoteValueGWhole,
      kNoteValueGHalf,
      kNoteValueGQuarter,
      kNoteValueG8th,
      kNoteValueG16th,
      kNoteValueG32nd,
      kNoteValueG64th,
      kNoteValueG128th,
      kNoteValueG256th,

      kNoteValueABreve,
      kNoteValueAWhole,
      kNoteValueAHalf,
      kNoteValueAQuarter,
      kNoteValueA8th,
      kNoteValueA16th,
      kNoteValueA32nd,
      kNoteValueA64th,
      kNoteValueA128th,
      kNoteValueA256th,

      kNoteValueBBreve,
      kNoteValueBWhole,
      kNoteValueBHalf,
      kNoteValueBQuarter,
      kNoteValueB8th,
      kNoteValueB16th,
      kNoteValueB32nd,
      kNoteValueB64th,
      kNoteValueB128th,
      kNoteValueB256th
    };

    static string noteValueKindAsString (
      bsrNoteValueKind noteValueKind);

    static string noteValueKindAsDebugString (
      bsrNoteValueKind noteValueKind);

    static S_bsrCellsList noteValueKindAsCellsList (
      int              inputLineNumber,
      bsrNoteValueKind noteValueKind);

    enum bsrNoteValueSizeKind {
      kNoteValueSizeNone,
      kNoteValueSizeLarger,
      kNoteValueSizeSmaller
    };

    static string noteValueSizeKindAsString (
      bsrNoteValueSizeKind noteValueSizeKind);

    static bsrNoteValueSizeKind noteValueSizeKindFromNoteValueKind (
      bsrNoteValueKind noteValueKind);

    static S_bsrCellsList noteValueSizeKindAsCellsList (
      int                  inputLineNumber,
      bsrNoteValueSizeKind noteValueSizeKind);

    enum bsrNoteOctaveIsNeeded {
      kNoteOctaveIsNeededYes, kNoteOctaveIsNeededNo
    };

    static string noteOctaveIsNeededAsString (
      bsrNoteOctaveIsNeeded noteOctaveIsNeeded);

    enum class bsrAccidentalKind {
      kAccidentalNone,
      kAccidentalSharp, kAccidentalNatural, kAccidentalFlat,
      kAccidentalDoubleFlat, kAccidentalDoubleSharp,
      kAccidentalQuarterSharp, kAccidentalQuarterFlat,
      kAccidentalThreeQuarterSharp, kAccidentalThreeQuarterFlat
    };

    static string msrAccidentalKindAsString (
      bsrAccidentalKind accidentalKind);

    static string accidentalKindAsDebugString (
      bsrAccidentalKind accidentalKind);

    static S_bsrCellsList accidentalKindAsCellsList (
      int                   inputLineNumber,
      bsrAccidentalKind accidentalKind);

    // creation
    // ------------------------------------------------------

    static SMARTP<bsrNote> create (
                            int                   inputLineNumber,
                            bsrNoteValueKind      noteValueKind,
                            int                   noteDotsNumber,
                            bsrNoteOctaveKind     noteOctaveKind,
                            bsrNoteOctaveIsNeeded noteOctaveIsNeeded,
                            bsrAccidentalKind accidentalKind);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

                          bsrNote (
                            int                   inputLineNumber,
                            bsrNoteValueKind      noteValueKind,
                            int                   noteDotsNumber,
                            bsrNoteOctaveKind     noteOctaveKind,
                            bsrNoteOctaveIsNeeded noteOctaveIsNeeded,
                            bsrAccidentalKind accidentalKind);

    virtual               ~bsrNote ();

  public:

    // set and get
    // ------------------------------------------------------

    bsrNoteValueKind      getNoteValueKind () const
                              { return fNoteValueKind; }

    int                   getNoteDotsNumber () const
                              { return fNoteDotsNumber; }

    void                  setNoteValueSizeIsNeeded ()
                              { fNoteValueSizeIsNeeded = true; }

    bool                  getNoteValueSizeIsNeeded () const
                              { return fNoteValueSizeIsNeeded; }

    void                  setNoteOctaveIsNeeded (
                            bsrNoteOctaveIsNeeded value)
                              { fNoteOctaveIsNeeded = value; }

    bsrNoteOctaveIsNeeded getNoteOctaveIsNeeded () const
                              { return fNoteOctaveIsNeeded; }

    bsrAccidentalKind getAccidentalKind () const
                              { return fAccidentalKind; }

   public:

    // public services
    // ------------------------------------------------------

    S_bsrCellsList        fetchCellsList () const override
                              { return buildCellsList (); }

    int                   fetchCellsNumber () const override;

  private:

    // private services
    // ------------------------------------------------------

    S_bsrCellsList        noteValueKindAsCellsList () const;

    S_bsrCellsList        noteValueSizeKindAsCellsList () const;

    S_bsrCellsList        accidentalKindAsCellsList () const;

    S_bsrCellsList        buildCellsList () const;

  public:

    // visitors
    // ------------------------------------------------------

    void                  acceptIn  (basevisitor* v) override;
    void                  acceptOut (basevisitor* v) override;

    void                  browseData (basevisitor* v) override;

  public:

    // print
    // ------------------------------------------------------

    string                asString () const override;

    string                asShortString () const override;

    string                asDebugString () const override;

    void                  print (ostream& os) const override;

  private:

    // private fields
    // ------------------------------------------------------


    bsrNoteValueKind      fNoteValueKind;
    int                   fNoteDotsNumber;

    bool                  fNoteValueSizeIsNeeded;

    bsrNoteOctaveKind     fNoteOctaveKind;
    bsrNoteOctaveIsNeeded fNoteOctaveIsNeeded;

    bsrAccidentalKind     fAccidentalKind;
};
typedef SMARTP<bsrNote> S_bsrNote;
EXP ostream& operator<< (ostream& os, const S_bsrNote& elt);


}


#endif
