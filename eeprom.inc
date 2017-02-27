;**** **** **** **** ****
; The following entries are block-copied from/to EEPROM
eeprom_sig_l:	.byte	1
eeprom_sig_h:	.byte	1
puls_high_l:	.byte	1	; -,
puls_high_h:	.byte	1	;  |
puls_low_l:	.byte	1	;  |- saved pulse lengths during throttle calibration
puls_low_h:	.byte	1	;  |  (order used by rc_prog)
puls_neutral_l:	.byte	1	;  |
puls_neutral_h:	.byte	1	; -'
.if USE_I2C
blc_revision:	.byte	1	; BLConfig revision
blc_setmask:	.byte	1	; BLConfig settings mask
blc_pwmscaling:	.byte	1	; BLConfig pwm scaling
blc_currlimit:	.byte	1	; BLConfig current limit
blc_templimit:	.byte	1	; BLConfig temperature limit
blc_currscale:	.byte	1	; BLConfig current scaling
blc_bitconfig:	.byte	1	; BLConfig bitconfig (1 == MOTOR_REVERSE)
blc_checksum:	.byte	1	; BLConfig checksum (0xaa + above bytes)
.endif
eeprom_end:	.byte	1
