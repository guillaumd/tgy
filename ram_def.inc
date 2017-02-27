
;**** **** **** **** ****
; RAM Definitions
.dseg				; DATA segment
.org SRAM_START

orig_osccal:	.byte	1	; original OSCCAL value
goodies:	.byte	1	; Number of rounds without timeout
powerskip:	.byte	1	; Skip power through this number of steps
ocr1ax:		.byte	1	; 3rd byte of OCR1A
tcnt1x:		.byte	1	; 3rd byte of TCNT1
pwm_on_ptr:	.byte	1	; Next PWM ON vector
rct_boot:	.byte	1	; Counter which increments while rc_timeout is 0 to jump to boot loader
rct_beacon:	.byte	1	; Counter which increments while rc_timeout is 0 to disarm and beep occasionally
idle_beacon:	.byte	1	; Counter which increments while armed and idle to beep occasionally
last_tcnt1_l:	.byte	1	; last timer1 value
last_tcnt1_h:	.byte	1
last_tcnt1_x:	.byte	1
l2_tcnt1_l:	.byte	1	; last last timer1 value
l2_tcnt1_h:	.byte	1
l2_tcnt1_x:	.byte	1
timing_l:	.byte	1	; interval of 2 commutations
timing_h:	.byte	1
timing_x:	.byte	1
com_time_l:	.byte	1	; time of last commutation
com_time_h:	.byte	1
com_time_x:	.byte	1
start_delay:	.byte	1	; delay count after starting commutations before checking back-EMF
start_modulate:	.byte	1	; Start modulation counter (to reduce heating from PWR_MAX_START if stuck)
start_fail:	.byte   1	; Number of start_modulate loops for eventual failure and disarm
rcp_beep_count:	.byte	1	; Number of RC pulse error beeps
rc_duty_l:	.byte	1	; desired duty cycle
rc_duty_h:	.byte	1
fwd_scale_l:	.byte	1	; 16.16 multipliers to scale input RC pulse to POWER_RANGE
fwd_scale_h:	.byte	1
rev_scale_l:	.byte	1
rev_scale_h:	.byte	1
neutral_l:	.byte	1	; Offset for neutral throttle (in CPU_MHZ)
neutral_h:	.byte	1
.if RCP_DEADBAND && defined(RCP_ALIAS_SHIFT)
deadband_l:	.byte	1	; Deadband scaled for possible input alias
deadband_h:	.byte	1
.endif
.if LOW_BRAKE
low_brake_l:	.byte	1	; Low brake position with deadband applied
low_brake_h:	.byte	1
.endif
.if USE_I2C
i2c_max_pwm:	.byte	1	; MaxPWM for MK (NOTE: 250 while stopped is magic and enables v2)
i2c_rx_state:	.byte	1
i2c_blc_offset:	.byte	1
.endif
motor_count:	.byte	1	; Motor number for serial control
brake_sub:	.byte	1	; Brake speed subtrahend (power of two)
brake_want:	.byte	1	; Type of brake desired
brake_active:	.byte	1	; Type of brake active
