/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef ___bsrScores___
#define ___bsrScores___

#include <sstream>
#include <string>
#include <list>

#include "msrScores.h"

#include "bsrElements.h"
#include "bsrPages.h"
#include "bsrTranscriptionNotes.h"

#include "bsrOah.h"


namespace MusicXML2
{

//______________________________________________________________________________
class EXP bsrScore : public bsrElement
{
  public:

    // creation
    // ------------------------------------------------------

    static SMARTP<bsrScore> create (
                            int            inputLineNumber,
                            S_msrScore     theMsrScore);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

                          bsrScore (
                            int            inputLineNumber,
                            S_msrScore     theMsrScore);

    virtual               ~bsrScore ();

  public:

    // set and get
    // ------------------------------------------------------

    S_msrScore            getMsrScore () const
                              { return fMsrScore; }

    S_bsrTranscriptionNotes
                          getTranscriptionNotes () const
                              { return fTranscriptionNotes; }

    unsigned int          getBrailleLineLength () const
                              { return fBrailleLineLength; }

    unsigned int          getBraillePageLength () const
                              { return fBraillePageLength; }

  public:

    // public services
    // ------------------------------------------------------

    void                  appendPageToScore (S_bsrPage page)
                              { fScorePagesList.push_back (page); }

    void                  appendTranscriptionNotesElementToScore ( // JMI
                            S_bsrTranscriptionNotesElement
                              transcriptionNotesElement)
                              {
                                fTranscriptionNotes->
                                  appendElementToTranscriptionNotes (
                                    transcriptionNotesElement);
                              }

  private:

    // private services
    // ------------------------------------------------------

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

  private:

    // private fields
    // ------------------------------------------------------

    // MSR data
    S_msrScore            fMsrScore;

    S_bsrTranscriptionNotes
                          fTranscriptionNotes;

    unsigned int          fBrailleLineLength; // cells JMI ???
    unsigned int          fBraillePageLength;

    list<S_bsrPage>       fScorePagesList;
};
typedef SMARTP<bsrScore> S_bsrScore;
EXP ostream& operator<< (ostream& os, const S_bsrScore& score);


}


#endif
