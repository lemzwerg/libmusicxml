/*
  MusicXML Library
  Copyright (C) Grame 2006-2020

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef __musicxml2lilypond__
#define __musicxml2lilypond__

using namespace std;

namespace MusicXML2
{

//_______________________________________________________________________________
EXP xmlErr convertMusicXMLToLilypond (
  string inputSourceName,
  string outputFileName,
  bool   loopBackToMusicXML); // loopBackToMusicXML is used by 'xml2ly -loop'

}

#endif
