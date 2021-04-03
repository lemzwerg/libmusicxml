/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef ___msr2musicxmlInsiderOahGroup___
#define ___msr2musicxmlInsiderOahGroup___

#include "oahBasicTypes.h"

#include "oahInsiderHandlers.h"


namespace MusicXML2
{
//_______________________________________________________________________________
class EXP msr2musicxmlInsiderHandler : public oahInsiderHandler
{
  public:

    // creation
    // ------------------------------------------------------

    static SMARTP<msr2musicxmlInsiderHandler> create (
                            string executableName,
                            string handlerHeader);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

                          msr2musicxmlInsiderHandler (
                            string executableName,
                            string handlerHeader);

    virtual               ~msr2musicxmlInsiderHandler ();

  private:

    // private initialization
    // ------------------------------------------------------

    void                  createTheMsr2musicxmlPrefixes ();

    void                  createTheMsr2musicxmlOptionGroups (
                            string executableName);

  public:

    // public services
    // ------------------------------------------------------

    string                handlerExecutableAboutInformation () const override;

    void                  checkOptionsAndArgumentsFromArgcAndArgv () const override;

    string                fetchOutputFileNameFromTheOptions () const override;

    // quiet mode
    void                  enforceHandlerQuietness () override;

    // consistency check
    void                  checkHandlerOptionsConsistency () override;

  public:

    // visitors
    // ------------------------------------------------------

  public:

    // print
    // ------------------------------------------------------

    void                  print (ostream& os) const;

  private:

    // private fields
    // ------------------------------------------------------

    S_oahPrefix           fShortIgnoreRedundantPrefix;
    S_oahPrefix           fLongIgnoreRedundantPrefix;
};
typedef SMARTP<msr2musicxmlInsiderHandler> S_msr2musicxmlInsiderHandler;
EXP ostream& operator<< (ostream& os, const S_msr2musicxmlInsiderHandler& elt);

//______________________________________________________________________________
class EXP msr2musicxmlInsiderOahGroup : public oahGroup
{
  public:

    static SMARTP<msr2musicxmlInsiderOahGroup> create ();

  public:

    // initialisation
    // ------------------------------------------------------

    void                  initializeMsr2musicxmlInsiderOahGroup ();

  protected:

    // constructors/destructor
    // ------------------------------------------------------

                          msr2musicxmlInsiderOahGroup ();

    virtual               ~msr2musicxmlInsiderOahGroup ();

  public:

    // set and get
    // ------------------------------------------------------

    // quit after some passes
    void                  setQuitAfterPass2a ()
                              { fQuitAfterPass2a = true; }
    bool                  getQuitAfterPass2a () const
                              { return fQuitAfterPass2a; }

    void                  setQuitAfterPass2b ()
                              { fQuitAfterPass2b = true; }
    bool                  getQuitAfterPass2b () const
                              { return fQuitAfterPass2b; }

  public:

    // public services
    // ------------------------------------------------------

    // quiet mode
    void                  enforceGroupQuietness () override;

    // consistency check
    void                  checkGroupOptionsConsistency () override;

  public:

    // visitors
    // ------------------------------------------------------

    void                  acceptIn  (basevisitor* v) override;
    void                  acceptOut (basevisitor* v) override;

    void                  browseData (basevisitor* v) override;

  public:

    // print
    // ------------------------------------------------------

    void                  printMsr2musicxmlInsiderOahGroupHelp ();

    void                  printMsr2musicxmlInsiderOahGroupValues (unsigned int fieldWidth);

  private:

    // private services
    // ------------------------------------------------------

  private:

    // private fields
    // ------------------------------------------------------

    // quit after some passes
    bool                  fQuitAfterPass2a;
    bool                  fQuitAfterPass2b;
};
typedef SMARTP<msr2musicxmlInsiderOahGroup> S_msr2musicxmlInsiderOahGroup;
EXP ostream& operator<< (ostream& os, const S_msr2musicxmlInsiderOahGroup& elt);

EXP extern S_msr2musicxmlInsiderOahGroup gGlobalMsr2musicxmlInsiderOahGroup;

//______________________________________________________________________________
S_msr2musicxmlInsiderOahGroup createGlobalMsr2musicxmlOahGroup ();


}


#endif