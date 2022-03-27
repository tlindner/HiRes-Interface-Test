; tandy high res joystick interface routine
; by tim lindner, 2022
; base on code by Robert Gault

 section code

_HiResJoyIn export
_setMasterSoundSwitch export

_HiResJoyIn:
 pshs cc
; sync ; reduces jitter
 orcc #$50 ; turn off interrupts
 lda $ff01 ; mux values; save and set for x jstick
 anda #~8
 tst 3,s
 beq mux1
 ora #$8
mux1
 sta $ff01 ; mux adjust
 lda $ff03
 anda #~8
 tst 4,s
 beq mux2
 ora #$08
mux2
 sta $ff03 ; mux adjust
 ldx #$ff00 ; set for indirect instruction

readjs
 ldd #$fe8c ; reg.a=dac; reg.b=discharge count
 sta $ff20 ; turn off ramp if on
discharge
 decb ; wait for full discharge
 bne discharge
 clra
 pshs a
 lda #2 ; ramp trigger
 sta $ff20 ; start ramp
sample
 lda ,x ; test dac for match
 bmi finish ; exit if match
 incb
 bne sample
 inc ,s
 bne sample
finish
 lda #$fe
 sta $ff20 ; stop ramp
 puls a
 puls cc,pc

_setMasterSoundSwitch:
 lda $ff23 ; sound control; turn off
 anda #~8 ; no sound
 tst 3,s
 beq setsound
 ora #8 ; yes sound
setsound
 sta $ff23
 puls pc

 end
