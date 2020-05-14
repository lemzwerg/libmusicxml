\version "2.19.83"

% Generated by xml2ly 0.92 from "/Users/menu/Documents/LaTeX/PartitionsLilypond/ch/Arizona_Oboe.xml"
% on Saturday 2020-01-18 @ 13:48:45 CET

% The translation command line was:
%   xml2ly '-xi' '-aofn' '-dmsr' '-dpg' '--dlpsr' '-abn' '-lpcd' '/Users/menu/Documents/LaTeX/PartitionsLilypond/ch/Arizona_Oboe.xml' '-dov' '-gbabn' '-adb' '-awb' '-sluragn' '-slashagn' '-cwtt' '-lpcd' '-aem' '1 7' '-t=transps' '-instrument' 'Soprano saxophone' '-mtp' 'Oboe=ees'
% or, with long option names:
%  xml2ly /Users/menu/Documents/LaTeX/PartitionsLilypond/ch/Arizona_Oboe.xml -xml2ly-infos -auto-output-file-name -display-msr -display-partgroups -display-lpsr -all-bar-numbers -lilypond-compile-date -display-options-values -generate-box-around-bar-number empty -all-dynamics-below -all-wedges-below -slur-all-grace-notes  -slash-all-grace-notes  -convert-words-to-tempo -lilypond-compile-date -add-empty-measures 1=7 -trace-transpositions -instrument 'Soprano saxophone' -mtp "Oboe=ees"
% or, with short option names:
%   xml2ly /Users/menu/Documents/LaTeX/PartitionsLilypond/ch/Arizona_Oboe.xml -xi -aofn -dmsr -dpg -dlpsr -abn -lpcd -dov -gbabn empty -adb -awb -sluragn -slashagn -cwtt -lpcd -aem 1=7 -ttransps -instrument 'Soprano saxophone' -mtp "Oboe=ees"

% Comment or adapt next line as needed (default is 20)
#(set-global-staff-size 18.2857)


% Scheme function(s): "date & time"
% A set of functions to obtain a source file's modification time.

#(define comml           (object->string (command-line)))
#(define loc             (+ (string-rindex comml #\space ) 2))
#(define commllen        (- (string-length comml) 2))
#(define filen           (substring comml loc commllen))
#(define siz             (object->string (stat:size (stat filen))))
#(define ver             (object->string (lilypond-version)))
#(define dat             (strftime "%d/%m/%Y" (localtime (current-time))))
#(define tim             (strftime "%H:%M:%S" (localtime (current-time))))
#(define modTime         (stat:mtime (stat filen)))
#(define modTimeAsString (strftime "%d/%m/%Y - %H:%M:%S" (localtime modTime)))


\header {
  instrument           = "Soprano saxophone"
  title              = "ARIZONA"
  rights             = ""
  composer           = "Franco Cesarini"
  poet               = ""
  software           = "Neuratron PhotoScore"
}

\paper {
  paper-height                   = 297\mm
  paper-width                    = 210\mm
  
  %left-margin                    = 0.0\mm
  %right-margin                   = 0.0\mm
  %top-margin                     = 0.0\mm
  %bottom-margin                  = 0.0\mm
  
  %horizontal-shift               = 0.0\mm
  %indent                         = 0.0\mm
  %short-indent                   = 0.0\mm
  
  %markup-system-spacing.padding  = 0.0\mm
  %between-system-space           = 0.0\mm
  %page-top-space                 = 0.0\mm
  
  %page-count                     = -1
  %system-count                   = -1
  
  oddHeaderMarkup                = \markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }

  evenHeaderMarkup               = \markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }

  oddFooterMarkup                = \markup {
    \tiny
    \column {
      \fill-line {
        #(string-append
"Music generated from MusicXML by xml2ly 0.92 and engraved by LilyPond " (lilypond-version))
      }
      \fill-line { \italic { \modTimeAsString }}
    }
  }

  evenFooterMarkup               = ""
}

\layout {
  \context {
    \Score
    autoBeaming = ##f % to display tuplets brackets
  }
  \context {
    \Voice
  }
}

% Pick your choice from the next two lines as needed
myBreak = { \break }
%myBreak = { }

% Pick your choice from the next two lines as needed
myPageBreak = { \pageBreak }
%myPageBreak = { }

