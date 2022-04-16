; CoCo Max III high res joystick interface routine
; by tim lindner, 2022
; base on code by Robert Gault

 section code

_HiResJoyIn_CM3 export
_PIA0_CM3_Mode export
_PIA0_Normal_Mode export

_HiResJoyIn_CM3:
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

 lda #$fe
 sta $ff20    raise dac
 lda #$04
 sta ,x  ; turn off ramp

 ldb #$8c ; reg.b=discharge count
discharge
 decb ; wait for full discharge
 bne discharge
 lda #$2
 sta $ff20    lower dac
 clra
 pshs a
 sta ,x ; start ramp
sample
 lda ,x ; test dac for match
 bmi finish ; exit if match
 incb
 bne sample
 inc ,s
 bne sample
finish

 lda #$fe
 sta $ff20  raise dac
 lda #$04
 sta ,x     turn off ramp


 puls a
 puls cc,pc

_PIA0_CM3_Mode:
 lda $ff01
 anda #~4   Enable data direction register
 sta $ff01
 lda #4   make right button 2 output
 sta $ff00
 lda $ff01
 ora #4     Enable data register
 sta $ff01
 rts

_PIA0_Normal_Mode:
 lda $ff01
 anda #~4   Enable data direction register
 sta $ff01
 lda #0   make all bits input
 sta $ff00
 lda $ff01
 ora #4     Enable data register
 sta $ff01
 rts

 end
