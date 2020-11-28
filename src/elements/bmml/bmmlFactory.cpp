/*
  MusicXML Library
  Copyright (C) Grame 2006-2020

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

//======================================================================
// DON'T MODIFY THIS FILE!
// It is automatically generated from the BMML schema.
// (see the schema folder)
//======================================================================

#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include "elements.h"
#include "factory.h"
#include "types.h"

using namespace std; 

// libmxmllineno is outside of name space MusicXML2
extern int libmxmllineno;


namespace MusicXML2 
{


template<int elt>
class newElementFunctor : public functor<Sxmlelement>
{
  public:
  
    Sxmlelement operator ()()
        { return musicxml<elt>::new_musicxml (libmxmllineno); }
};


Sxmlelement factory::create (const string& eltname) const
{ 
	map<std::string, functor<Sxmlelement>*>::const_iterator i = fMap.find (eltname);
	if (i != fMap.end()) {
		functor<Sxmlelement>* f = i->second;
		if (f) {
			Sxmlelement elt = (*f)();
			elt->setName(eltname);
			return elt;
		}
	}
	cerr << "Sxmlelement factory::create called with unknown element \"" << eltname << "\"" << endl;
	return 0;
}

Sxmlelement factory::create(int type) const
{ 
	map<int, const char*>::const_iterator i = fType2name.find (type);
	if (i != fType2name.end()) {
		return create (i->second);
	}
	cerr << "Sxmlelement factory::create called with unknown type \"" << type << "\"" << endl;
	return 0;
}


factory::factory() 
{
	fMap["comment"] 		= new newElementFunctor<kComment>;
	fMap["pi"] 				= new newElementFunctor<kProcessingInstruction>;
	fType2name[kComment] 	= "comment";
	fType2name[kProcessingInstruction]  = "pi";

	fMap["abbr_name"] 	= new newElementFunctor<k_abbr_name>;
	fMap["accidental"] 	= new newElementFunctor<k_accidental>;
	fMap["accordion_register"] 	= new newElementFunctor<k_accordion_register>;
	fMap["accordion_row"] 	= new newElementFunctor<k_accordion_row>;
	fMap["alteration"] 	= new newElementFunctor<k_alteration>;
	fMap["alternation"] 	= new newElementFunctor<k_alternation>;
	fMap["alternation_ref"] 	= new newElementFunctor<k_alternation_ref>;
	fMap["appoggiatura_ref"] 	= new newElementFunctor<k_appoggiatura_ref>;
	fMap["barline"] 	= new newElementFunctor<k_barline>;
	fMap["barline_type"] 	= new newElementFunctor<k_barline_type>;
	fMap["barre"] 	= new newElementFunctor<k_barre>;
	fMap["bow"] 	= new newElementFunctor<k_bow>;
	fMap["breath"] 	= new newElementFunctor<k_breath>;
	fMap["chord"] 	= new newElementFunctor<k_chord>;
	fMap["chord_data"] 	= new newElementFunctor<k_chord_data>;
	fMap["chord_prefix"] 	= new newElementFunctor<k_chord_prefix>;
	fMap["chord_type"] 	= new newElementFunctor<k_chord_type>;
	fMap["clef"] 	= new newElementFunctor<k_clef>;
	fMap["coda"] 	= new newElementFunctor<k_coda>;
	fMap["dot"] 	= new newElementFunctor<k_dot>;
	fMap["duration"] 	= new newElementFunctor<k_duration>;
	fMap["dynamic"] 	= new newElementFunctor<k_dynamic>;
	fMap["editorial_mark"] 	= new newElementFunctor<k_editorial_mark>;
	fMap["ending"] 	= new newElementFunctor<k_ending>;
	fMap["family"] 	= new newElementFunctor<k_family>;
	fMap["fermata"] 	= new newElementFunctor<k_fermata>;
	fMap["fingering"] 	= new newElementFunctor<k_fingering>;
	fMap["foot_crossing"] 	= new newElementFunctor<k_foot_crossing>;
	fMap["generic_text"] 	= new newElementFunctor<k_generic_text>;
	fMap["hand"] 	= new newElementFunctor<k_hand>;
	fMap["harmonic"] 	= new newElementFunctor<k_harmonic>;
	fMap["inaccord"] 	= new newElementFunctor<k_inaccord>;
	fMap["interval"] 	= new newElementFunctor<k_interval>;
	fMap["interval_data"] 	= new newElementFunctor<k_interval_data>;
	fMap["interval_ref"] 	= new newElementFunctor<k_interval_ref>;
	fMap["interval_type"] 	= new newElementFunctor<k_interval_type>;
	fMap["intervals"] 	= new newElementFunctor<k_intervals>;
	fMap["key_signature"] 	= new newElementFunctor<k_key_signature>;
	fMap["line_of_continuation"] 	= new newElementFunctor<k_line_of_continuation>;
	fMap["lyric"] 	= new newElementFunctor<k_lyric>;
	fMap["lyric_prefix"] 	= new newElementFunctor<k_lyric_prefix>;
	fMap["lyric_repeat"] 	= new newElementFunctor<k_lyric_repeat>;
	fMap["lyric_repetition"] 	= new newElementFunctor<k_lyric_repetition>;
	fMap["lyrics"] 	= new newElementFunctor<k_lyrics>;
	fMap["merged_text"] 	= new newElementFunctor<k_merged_text>;
	fMap["meta_data"] 	= new newElementFunctor<k_meta_data>;
	fMap["metronome"] 	= new newElementFunctor<k_metronome>;
	fMap["metronome_equal"] 	= new newElementFunctor<k_metronome_equal>;
	fMap["metronome_note_type"] 	= new newElementFunctor<k_metronome_note_type>;
	fMap["metronome_value"] 	= new newElementFunctor<k_metronome_value>;
	fMap["midi_instrument"] 	= new newElementFunctor<k_midi_instrument>;
	fMap["midi_metronome"] 	= new newElementFunctor<k_midi_metronome>;
	fMap["multimeasure"] 	= new newElementFunctor<k_multimeasure>;
	fMap["music_hyphen"] 	= new newElementFunctor<k_music_hyphen>;
	fMap["name"] 	= new newElementFunctor<k_name>;
	fMap["newline"] 	= new newElementFunctor<k_newline>;
	fMap["note"] 	= new newElementFunctor<k_note>;
	fMap["note_data"] 	= new newElementFunctor<k_note_data>;
	fMap["note_ref"] 	= new newElementFunctor<k_note_ref>;
	fMap["note_type"] 	= new newElementFunctor<k_note_type>;
	fMap["nuance"] 	= new newElementFunctor<k_nuance>;
	fMap["nuance_ref"] 	= new newElementFunctor<k_nuance_ref>;
	fMap["nuances"] 	= new newElementFunctor<k_nuances>;
	fMap["number"] 	= new newElementFunctor<k_number>;
	fMap["octave"] 	= new newElementFunctor<k_octave>;
	fMap["organ_pedal"] 	= new newElementFunctor<k_organ_pedal>;
	fMap["ornament"] 	= new newElementFunctor<k_ornament>;
	fMap["ornament_type"] 	= new newElementFunctor<k_ornament_type>;
	fMap["part"] 	= new newElementFunctor<k_part>;
	fMap["part_data"] 	= new newElementFunctor<k_part_data>;
	fMap["part_list"] 	= new newElementFunctor<k_part_list>;
	fMap["part_name"] 	= new newElementFunctor<k_part_name>;
	fMap["pedal"] 	= new newElementFunctor<k_pedal>;
	fMap["pitch"] 	= new newElementFunctor<k_pitch>;
	fMap["pizzicato"] 	= new newElementFunctor<k_pizzicato>;
	fMap["rasgueado"] 	= new newElementFunctor<k_rasgueado>;
	fMap["repeat"] 	= new newElementFunctor<k_repeat>;
	fMap["repeat_data"] 	= new newElementFunctor<k_repeat_data>;
	fMap["repeat_ref"] 	= new newElementFunctor<k_repeat_ref>;
	fMap["repeats"] 	= new newElementFunctor<k_repeats>;
	fMap["repetition"] 	= new newElementFunctor<k_repetition>;
	fMap["rest"] 	= new newElementFunctor<k_rest>;
	fMap["rest_data"] 	= new newElementFunctor<k_rest_data>;
	fMap["rest_type"] 	= new newElementFunctor<k_rest_type>;
	fMap["rhythmic_group"] 	= new newElementFunctor<k_rhythmic_group>;
	fMap["right_string_fingering"] 	= new newElementFunctor<k_right_string_fingering>;
	fMap["score"] 	= new newElementFunctor<k_score>;
	fMap["score_data"] 	= new newElementFunctor<k_score_data>;
	fMap["score_header"] 	= new newElementFunctor<k_score_header>;
	fMap["segno"] 	= new newElementFunctor<k_segno>;
	fMap["separator"] 	= new newElementFunctor<k_separator>;
	fMap["shift_line"] 	= new newElementFunctor<k_shift_line>;
	fMap["slur"] 	= new newElementFunctor<k_slur>;
	fMap["slur_ref"] 	= new newElementFunctor<k_slur_ref>;
	fMap["slurs"] 	= new newElementFunctor<k_slurs>;
	fMap["space"] 	= new newElementFunctor<k_space>;
	fMap["stem"] 	= new newElementFunctor<k_stem>;
	fMap["stem_data"] 	= new newElementFunctor<k_stem_data>;
	fMap["stem_type"] 	= new newElementFunctor<k_stem_type>;
	fMap["string"] 	= new newElementFunctor<k_string>;
	fMap["string_fingering"] 	= new newElementFunctor<k_string_fingering>;
	fMap["string_position"] 	= new newElementFunctor<k_string_position>;
	fMap["stroke"] 	= new newElementFunctor<k_stroke>;
	fMap["syllabic_mute"] 	= new newElementFunctor<k_syllabic_mute>;
	fMap["syllabic_parenthesis"] 	= new newElementFunctor<k_syllabic_parenthesis>;
	fMap["syllabic_slur"] 	= new newElementFunctor<k_syllabic_slur>;
	fMap["syllabic_text"] 	= new newElementFunctor<k_syllabic_text>;
	fMap["syllable"] 	= new newElementFunctor<k_syllable>;
	fMap["syllable_mute"] 	= new newElementFunctor<k_syllable_mute>;
	fMap["syllable_ref"] 	= new newElementFunctor<k_syllable_ref>;
	fMap["tie"] 	= new newElementFunctor<k_tie>;
	fMap["tie_ref"] 	= new newElementFunctor<k_tie_ref>;
	fMap["ties"] 	= new newElementFunctor<k_ties>;
	fMap["time_signature"] 	= new newElementFunctor<k_time_signature>;
	fMap["tremolo"] 	= new newElementFunctor<k_tremolo>;
	fMap["tremolo_ref"] 	= new newElementFunctor<k_tremolo_ref>;
	fMap["tuplet"] 	= new newElementFunctor<k_tuplet>;
	fMap["tuplet_ref"] 	= new newElementFunctor<k_tuplet_ref>;
	fMap["tuplets"] 	= new newElementFunctor<k_tuplets>;
	fMap["unknown"] 	= new newElementFunctor<k_unknown>;
	fMap["value_prefix"] 	= new newElementFunctor<k_value_prefix>;

	fType2name[k_abbr_name] 	= "abbr_name";
	fType2name[k_accidental] 	= "accidental";
	fType2name[k_accordion_register] 	= "accordion_register";
	fType2name[k_accordion_row] 	= "accordion_row";
	fType2name[k_alteration] 	= "alteration";
	fType2name[k_alternation] 	= "alternation";
	fType2name[k_alternation_ref] 	= "alternation_ref";
	fType2name[k_appoggiatura_ref] 	= "appoggiatura_ref";
	fType2name[k_barline] 	= "barline";
	fType2name[k_barline_type] 	= "barline_type";
	fType2name[k_barre] 	= "barre";
	fType2name[k_bow] 	= "bow";
	fType2name[k_breath] 	= "breath";
	fType2name[k_chord] 	= "chord";
	fType2name[k_chord_data] 	= "chord_data";
	fType2name[k_chord_prefix] 	= "chord_prefix";
	fType2name[k_chord_type] 	= "chord_type";
	fType2name[k_clef] 	= "clef";
	fType2name[k_coda] 	= "coda";
	fType2name[k_dot] 	= "dot";
	fType2name[k_duration] 	= "duration";
	fType2name[k_dynamic] 	= "dynamic";
	fType2name[k_editorial_mark] 	= "editorial_mark";
	fType2name[k_ending] 	= "ending";
	fType2name[k_family] 	= "family";
	fType2name[k_fermata] 	= "fermata";
	fType2name[k_fingering] 	= "fingering";
	fType2name[k_foot_crossing] 	= "foot_crossing";
	fType2name[k_generic_text] 	= "generic_text";
	fType2name[k_hand] 	= "hand";
	fType2name[k_harmonic] 	= "harmonic";
	fType2name[k_inaccord] 	= "inaccord";
	fType2name[k_interval] 	= "interval";
	fType2name[k_interval_data] 	= "interval_data";
	fType2name[k_interval_ref] 	= "interval_ref";
	fType2name[k_interval_type] 	= "interval_type";
	fType2name[k_intervals] 	= "intervals";
	fType2name[k_key_signature] 	= "key_signature";
	fType2name[k_line_of_continuation] 	= "line_of_continuation";
	fType2name[k_lyric] 	= "lyric";
	fType2name[k_lyric_prefix] 	= "lyric_prefix";
	fType2name[k_lyric_repeat] 	= "lyric_repeat";
	fType2name[k_lyric_repetition] 	= "lyric_repetition";
	fType2name[k_lyrics] 	= "lyrics";
	fType2name[k_merged_text] 	= "merged_text";
	fType2name[k_meta_data] 	= "meta_data";
	fType2name[k_metronome] 	= "metronome";
	fType2name[k_metronome_equal] 	= "metronome_equal";
	fType2name[k_metronome_note_type] 	= "metronome_note_type";
	fType2name[k_metronome_value] 	= "metronome_value";
	fType2name[k_midi_instrument] 	= "midi_instrument";
	fType2name[k_midi_metronome] 	= "midi_metronome";
	fType2name[k_multimeasure] 	= "multimeasure";
	fType2name[k_music_hyphen] 	= "music_hyphen";
	fType2name[k_name] 	= "name";
	fType2name[k_newline] 	= "newline";
	fType2name[k_note] 	= "note";
	fType2name[k_note_data] 	= "note_data";
	fType2name[k_note_ref] 	= "note_ref";
	fType2name[k_note_type] 	= "note_type";
	fType2name[k_nuance] 	= "nuance";
	fType2name[k_nuance_ref] 	= "nuance_ref";
	fType2name[k_nuances] 	= "nuances";
	fType2name[k_number] 	= "number";
	fType2name[k_octave] 	= "octave";
	fType2name[k_organ_pedal] 	= "organ_pedal";
	fType2name[k_ornament] 	= "ornament";
	fType2name[k_ornament_type] 	= "ornament_type";
	fType2name[k_part] 	= "part";
	fType2name[k_part_data] 	= "part_data";
	fType2name[k_part_list] 	= "part_list";
	fType2name[k_part_name] 	= "part_name";
	fType2name[k_pedal] 	= "pedal";
	fType2name[k_pitch] 	= "pitch";
	fType2name[k_pizzicato] 	= "pizzicato";
	fType2name[k_rasgueado] 	= "rasgueado";
	fType2name[k_repeat] 	= "repeat";
	fType2name[k_repeat_data] 	= "repeat_data";
	fType2name[k_repeat_ref] 	= "repeat_ref";
	fType2name[k_repeats] 	= "repeats";
	fType2name[k_repetition] 	= "repetition";
	fType2name[k_rest] 	= "rest";
	fType2name[k_rest_data] 	= "rest_data";
	fType2name[k_rest_type] 	= "rest_type";
	fType2name[k_rhythmic_group] 	= "rhythmic_group";
	fType2name[k_right_string_fingering] 	= "right_string_fingering";
	fType2name[k_score] 	= "score";
	fType2name[k_score_data] 	= "score_data";
	fType2name[k_score_header] 	= "score_header";
	fType2name[k_segno] 	= "segno";
	fType2name[k_separator] 	= "separator";
	fType2name[k_shift_line] 	= "shift_line";
	fType2name[k_slur] 	= "slur";
	fType2name[k_slur_ref] 	= "slur_ref";
	fType2name[k_slurs] 	= "slurs";
	fType2name[k_space] 	= "space";
	fType2name[k_stem] 	= "stem";
	fType2name[k_stem_data] 	= "stem_data";
	fType2name[k_stem_type] 	= "stem_type";
	fType2name[k_string] 	= "string";
	fType2name[k_string_fingering] 	= "string_fingering";
	fType2name[k_string_position] 	= "string_position";
	fType2name[k_stroke] 	= "stroke";
	fType2name[k_syllabic_mute] 	= "syllabic_mute";
	fType2name[k_syllabic_parenthesis] 	= "syllabic_parenthesis";
	fType2name[k_syllabic_slur] 	= "syllabic_slur";
	fType2name[k_syllabic_text] 	= "syllabic_text";
	fType2name[k_syllable] 	= "syllable";
	fType2name[k_syllable_mute] 	= "syllable_mute";
	fType2name[k_syllable_ref] 	= "syllable_ref";
	fType2name[k_tie] 	= "tie";
	fType2name[k_tie_ref] 	= "tie_ref";
	fType2name[k_ties] 	= "ties";
	fType2name[k_time_signature] 	= "time_signature";
	fType2name[k_tremolo] 	= "tremolo";
	fType2name[k_tremolo_ref] 	= "tremolo_ref";
	fType2name[k_tuplet] 	= "tuplet";
	fType2name[k_tuplet_ref] 	= "tuplet_ref";
	fType2name[k_tuplets] 	= "tuplets";
	fType2name[k_unknown] 	= "unknown";
	fType2name[k_value_prefix] 	= "value_prefix";
}
}