Part_POne_Staff_One_Voice_One = \absolute {
  \language "nederlands"
  \set Score.barNumberVisibility = #all-bar-numbers-visible
  \override Score.BarNumber.break-visibility = ##(#f #t #t)
  
  \key f \major
  \time 4/4
  
  \clef "treble"
  \tempo "Andantino"
  R%{1%}1 | % 2
  \barNumberCheck #2
  R%{1%}1 | % 3
  \barNumberCheck #3
  r%{2%}2 \tuplet 3/2 {
  r%{3%}8 f' \p [ ( g' ] }
  a'16 [ _\< bes' \! c'' d'' ] ) | % 4
  \barNumberCheck #4
  ees''!4. \mf ( c''8 ) c'' [ ( bes' aes'! bes' ] )  % NoteIsFollowedByGraceNotesGroup
  | % 5
  \barNumberCheck #5
  \acciaccatura { b'!8 } c''4. ( aes'!8 ) aes' [ ( f' ees'! f' ] ) | % 6
  \barNumberCheck #6
  \myBreak | % 6
  
  ees'!4 ( aes'!2 ) aes'8 [ -- aes' ] -- | % 7
  \barNumberCheck #7
  bes'4 --  % NoteIsFollowedByGraceNotesGroup
  \acciaccatura { b'!8 } c''8 [ ( aes'! ] ) aes' [ ( f' ees'! f' ] ) | % 8
  \barNumberCheck #8
  ees'!4 ( aes'!2 ) aes'8 [ -- aes' ] -- | % 9
  \barNumberCheck #9
  bes'4 ( --  % NoteIsFollowedByGraceNotesGroup
  \acciaccatura { b'!8 } c''2. ) _\> | % 10
  \barNumberCheck #10
  R%{1%}1 \! \bar "||"
  | % 11
  \barNumberCheck #11
  \myBreak | % 11
  
  \tempo "Allegro vivace"
  R%{1%}1 | % 12
  \barNumberCheck #12
  r%{2%}2 r%{2%}4 f'16 \mf [ ( g' a' bes' ] | % 13
  \barNumberCheck #13
  c''8 [ ) -. r%{2%} r%{2%} a' ] -. r%{2%} g' [ -. f' -. g' ] -. | % 14
  \barNumberCheck #14
  a'8 [ -. r%{2%} r%{2%} f' ] -. r%{2%} d' [ -. c' -. d' ] -. | % 15
  \barNumberCheck #15
  c'8 -. r%{2%} f' -. r%{2%} r%{2%}4 f'8 [ -. f' ] -. | % 16
  \barNumberCheck #16
  \myBreak | % 16
  
  g'8 -. r%{2%} a' [ -. f' ] -. r%{2%} d' [ -. c' -. d' ] -. | % 17
  \barNumberCheck #17
  c'8 -. r%{2%} f' -. r%{2%} r%{2%}4 f'8 [ -. f' ] -. \bar "||"
  | % 18
  \barNumberCheck #18
  g'8 [ -. r%{2%} r%{2%} a' ] -. g' [ -. f' -. g' -. a' ] -. | % 19
  \barNumberCheck #19
  c''8 -. r%{2%} r%{2%}4 r%{2%}2 | % 20
  \barNumberCheck #20
  R%{1%}1 | % 21
  \barNumberCheck #21
  R%{1%}1 | % 22
  \barNumberCheck #22
  c''8 \f [ -. a' -. g' -. a' ] -. c'' -. r%{2%} r%{2%}4 | % 23
  \barNumberCheck #23
  \myBreak | % 23
  
  r%{2%}2 r%{2%}4 f'16 \f [ ( g' _\< a' \! bes' ] ) | % 24
  \barNumberCheck #24
  c''8 -. r%{2%} r%{2%}4 r%{2%} a'16 \f [ ( _\< bes' \! c'' d'' ] ) | % 25
  \barNumberCheck #25
  ees''!8 -. r%{2%} r%{2%}4 r%{2%}2 | % 26
  \barNumberCheck #26
  ees''!8 \f [ -. r%{2%} r%{2%} c'' ] -. r%{2%} bes' [ -. aes'! -. bes' ] -. | % 27
  \barNumberCheck #27
  c''8 [ -. r%{2%} r%{2%} aes'! ] r%{2%} f' [ -. ees'! -. f' ] -. | % 28
  \barNumberCheck #28
  \myBreak | % 28
  
  ees'!8 -. r%{2%} aes'! -. r%{2%} r%{2%}4 aes'8 [ -. aes' ] -. | % 29
  \barNumberCheck #29
  bes'8 -. r%{2%} c'' [ -. aes'! ] r%{2%} f' [ -. ees'! -. f' ] -. | % 30
  \barNumberCheck #30
  ees'!8 -. r%{2%} aes'! -. r%{2%} r%{2%} aes' [ -. bes' -. c'' ] -. | % 31
  \barNumberCheck #31
  ees''!8 -. r%{2%} r%{2%}4 r%{2%}2 | % 32
  \barNumberCheck #32
  R%{1%}1 \bar "||"
  | % 33
  \barNumberCheck #33
  \numericTimeSignature \time 7/8
  \myBreak | % 33
  
  \tempo "(2+2+3)"
  g'8 \f [ ( a' ] ) c''4 d'' d''8 | % 34
  \barNumberCheck #34
  e''4 c'' a'8 [ ( g' ) a' ] | % 35
  \barNumberCheck #35
  g'8 [ ( a' ] ) c''4 d'' d''8 | % 36
  \barNumberCheck #36
  e''4 c'' a'8 [ ( g' ) a' ] | % 37
  \barNumberCheck #37
  bes'8 [ ( c'' ] ) ees''!4 f''8 [ ( ees'' ) f'' ] | % 38
  \barNumberCheck #38
  \myBreak | % 38
  
  g''4 ees''! c'' c''8 | % 39
  \barNumberCheck #39
  bes'8 [ c'' ] ees''!4 f''8 [ ( ees'' ) f'' ] | % 40
  \barNumberCheck #40
  g''4 ees''! c'' c''8 | % 41
  \barNumberCheck #41
  bes'8 [ ( c'' ] ) ees''!4 f''8 [ ( ees'' ) f'' ] | % 42
  \barNumberCheck #42
  \myBreak | % 42
  
  g''4 ees''! c'' c''8 | % 43
  \barNumberCheck #43
  bes'8 [ ( c'' ] ) ees''!4 f''8 [ ( ees'' ) f'' ] | % 44
  \barNumberCheck #44
  g''4 ees''! c'' c''8 | % 45
  \barNumberCheck #45
  des''!8 r%{2%}4 r%{2%}8 r%{2%}4. | % 46
  \barNumberCheck #46
  R%{1%}2.. \bar "||"
  | % 47
  \barNumberCheck #47
  \time 4/4
  \myBreak | % 47
  
  des''!8 \f [ -. bes' -. aes'! -. bes' ] -. des'' [ -. ees''! _\< -. f'' \! -. fis''! ] -. | % 48
  \barNumberCheck #48
  g''8 -. r%{2%} r%{2%}4 r%{2%}2 | % 49
  \barNumberCheck #49
  R%{1%}1 | % 50
  \barNumberCheck #50
  g''8 \p r%{2%} r%{2%} g'' r%{2%} a'' [ r%{2%} a'' ] | % 51
  \barNumberCheck #51
  \myBreak | % 51
  
  g''8 r%{2%} r%{2%}4 r%{2%}2 | % 52
  \barNumberCheck #52
  R%{1%}1 | % 53
  \barNumberCheck #53
  g''8 \p r%{2%} r%{2%} g'' r%{2%} a'' [ r%{2%} a'' ] | % 54
  \barNumberCheck #54
  g''8 r%{2%} r%{2%}4 r%{2%}2 | % 55
  \barNumberCheck #55
  R%{1%}1 | % 56
  \barNumberCheck #56
  ees''!8 \f [ -. r%{2%} r%{2%} bes' ] -. r%{2%} c'' [ -. c'' -. c'' ] -. | % 57
  \barNumberCheck #57
  \myBreak | % 57
  
  ees''!8 [ -. r%{2%} r%{2%} bes' ] -. r%{2%} a' [ -. a' -. a' ] -. | % 58
  \barNumberCheck #58
  g'8 -. r%{2%} bes' -. r%{2%} r%{2%}4 a'8 [ -. a' ] -. | % 59
  \barNumberCheck #59
  bes'8 -. r%{2%} ees''! [ -. bes' ] -. r%{2%} a' [ -. a' -. a' ] -. | % 60
  \barNumberCheck #60
  g'8 -. r%{2%} bes' -. r%{2%} r%{2%}4 a'8 [ -. a' ] -. | % 61
  \barNumberCheck #61
  bes'8 [ -. r%{2%} r%{2%} ees''! ] -. c'' [ -. c'' -. c'' -. c'' ] -. | % 62
  \barNumberCheck #62
  \myBreak | % 62
  
  ees''!8 -. ees'! \f [ -. f' -. g' ] -. bes' -. r%{2%} r%{2%}4 | % 63
  \barNumberCheck #63
  r%{2%}2 a'16 \mf [ ( bes' c'' _\< d'' ] \! ees''! [ f'' g'' a'' ] ) -. \bar "||"
  | % 64
  \barNumberCheck #64
  \numericTimeSignature \time 7/8
  \tempo "(2+2+3)"
  bes''8 \f r%{2%} r%{2%}4 r%{2%}4. | % 65
  \barNumberCheck #65
  R%{1%}2.. | % 66
  \barNumberCheck #66
  f'8 \f [ ( g' ] ) bes'4 c'' c''8 | % 67
  \barNumberCheck #67
  d''4 bes' g'8 [ ( f' ) g' ] | % 68
  \barNumberCheck #68
  \myBreak | % 68
  
  aes'!8 \f [ bes' ] des''!4 ees''!8 [ ( des'' ) ees'' ] | % 69
  \barNumberCheck #69
  f''4 des''! bes' bes'8 | % 70
  \barNumberCheck #70
  aes'!8 [ ( bes' ] ) des''!4 ees''!8 [ ( des'' ) ees'' ] | % 71
  \barNumberCheck #71
  f''4 des''! bes' bes'8 | % 72
  \barNumberCheck #72
  c''8 [ ( d'' ] ) f''4 g''8 [ ( f'' ) g'' ] | % 73
  \barNumberCheck #73
  a''4 f'' d'' d''8 | % 74
  \barNumberCheck #74
  \myBreak | % 74
  
  c''8 [ ( d'' ] ) f''4 g''8 [ ( f'' ) g'' ] | % 75
  \barNumberCheck #75
  a''4 f'' d'' d''8 | % 76
  \barNumberCheck #76
  c''8 [ ( d'' ] ) f''4 g''8 [ ( f'' ) g'' ] | % 77
  \barNumberCheck #77
  a''4 f'' d'' d''8 | % 78
  \barNumberCheck #78
  c''8 [ ( d'' ] ) f''4 g''8 [ ( f'' ) g'' ] | % 79
  \barNumberCheck #79
  a''4 f'' d'' d''8 | % 80
  \barNumberCheck #80
  f''2  ~ \trill \ff f''4.  ~ | % 81
  \barNumberCheck #81
  \myBreak | % 81
  
  f''2  ~ f''4. | % 82
  \barNumberCheck #82
  c''8 [ ( f'' ] ) c'' [ ( d'' ] ) ees''! [ ( f'' ) d'' ] | % 83
  \barNumberCheck #83
  c''8 [ ( f'' ] ) c'' [ ( d'' ] ) ees''! [ ( f'' ) d'' ] | % 84
  \barNumberCheck #84
  c''8 r%{2%} r%{2%}4 r%{2%}4. \bar "||"
  | % 85
  \barNumberCheck #85
  \key bes \major
  \time 4/4
  \tempo "Adagio"
  r%{2%}4 \tempo "Solo"
  c''2 \mf  % NoteIsFollowedByGraceNotesGroup
  \acciaccatura { d''8 } c''4  ~ | % 86
  \barNumberCheck #86
  c''4 c''2  % NoteIsFollowedByGraceNotesGroup
  \acciaccatura { bes'8 } c''4  ~ ( | % 87
  \barNumberCheck #87
  \myBreak | % 87
  
  c''4 ) bes'8 [ _\< c'' ] ( \! ees'' c''4 _\> bes'8  ~ \! | % 88
  \barNumberCheck #88
  \tempo "Rall."
  bes'2  ~ _\< bes'8 ) \! ges'!4 aes'!8 ( | % 89
  \barNumberCheck #89
  \tempo "A tempo"
  bes'1 ) _\> | % 90
  \barNumberCheck #90
  R%{1%}1 \! | % 91
  \barNumberCheck #91
  R%{1%}1 | % 92
  \barNumberCheck #92
  r%{2%}2 \tempo "all players"
  r%{2%}4 ees' \f | % 93
  \barNumberCheck #93
  \tempo "Grandioso"
  ees''4. ( c''8 ) c'' [ ( bes' aes'! bes' ] )  % NoteIsFollowedByGraceNotesGroup
  | % 94
  \barNumberCheck #94
  \myBreak | % 94
  
  \acciaccatura { bes'!8 } c''4. ( aes'!8 ) aes' [ ( f' ees' f' ] ) | % 95
  \barNumberCheck #95
  ees'4 ( aes'!2 ) aes'8 [ -- aes' ] -- | % 96
  \barNumberCheck #96
  bes'4 --  % NoteIsFollowedByGraceNotesGroup
  \acciaccatura { b'!8 } c''8 [ ( aes'! ] ) aes' [ ( f' ees' f' ] ) | % 97
  \barNumberCheck #97
  ees'4 ( aes'!2 ) aes'8 [ -- aes' ] -- | % 98
  \barNumberCheck #98
  bes'4  % NoteIsFollowedByGraceNotesGroup
  \acciaccatura { b'!8 } c''2. ( | % 99
  \barNumberCheck #99
  \myBreak | % 99
  
  c''2  ~ \tuplet 3/2 {
  c''8 [ aes''! ) _\> g'' ] \! }
  \tuplet 3/2 {
  f''8 [ ees'' des''! ] }
  | % 100
  \barNumberCheck #100
  c''2  ~ \p c''8 r%{2%} r%{2%}4 | % 101
  \barNumberCheck #101
  R%{1%}1 | % 102
  \barNumberCheck #102
  ees''4  ~ \mf ( ees''8 [ f'' ] ) _\< ees''4  ~ ( \! ees''8 [ f'' ] ) | % 103
  \barNumberCheck #103
  \tempo "Rall."
  ees''1  ~ _\> | % 104
  \barNumberCheck #104
  \tempo "Rall. molto"
  ees''2 \! r%{2%} | % 105
  \barNumberCheck #105
  R%{1%}1 | % 106
  \barNumberCheck #106
  R%{1%}1 | % 107
  \barNumberCheck #107
  \myBreak | % 107
  
  r%{2%}2 ees''4. \p ( -- c''8  ~ | % 108
  \barNumberCheck #108
  c''1  ~ | % 109
  \barNumberCheck #109
  c''8 ) r%{2%} r%{2%}4 r%{2%}2 \bar "||"
  | % 110
  \barNumberCheck #110
  \key f \major
  \numericTimeSignature \time 7/8
  \tempo "Allegro vivace (2+2+3)"
  R%{1%}2.. | % 111
  \barNumberCheck #111
  aes'!8 \mf r%{2%} aes' -. r%{2%} aes' -. r%{2%} r%{2%} | % 112
  \barNumberCheck #112
  aes'!8 -. r%{2%} aes' -. r%{2%} aes' -. r%{2%} r%{2%} | % 113
  \barNumberCheck #113
  \myBreak | % 113
  
  aes'!8 -. r%{2%} aes' _\< -. r%{2%} \! aes' -. r%{2%} r%{2%} | % 114
  \barNumberCheck #114
  aes'!8 -. r%{2%} aes' -. r%{2%} aes' -. aes'16 \mf [ ( a'! bes' b'! ] | % 115
  \barNumberCheck #115
  c''8 ) -. r%{2%} c'' -. r%{2%} c'' -. r%{2%} r%{2%} | % 116
  \barNumberCheck #116
  c''8 -. r%{2%} c'' -. r%{2%} c'' -. r%{2%} r%{2%} | % 117
  \barNumberCheck #117
  c''8 -. r%{2%} c'' _\< -. r%{2%} \! c'' -. r%{2%} r%{2%} | % 118
  \barNumberCheck #118
  c''8 -. r%{2%} c'' -. r%{2%} c'' -. r%{2%} r%{2%} | % 119
  \barNumberCheck #119
  \myBreak | % 119
  
  c''8 \f [ -. c'' ] -. c'' [ -. c'' ] -. c'' [ -. c'' -. c'' ] -. | % 120
  \barNumberCheck #120
  f''8 [ ( -> c'' ] ) c'' [ -. c'' ] -. c'' [ -. c'' -. c'' ] -. | % 121
  \barNumberCheck #121
  c''8 [ -. c'' ] -. c'' [ -. c'' ] -. c'' [ -. c'' -. c'' ] -. | % 122
  \barNumberCheck #122
  d''8 [ ( -> c'' ] ) c'' [ -. c'' ] -. c'' [ -. c'' -. c'' ] -. | % 123
  \barNumberCheck #123
  c''8 [ ( d'' ] ) f''4 g''8 [ ( f'' ) g'' ] | % 124
  \barNumberCheck #124
  a''4 f'' d'' d''8 | % 125
  \barNumberCheck #125
  \myBreak | % 125
  
  c''8 [ ( d'' ] ) f''4 g''8 [ ( f'' ) g'' ] | % 126
  \barNumberCheck #126
  a''4 f'' d'' d''8 | % 127
  \barNumberCheck #127
  c''8 r%{2%} r%{2%}4 r%{2%}4. | % 128
  \barNumberCheck #128
  r%{2%}4 a'' \f -. g''8 [ ( f'' ) g'' ] | % 129
  \barNumberCheck #129
  f''4 -. r%{2%} r%{2%}4. | % 130
  \barNumberCheck #130
  r%{2%}4 f'' -. g''8 [ ( f'' ) g'' ] | % 131
  \barNumberCheck #131
  f''4 -. f'' -. g''8 [ ( f'' ) g'' ] | % 132
  \barNumberCheck #132
  f''4 -. f'' -. g''8 [ ( f'' ) g'' ] \bar "||"
  | % 133
  \barNumberCheck #133
  \numericTimeSignature \time 6/8
  \myBreak | % 133
  
  f''8 [ ees''! -> f'' ] -> g'' [ -> f'' -> g'' ] -> \bar "||"
  | % 134
  \barNumberCheck #134
  \time 4/4
  aes''!8 r%{2%} r%{2%}4 r%{2%}2 | % 135
  \barNumberCheck #135
  R%{1%}1 | % 136
  \barNumberCheck #136
  r%{2%}2 r%{2%}4 ees'!16 \f [ ( f' _\< g' \! aes'! ] | % 137
  \barNumberCheck #137
  bes'8 [ ) -. r%{2%} r%{2%} bes' ] -. r%{2%} c'' [ -. c'' -. c'' ] -. | % 138
  \barNumberCheck #138
  \myBreak | % 138
  
  ees''!8 [ r%{2%} r%{2%} bes' ] -. r%{2%} a' [ -. a' -. a' ] -. | % 139
  \barNumberCheck #139
  g'8 -. r%{2%} bes' -. r%{2%} r%{2%}4 a'8 [ -. a' ] -. | % 140
  \barNumberCheck #140
  bes'8 -. r%{2%} ees''! [ -. bes' ] -. r%{2%} a' [ -. a' -. a' ] -. | % 141
  \barNumberCheck #141
  g'8 -. r%{2%} bes' -. r%{2%} r%{2%}4 a'8 [ -. a' ] -. | % 142
  \barNumberCheck #142
  bes'8 [ -. r%{2%} r%{2%} ees''! ] -. c'' [ -. c'' -. c'' -. c'' ] -. | % 143
  \barNumberCheck #143
  \myBreak | % 143
  
  ees''!8 -. ees'! \f [ -. f' -. g' ] -. bes' -. r%{2%} r%{2%}4 | % 144
  \barNumberCheck #144
  r%{2%}2 ees'!16 \mf [ ( f' _\< g' \! a' ] bes' [ c'' d'' ees''! ] ) \bar "||"
  | % 145
  \barNumberCheck #145
  \numericTimeSignature \time 7/8
  \tempo "(2+2+3)"
  f''8 \f r%{2%} r%{2%}4 r%{2%}4. | % 146
  \barNumberCheck #146
  R%{1%}2.. | % 147
  \barNumberCheck #147
  f'8 \f [ ( g' ] ) bes'4 c'' c''8 | % 148
  \barNumberCheck #148
  d''4 bes' g'8 [ ( f' ) g' ] | % 149
  \barNumberCheck #149
  \myBreak | % 149
  
  aes'!8 [ ( bes' ] ) des''!4 ees''!8 [ ( des'' ) ees'' ] | % 150
  \barNumberCheck #150
  f''4 des''! bes' bes'8 | % 151
  \barNumberCheck #151
  aes'!8 [ ( bes' ] ) des''!4 ees''!8 [ ( des'' ) ees'' ] | % 152
  \barNumberCheck #152
  f''4 des''! bes' bes'8 | % 153
  \barNumberCheck #153
  c''8 [ ( d'' ] ) f''4 g''8 [ ( f'' ) g'' ] | % 154
  \barNumberCheck #154
  a''4 f'' d'' d''8 | % 155
  \barNumberCheck #155
  \myBreak | % 155
  
  c''8 [ ( d'' ] ) f''4 g''8 [ ( f'' ) g'' ] | % 156
  \barNumberCheck #156
  a''4 f'' d'' d''8 | % 157
  \barNumberCheck #157
  c''8 [ ( d'' ] ) f''4 g''8 [ ( f'' ) g'' ] | % 158
  \barNumberCheck #158
  a''4 f'' d'' d''8 | % 159
  \barNumberCheck #159
  c''8 [ ( d'' ] ) f''4 g''8 [ ( f'' ) g'' ] | % 160
  \barNumberCheck #160
  a''4 f'' d'' d''8 | % 161
  \barNumberCheck #161
  \myBreak | % 161
  
  f''2  ~ \trill \ff f''4.  ~ | % 162
  \barNumberCheck #162
  f''2  ~ f''4. | % 163
  \barNumberCheck #163
  c''8 [ ( f'' ] ) c'' [ ( d'' ] ) ees''! [ ( f'' ) d'' ] | % 164
  \barNumberCheck #164
  c''8 [ ( f'' ] ) c'' [ ( d'' ] ) ees''! [ ( f'' ) d'' ] | % 165
  \barNumberCheck #165
  c''4 -> a' -> g'8 [ ( -> f' ) -> g' ] -> | % 166
  \barNumberCheck #166
  a'4 -> c'' -> g'16 [ ( aes'! bes' c'' d'' ees''! ] ) | % 167
  \barNumberCheck #167
  f''8 -> r%{2%} r%{2%}4 r%{2%}4.
  \bar "|."
  | % 168
  \barNumberCheck #168
}

