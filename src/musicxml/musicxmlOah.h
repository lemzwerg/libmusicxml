/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef ___musicxmlOah___
#define ___musicxmlOah___

#include "oahBasicTypes.h"


namespace MusicXML2
{

//______________________________________________________________________________
class musicxmlOah : public oahGroup
{
  public:

    // creation
    // ------------------------------------------------------

    static SMARTP<musicxmlOah> create (
      S_oahHandler handlerUpLink);

    SMARTP<musicxmlOah>   createCloneWithDetailedTrace ();

  private:

    // initialisation
    // ------------------------------------------------------

    void                  initializeMusicxmlOah (
                            bool boolOptionsInitialValue);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

    musicxmlOah (
      S_oahHandler handlerUpLink);

    virtual ~musicxmlOah ();

  public:

    // quiet mode
    // ------------------------------------------------------

    void                  enforceQuietness ();

  public:

    // consistency check
    // ------------------------------------------------------

    virtual void          checkOptionsConsistency ();

  public:

    // set and get
    // ------------------------------------------------------

    void                  setAllMusicXMLTraceOah (
                            bool boolOptionsInitialValue);

  public:

    // public services
    // ------------------------------------------------------

  private:

    // private services
    // ------------------------------------------------------

#ifdef TRACE_OAH
    void                  initializeMusicxmlTraceOah (
                            bool boolOptionsInitialValue);
#endif

  public:

    // visitors
    // ------------------------------------------------------

    virtual void          acceptIn  (basevisitor* v);
    virtual void          acceptOut (basevisitor* v);

    virtual void          browseData (basevisitor* v);

  public:

    // print
    // ------------------------------------------------------

    void                  printMusicxmlHelp ();

    void                  printMusicxmlValues (int fieldWidth);

  public:

    // fields
    // ------------------------------------------------------

#ifdef TRACE_OAH
    // specific trace
    // --------------------------------------

    // encoding
    bool                  fTraceEncoding;

    // divisions
    bool                  fTraceDivisions;

    // backup
    bool                  fTraceBackup;

    // forward
    bool                  fTraceForward;
#endif
};
typedef SMARTP<musicxmlOah> S_musicxmlOah;
EXP ostream& operator<< (ostream& os, const S_musicxmlOah& elt);

EXP extern S_musicxmlOah gMusicxmlOah;
EXP extern S_musicxmlOah gMusicxmlOahUserChoices;
EXP extern S_musicxmlOah gMusicxmlOahWithDetailedTrace;

//______________________________________________________________________________
void initializeMusicxmlOahHandling (
  S_oahHandler handler);


}


#endif