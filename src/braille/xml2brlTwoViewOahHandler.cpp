/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <iomanip>      // setw, setprecision, ...

#include "setTraceOahIfDesired.h"
#ifdef TRACE_OAH
  #include "traceOah.h"
#endif

#include "utilities.h"
#include "messagesHandling.h"

// JMI #include "oahTwoViewHandlers.h"

#include "xml2brlFullViewOahHandler.h"

#include "xml2brlTwoViewOahHandler.h"


using namespace std;

namespace MusicXML2
{

//#define OAH_TESTS

/*
//______________________________________________________________________________
string oahTwoViewHandlerViewKindAsString (
  oahTwoViewHandlerViewKind twoViewHandlerViewKind)
{
  string result;

  switch (twoViewHandlerViewKind) {
    case kViewFullView:
      return "kViewFullView";
      break;
    case kViewAlternate:
      return "kViewAlternate";
      break;
  }

  return result;
}
*/
//______________________________________________________________________________
S_xml2brlTwoViewOahHandler xml2brlTwoViewOahHandler::create (
  string   executableName,
  ostream& os)
{
  xml2brlTwoViewOahHandler* o = new
    xml2brlTwoViewOahHandler (
      executableName,
      os);
  assert(o!=0);

  return o;
}

xml2brlTwoViewOahHandler::xml2brlTwoViewOahHandler (
  string   executableName,
  ostream& os)
  : oahTwoViewHandler (
      "xml2brlTwoViewOahHandler",
      executableName,
      "full view",
      "",
      os)
{
  createTheTwoHandlers (os);
}

xml2brlTwoViewOahHandler::~xml2brlTwoViewOahHandler ()
{}

void xml2brlTwoViewOahHandler::createTheTwoHandlers (
  ostream& os)
{
#ifdef TRACE_OAH
#ifdef OAH_TESTS
  gLogOstream <<
    "Creating the two OAH handlers for \"" << fTwoViewHandlerName << "\"" <<
    endl;
#endif
#endif

  gIndenter++;

  // create the 'full view' handler
#ifdef TRACE_OAH
#ifdef OAH_TESTS
  gLogOstream <<
    "Creating the full view handler for \"" << fTwoViewHandlerName << "\"" <<
    endl;
#endif
#endif

  fFullViewOahHandler =
    xml2brlFullViewOahHandler::create (
      fExecutableName,
      fExecutableName + " 'full view' help",
      os);

  // create the 'user' handler
#ifdef TRACE_OAH
#ifdef OAH_TESTS
  gLogOstream <<
    "Creating the user handler for \"" << fTwoViewHandlerName << "\"" <<
    endl;
#endif
#endif

  fAlternateViewOahHandler =
    xml2brlFullViewOahHandler::createWithOnlyThePrefixes (
      fExecutableName,
      fExecutableName + " 'user' help",
      os);

  // create the user handler groups
  createAlternateHandlerGroups (os);

  // populate the user handler from the full view handler
  populateAlternateViewHandlerFromFullViewHandler ();

  // register user handler in itself,
  // so that the 'global' help options can be handled
  fAlternateViewOahHandler->
    registerHandlerInItself ();

  // the default is to use the 'user' oahHandler
  fOahHandlerToBeUsed = fAlternateViewOahHandler;

#ifdef TRACE_OAH
#ifdef OAH_TESTS
  gLogOstream <<
    "Setting twoView handler \"" <<
    fTwoViewHandlerName <<
    "\" handler to \"" <<
    fOahHandlerToBeUsed->getHandlerHeader () <<
    "\"" <<
    endl;
#endif
#endif

  gIndenter--;
}

void xml2brlTwoViewOahHandler::createAlternateHandlerGroups (
  ostream& os)
{
#ifdef TRACE_OAH
#ifdef OAH_TESTS
  gLogOstream <<
    "Creating the user handler groups for \"" << fTwoViewHandlerName << "\"" <<
    endl;
#endif
#endif

  createOahAlternateGroup (os);

  createInformationsAlternateGroup (os);

  createWarningAndErrorsAlternateGroup (os);

  createFilesAlternateGroup (os);

  createInputAlternateGroup (os);

  createPartsAlternateGroup (os);
  createStavesAlternateGroup (os);
  createVoicesAlternateGroup (os);

  createTranspositionsAlternateGroup (os);

  createClefsAlternateGroup (os);
  createKeysAlternateGroup (os);
  createTimesAlternateGroup (os);

  createRepeatsAlternateGroup (os);

  createMeasuresAlternateGroup (os);

  createRestsAlternateGroup (os);
  createNotesAlternateGroup (os);

  creatBeamsAlternateGroup (os);

  createArticulationsAlternateGroup (os);

  createOrnamentsAlternateGroup (os);

  createGraceNotesAlternateGroup (os);

  createChordsAlternateGroup (os);

  createTiesAlternateGroup (os);
  createSlursAlternateGroup (os);
  createLigaturesAlternateGroup (os);

  createDynamicsAlternateGroup (os);
  createWedgesAlternateGroup (os);

  createTupletsAlternateGroup (os);

  createLyricsAlternateGroup (os);

  createStringsAlternateGroup (os);

  createTablaturesAlternateGroup (os);

  createHarmoniesAlternateGroup (os);

  createFiguredBassesAlternateGroup (os);

  createOutputAlternateGroup (os);
}

void xml2brlTwoViewOahHandler::createOahAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Options and help group",
        "hoah-grp",
        "help-oah-grp",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  group->
    setGroupHeaderIsToBeWritten (false);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Options and help",
        "hoah",
        "help-oah",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

/* JMI ???
  // the 'full view' atom

  S_oahTwoViewHandlerFullViewAtom
    twoViewHandlerFullViewAtom =
      oahTwoViewHandlerFullViewAtom::create (
          fTwoViewAtomShortName, fFullViewAtomLongName,
R"(In the default 'user' view, the options are grouped by music scoring topics,
such a slurs, tuplets and figured bass.
This option switches the options and help view to 'full view',
in which the options are grouped as they are used by the various
internal representations and translation passes.
This unleashes the full set of display and trace options.
This option should be the first one.)");

  subGroup->
    appendAtomToSubGroup (twoViewHandlerFullViewAtom);
*/