\book {
  \header {
    instrument = "Soprano saxophone"
  }
  
  \score {
    <<
      
      \new Staff = "Part_POne_Staff_One"
      \with {
        instrumentName = "Oboe"
      }
      <<
        \context Voice = "Part_POne_Staff_One_Voice_One" <<
          \transposition ees
          \transpose ees c'
          \Part_POne_Staff_One_Voice_One
        >>
      >>
      
    >>
    
    \layout {
      \context {
        \Score
        autoBeaming = ##f % to display tuplets brackets
      }
      \context {
        \Voice
      }
    }
    
    \midi {
      \tempo 4 = 90
    }
  }
  
  \paper {
    paper-height                   = 297\mm
    paper-width                    = 210\mm
    
    %left-margin                    = 0.0\mm
    %right-margin                   = 0.0\mm
    %top-margin                     = 0.0\mm
    %bottom-margin                  = 0.0\mm
    
    %horizontal-shift               = 0.0\mm
    %indent                         = 0.0\mm
    %short-indent                   = 0.0\mm
    
    %markup-system-spacing.padding  = 0.0\mm
    %between-system-space           = 0.0\mm
    %page-top-space                 = 0.0\mm
    
    %page-count                     = -1
    %system-count                   = -1
    
    oddHeaderMarkup                = \markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }

    evenHeaderMarkup               = \markup {
    \fill-line {
      \on-the-fly \not-first-page {
        \fromproperty #'page:page-number-string
        " "
        \fromproperty #'header:title
        " "
        \fromproperty #'header:subtitle
      }
    }
  }

    oddFooterMarkup                = \markup {
    \tiny
    \column {
      \fill-line {
        #(string-append
"Music generated from MusicXML by xml2ly 0.92 and engraved by LilyPond " (lilypond-version))
      }
      \fill-line { \italic { \modTimeAsString }}
    }
  }

    evenFooterMarkup               = ""
  }
  
}
