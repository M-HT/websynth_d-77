# MIDI Implementation

## Channel Voice Messages

|MIDI Message|HEX Code|Description|Compatibility|
|:---------- |:------ |:--------- |:-----------:|
|NOTE ON|9nH kk vv|Midi channel n(0-15) note ON #kk(0-127), velocity vv(1-127).<br>vv=0 means NOTE OFF|MIDI|
|NOTE OFF|8nH kk vv|Midi channel n(0-15) note OFF #kk(0-127), vv is ignored.|MIDI|
|PITCH BEND|EnH bl bh|Pitch bend as specified by bh\|bl (14 bits).<br>Maximum swing is +/- 1 tone (power-up).<br>Can be changed using « Pitch bend sensitivity ».<br>Center position is 00H 40H.|GM|
|PROGRAM<br>CHANGE|CnH pp|Program (patch) change.<br>Specific action on channel 10 (n=9) : select drumset.<br>Refer to sounds / drumset list.|GM/GS|
|CHANNEL<br>AFTERTOUCH|DnH vv|vv pressure value|MIDI|
|CTRL 00|BnH 00H cc|Bank select : Refer to soundmap. No action on drumset|GS|
|CTRL 01|BnH 01H cc|Modulation wheel|MIDI|
|CTRL 06|BnH 06H cc|Data entry MSB : provides data to RPN and NRPN|MIDI|
|CTRL 07|BnH 07H cc|Volume|MIDI|
|CTRL 10|BnH 0AH cc|Pan|MIDI|
|CTRL 11|BnH 0BH cc|Expression|MIDI/GM|
|CTRL 38|BnH 26H cc|Data entry LSB : provides data to RPN and NRPN<br>Must be received before « Data entry MSB »|MIDI|
|CTRL 64|BnH 40H cc|Sustain (damper) pedal|MIDI|
|CTRL 91|BnH 5BH vv|Reverb send level vv=00H to 7FH|GS|
|CTRL 93|BnH 5DH vv|Chorus send level vv=00H to 7FH|GS|
|CTRL 98|BnH 62H vv|NRPN LSB|MIDI|
|CTRL 99|BnH 63H vv|NRPN MSB|MIDI|
|CTRL 100|BnH 64H vv|RPN LSB|MIDI|
|CTRL 101|BnH 65H vv|RPN MSB|MIDI|
|CTRL 120|BnH 78H xx|All sounds off (abrupt stop of sound on channel n)|MIDI|
|CTRL 121|BnH 79H xx|Reset all controllers|MIDI|
|CTRL 123|BnH 7BH xx|All notes off|MIDI|
|CTRL 124|BnH 7CH xx|Omni off.<br>The same processing will be carried out as when « All Sounds Off » is received.|MIDI|
|CTRL 125|BnH 7DH xx|Omni on.<br>The same processing will be carried out as when « All Sounds Off » is received.|MIDI|
|CTRL 126|BnH 7EH xx|Mono on.<br>The same processing will be carried out as when « All Sounds Off » is received.|MIDI|
|CTRL 127|BnH 7FH xx|Poly on.<br>The same processing will be carried out as when « All Sounds Off » is received.|MIDI|
|RPN 0000H|BnH 65H 00H 64H 00H 06H vv|Pitch bend sensitivity in semitones|MIDI/GM|
|RPN 0001H|BnH 65H 00H 64H 01H 26H vl 06H vh|Fine tuning in cents (vh,vl=00 00H -100, vh,vl=40 00H 0, vh,vl=7F 7FH +99.99)|MIDI|
|RPN 0002H|BnH 65H 00H 64H 02H 06H vv|Coarse tuning in half-tones (vv=00H -64, vv=40H 0, vv=7FH +64)|MIDI|
|NRPN 0120H|BnH 63H 01H 62H 20H 06H vv|TVF cutoff freq modify (vv=40H ->no modif)|GS|
|NRPN 0121H|BnH 63H 01H 62H 21H 06H vv|TVF resonance modify (vv=40H ->no modif)|GS|
|NRPN 18rrH|BnH 63H 18H 62H rr 06H vv|Pitch coarse of drum instrument note rr in semitones (vv=40H ->no modif)|GS|
|NRPN 1ArrH|BnH 63H 1AH 62H rr 06H vv|Level of drum instrument note rr (vv=00H to 7FH)|GS|
|NRPN 1CrrH|BnH 63H 1CH 62H rr 06H vv|Pan of drum instrument note rr (40H = middle)|GS|
|NRPN 1DrrH|BnH 63H 1DH 62H rr 06H vv|Reverb send level of drum instrument note rr (vv=00H to 7FH)|GS|

## System Exclusive Messages

|Manufacturer ID|HEX Code|Description|Compatibility|
|:------------- |:------ |:--------- |:-----------:|
|Universal Non-Real Time|F0H 7EH 7FH 09H 01H F7H|General MIDI reset|GM|
|Universal Real Time|F0H 7FH 7FH 04H 01H 00H ll F7H|Master volume (ll=0 to 127)|GM|
|Yamaha Corporation|F0H 43H 1xH 4CH 00H 00H 7EH xx F7|XG reset<br>The same processing will be carried out as when « GM reset » is received.|XG|
|Roland Corporation|F0H 41H xx 42H 12H 00H 00H 7FH 00H xx F7H|Mode-1 (Single module mode)<br>The same processing will be carried out as when « GM reset » is received.|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 00H 04H vv xx F7H|Master volume (default vv=7FH)|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 00H 7FH 00H xx F7H|GS reset<br>The same processing will be carried out as when « GM reset » is received.|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 01H 30H vv xx F7H|Reverb type (vv=0 to 7), default = 04H<br>00H : Room1, 01H : Room2<br>02H : Room3, 03H : Hall1<br>04H : Hall2, 05H : Plate<br>06H : Delay, 07H : Pan delay|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 01H 31H vv xx F7H|Reverb character, default = 04H<br>The same processing will be carried out as when « Reverb type » is received.|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 01H 33H vv xx F7H|Reverb master level, default = 64|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 01H 34H vv xx F7H|Reverb time|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 01H 38H vv xx F7H|Chorus type (vv=0 to 7), default = 02H<br>00H : Chorus1, 01H : Chorus2<br>02H : Chorus3, 03H : Chorus4<br>04H : Feedback, 05H : Flanger<br>06H : Short delay, 07H : FB delay|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 01H 3AH vv xx F7H|Chorus master level, default = 64|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 01H 3BH vv xx F7H|Chorus feedback|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 01H 3CH vv xx F7H|Chorus delay|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 01H 3DH vv xx F7H|Chorus rate|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 01H 3EH vv xx F7H|Chorus depth|GS|
|Roland Corporation|F0H 41H xx 42H 12H 40H 1pH 15H vv xx F7H|*Part to rhythm allocation, p is part (0 to 15), vv is 00 (sound part) or 01 (rhythm part).*<br>This SYSEX doesn't do anything.|GS|