    /*
  twoViewHandlerFullViewAtom ->
    registerAtomInHandler (fAlternateViewOahHandler);

 fAlternateViewOahHandler->
    registerElementInHandler (
      twoViewHandlerFullViewAtom);

  fAlternateViewOahHandler->
    registerSpecificElementNamesInHandler (
      twoViewHandlerFullViewAtom);
      */

  // atoms

  fAtomNamesToAlternateSubGroupsMap [fTwoViewAtomShortName] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["help-options-usage"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["option-name-help"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["display-options-values"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["show-options-and-arguments"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["trace-oah"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["trace-passes"] = subGroup;
}

void xml2brlTwoViewOahHandler::createInformationsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Informations group",
        "hinfos-grp",
        "help-informations-grp",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  group->
    setGroupHeaderIsToBeWritten (false);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Informations",
        "hinfos",
        "help-informations",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["version"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["about"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["contact"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["display-cpu-usage"] = subGroup;
}

void xml2brlTwoViewOahHandler::createWarningAndErrorsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Warning and errors group",
        "warning-and-errors-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Warning and errors",
        "warning-and-errors",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["quiet"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["dont-show-errors"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["dont-exit-on-errors"] = subGroup;
}

void xml2brlTwoViewOahHandler::createPresentationAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Presentation group",
        "presentation-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Presentation",
        "presentation",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["use-filename-as-work-title"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["use-lyricists-as-poets"] = subGroup;
}

void xml2brlTwoViewOahHandler::createInputAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Input group",
        "hinput-grp",
        "help-input-grp",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  group->
    setGroupHeaderIsToBeWritten (false);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);
//  fAlternateViewOahHandler-> // JMI
//    registerElementInHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Input",
        "hinput",
        "help-input",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["omit-words"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["convert-tempos-to-rehearsal-marks"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["convert-words-to-rehearsal-marks"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["convert-words-to-tempo"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["cubase"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["dal-segno"] = subGroup;
}

void xml2brlTwoViewOahHandler::createFilesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Files group",
        "files-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Files",
        "files",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["output-file-name"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["auto-output-file-name"] = subGroup;
}

void xml2brlTwoViewOahHandler::createPartsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Parts group",
        "parts-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Parts",
        "parts",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["msr-omit-part-id"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["msr-omit-part-name"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["msr-keep-part-id"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["msr-keep-part-name"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["msr-rename-part"] = subGroup;
}

void xml2brlTwoViewOahHandler::createStavesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Staves group",
        "staves-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Staves",
        "staves",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["create-voices-staff-relative-numbers"] = subGroup;
}

void xml2brlTwoViewOahHandler::createVoicesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Voices group",
        "voices-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Voices",
        "voices",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["create-single-line-staves-as-rythmic"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["connect-arpeggios"] = subGroup;
}

void xml2brlTwoViewOahHandler::createTranspositionsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Transpositions group",
        "transpositions-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Transpositions",
        "transpositions",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["lpsr-transpose"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["lilypond-transpose-part"] = subGroup;
}

void xml2brlTwoViewOahHandler::createClefsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Clefs group",
        "clefs-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Clefs",
        "clefs",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["msr-replace-clef"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["ignore-redundant-clefs"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["comment-clef-changes"] = subGroup;
}

void xml2brlTwoViewOahHandler::createKeysAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Keys group",
        "keys-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Keys",
        "keys",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["msr-replace-keys"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["ignore-redundant-keys"] = subGroup;
}

void xml2brlTwoViewOahHandler::createTimesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Times group",
        "times-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Times",
        "times",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["ignore-redundant-times"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["numerical-time"] = subGroup;
}

void xml2brlTwoViewOahHandler::createRepeatsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Repeats group",
        "repeats-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Repeats",
        "repeats",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["create-implicit-initial-repeat-barline"] = subGroup;
//  fAtomNamesToAlternateSubGroupsMap ["keep-repeat-barlines"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["repeat-brackets"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["ignore-repeat-numbers"] = subGroup;
}

void xml2brlTwoViewOahHandler::createMeasuresAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Measures group",
        "measures-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Measures",
        "measures",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["add-empty-measures"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["replicate-empty-measure"] = subGroup;
}

void xml2brlTwoViewOahHandler::createRestsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Rests group",
        "rests-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Rests",
        "rests",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["delay-rests"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["delay-rests-slashes"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["compress-full-measure-rests"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["merges-rests"] = subGroup;
}

void xml2brlTwoViewOahHandler::createNotesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Notes group",
        "notes-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Notes",
        "notes",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["msr-pitches-language"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["delay-rests-slashes"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["compress-full-measure-rests"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["merges-rests"] = subGroup;
}

void xml2brlTwoViewOahHandler::creatBeamsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Beams group",
        "hbeams-grp",
        "help-beams-grp",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  group->
    setGroupHeaderIsToBeWritten (false);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Beams",
        "hbeams",
        "help-beams",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["no-auto-beaming"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["no-beams"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["delay-rests-beams"] = subGroup; // JMI
}

void xml2brlTwoViewOahHandler::createArticulationsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Articulations group",
        "articulations-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Articulations",
        "articulations",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["omit-articulations"] = subGroup;
}

void xml2brlTwoViewOahHandler::createOrnamentsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Ornaments group",
        "ornaments-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Ornaments",
        "ornaments",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["omit-ornaments"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["delayed-ornaments-fraction"] = subGroup;
}

void xml2brlTwoViewOahHandler::createGraceNotesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Grace notes group",
        "grace-notes-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Grace notes",
        "grace-notes",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["slash-all-grace-notes"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["slur-all-grace-notes"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["beam-all-grace-notes"] = subGroup;
}

void xml2brlTwoViewOahHandler::createChordsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Chords group",
        "chords-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Chords",
        "chords",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["trace-chords"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["add-words-from-the-chords"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["lpsr-chords-language"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["lpsr-pitches-language"] = subGroup;
}

void xml2brlTwoViewOahHandler::createTiesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Ties group",
        "hties-grp",
        "help-ties-grp",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  group->
    setGroupHeaderIsToBeWritten (false);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Ties",
        "hties",
        "help-ties",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["omit-ties"] = subGroup;
}

void xml2brlTwoViewOahHandler::createSlursAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Slurs group",
        "hslurs-grp",
        "help-slurs-grp",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  group->
    setGroupHeaderIsToBeWritten (false);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Slurs",
        "hslurs",
        "help-slurs",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["omit-slurs"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["delay-slurs"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["delay-rests-slurs"] = subGroup;
}

void xml2brlTwoViewOahHandler::createLigaturesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Ligatures group",
        "hligs-grp",
        "help-ligatures-grp",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  group->
    setGroupHeaderIsToBeWritten (false);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Ligatures",
        "hligs",
        "help-ligatures",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["delay-rests-ligatures"] = subGroup;
}

void xml2brlTwoViewOahHandler::createDynamicsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Dynamics group",
        "hdyns-grp",
        "help-dynamics-grp",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  group->
    setGroupHeaderIsToBeWritten (false);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Dynamics",
        "hdyns",
        "help-dynamics",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["omit-dynamics"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["all-dynamics-below"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["delay-dynamics"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["delay-rests-dynamics"] = subGroup;
}

void xml2brlTwoViewOahHandler::createWedgesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Wedges group",
        "hweds-grp",
        "help-wedges-grp",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  group->
    setGroupHeaderIsToBeWritten (false);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Wedges",
        "hweds",
        "help-wedges",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["omit-wedges"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["all-wedges-below"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["delay-rests-wedges"] = subGroup;
}

void xml2brlTwoViewOahHandler::createTupletsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Tuplets group",
        "tuplets-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Tuplets",
        "tuplets",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["trace-tuplets"] = subGroup;
//  fAtomNamesToAlternateSubGroupsMap ["add-words-from-the-tuplets"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["lpsr-tuplets-language"] = subGroup;
}

void xml2brlTwoViewOahHandler::createStringsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Strings group",
        "hstrings-grp",
        "help-strings-grp",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  group->
    setGroupHeaderIsToBeWritten (false);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Strings",
        "hstrings",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["roman-string-numbers"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["avoid-open-strings"] = subGroup;
}

void xml2brlTwoViewOahHandler::createTablaturesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Tablatures group",
        "htabs-grp",
        "help-tablatures-grp",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  group->
    setGroupHeaderIsToBeWritten (false);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Tablatures",
        "htabs",
        "help-tablatures",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["tabFullNotation"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["modernTab"] = subGroup;
}

void xml2brlTwoViewOahHandler::createHarmoniesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Harmonies group",
        "harmonies-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Harmonies",
        "harmonies",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["omit-harmonies"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["show-harmony-voices"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["harmonies-display"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["jazz-harmonies-display"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["show-harmonies-structures"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["show-all-harmonies-contents"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["show-harmony-details"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["show-harmony-analysis"] = subGroup;
}

void xml2brlTwoViewOahHandler::createFiguredBassesAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Figured basses group",
        "figured-basses-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Figured basses",
        "figured-basses",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["omit-figured-basses"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["show-figured-bass-voices"] = subGroup;
}

void xml2brlTwoViewOahHandler::createLyricsAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Lyrics group",
        "lyrics-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Lyrics",
        "lyrics",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["omit-lyrics"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["add-words-from-the-lyrics"] = subGroup;

  fAtomNamesToAlternateSubGroupsMap ["no-lilypond-lyrics"] =subGroup;
  fAtomNamesToAlternateSubGroupsMap ["lyrics-durations"] =subGroup;
  fAtomNamesToAlternateSubGroupsMap ["add-stanzas-numbers-to-lyrics"] =subGroup;
  fAtomNamesToAlternateSubGroupsMap ["lyrics-durations"] =subGroup;
}

void xml2brlTwoViewOahHandler::createOutputAlternateGroup (
  ostream& os)
{
  // group

  S_oahGroup
    group =
      oahGroup::create (
        "Ouptut group",
        "ouptut-group",
        "",
        "",
        kElementVisibilityWhole,
        fAlternateViewOahHandler);
  fAlternateViewOahHandler->
    appendGroupToHandler (group);

  // subgroup

  S_oahSubGroup
    subGroup =
      oahSubGroup::create (
        "Ouptut",
        "ouptut",
        "",
        "",
        kElementVisibilityWhole,
        group);
  group->
    appendSubGroupToGroup (subGroup);

  // atoms

  fAtomNamesToAlternateSubGroupsMap ["msr2lpsr-score-output-kind"] = subGroup;
  fAtomNamesToAlternateSubGroupsMap ["lpsr-Languages-language"] = subGroup;
}

void xml2brlTwoViewOahHandler::checkOptionsAndArguments ()
{
/* JMI
  if (
    // xml2brlTwoViewOahHandler?
    S_xml2brlFullViewOahHandler
      theXml2brlFullViewOahHandler =
        dynamic_cast<xml2brlFullViewOahHandler*>(&(*fOahHandlerToBeUsed))
  ) {
    theXml2brlFullViewOahHandler->
      checkOptionsAndArguments ();
  }
  else {
    stringstream s;

    s <<
      "xml2brlFullViewOahHandler expected for checkOptionsAndArguments()";

    oahError (s.str ());
  }
  */
}

string xml2brlTwoViewOahHandler::asString () const
{
  return "xml2brlTwoViewOahHandler";
}

void xml2brlTwoViewOahHandler::print (ostream& os) const
{
  os <<
    "xml2brlTwoViewOahHandler:" <<
    endl;

  gIndenter++;

  os <<
    "full viewHandler" <<
    endl;

  gIndenter++;

  const list<S_oahGroup>
    fullViewHandlerGroupsList =
      fFullViewOahHandler->getHandlerGroupsList ();

  if (fullViewHandlerGroupsList.size ()) {
    os << endl;

    list<S_oahGroup>::const_iterator
      iBegin = fullViewHandlerGroupsList.begin (),
      iEnd   = fullViewHandlerGroupsList.end (),
      i      = iBegin;
    for ( ; ; ) {
      // print the group
      os << (*i);
      if (++i == iEnd) break;
      os << endl;
    } // for
  }

  gIndenter--;

  os <<
    "userOahHandler" <<
    endl;

  gIndenter++;

  const list<S_oahGroup>
    userOahHandlerGroupsList =
      fAlternateViewOahHandler->getHandlerGroupsList ();

  if (userOahHandlerGroupsList.size ()) {
    os << endl;

    list<S_oahGroup>::const_iterator
      iBegin = userOahHandlerGroupsList.begin (),
      iEnd   = userOahHandlerGroupsList.end (),
      i      = iBegin;
    for ( ; ; ) {
      // print the group
      os << (*i);
      if (++i == iEnd) break;
      os << endl;
    } // for
  }

  gIndenter--;

  gIndenter--;

  os << endl;
}

ostream& operator<< (ostream& os, const S_xml2brlTwoViewOahHandler& elt)
{
  elt->print (os);
  return os;
}

/*
string xml2brlTwoViewHandlerFullViewAtom::asShortNamedOptionString () const
{
  stringstream s;

  s <<
    "-" << fShortName << " " <<
    S_xml2brlTwoViewOahHandlerAsString (fXml2brlOahTwoViewHandlerVariable);

  return s.str ();
}

string xml2brlTwoViewHandlerFullViewAtom::asActualLongNamedOptionString () const
{
  stringstream s;

  s <<
    "-" << fLongName << " " <<
    S_xml2brlTwoViewOahHandlerAsString (fXml2brlOahTwoViewHandlerVariable);

  return s.str ();
}
*/


}


/*
  map<string, oahTwoViewHandlerViewKind>::const_iterator
    it =
      goahTwoViewHandlerViewKindsMap.find (
        theString);

  if (it == goahTwoViewHandlerViewKindsMap.end ()) {
    // no, optional values style kind is unknown in the map
    stringstream s;

    s <<
      "OAH optional values style kind '" << theString <<
      "' is unknown" <<
      endl <<
      "The " <<
      goahTwoViewHandlerViewKindsMap.size () - 1 <<
      " known OAH optional values style kind are:" <<
      endl;

    gIndenter++;

    s <<
      existingoahTwoViewHandlerViewKinds (K_NAMES_LIST_MAX_LENGTH);

    gIndenter--;

    oahError (s.str ());
  }

  setoahTwoViewHandlerViewKindVariable (
    (*it).second);
    */
