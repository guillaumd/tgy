
;-- Instruction extension macros -----------------------------------------

; Add any 16-bit immediate to a register pair (@0:@1 += @2), no Z flag
.macro adi2
	.if byte1(-@2)
		subi	@0, byte1(-@2)
		sbci	@1, byte1(-byte2(@2 + 0xff))
	.else
		subi	@1, byte1(-byte2(@2 + 0xff))
	.endif
.endmacro

; Smaller version for r24 and above, Z flag not reliable
.macro adiwx
	.if !(@2 & 0xff) || (@2) & ~0x3f
		adi2	@0, @1, @2
	.else
		adiw	@0, @2
	.endif
.endmacro

; Compare any 16-bit immediate from a register pair (@0:@1 -= @2, maybe clobbering @3)
.macro cpiz2
		cpi	@0, byte1(@2)
	.if byte2(@2)
		ldi	@3, byte2(@2)
		cpc	@1, @3
	.else
		cpc	@1, ZH
	.endif
.endmacro

; Compare any 16-bit immediate from a register pair (@0:@1 -= @2, maybe clobbering @3), no Z flag
; Do not follow by Z flag tests like breq, brne, brlt, brge, brlo, brsh!
; The idea here is that the low byte being compared with (subtracted by)
; 0 will never set carry, so skipping it and cpi'ing the high byte is the
; same other than the result of the Z flag.
.macro cpi2
	.if byte1(@2)
		cpiz2	@0, @1, @2, @3
	.else
		cpi	@1, byte2(@2)
	.endif
.endmacro

; Compare any 24-bit immediate from a register triplet (@0:@1:@2 -= @3, maybe clobbering @4)
.macro cpiz3
		cpi	@0, byte1(@3)
	.if byte2(@3)
		ldi	@4, byte2(@3)
		cpc	@1, @4
	.else
		cpc	@1, ZH
	.endif
	.if byte3(@3)
		ldi	@4, byte3(@3)
		cpc	@2, @4
	.else
		cpc	@2, ZH
	.endif
.endmacro

; Compare any 24-bit immediate from a register triplet (@0:@1:@2 -= @3, maybe clobbering @4)
; May not set Z flag, as above.
.macro cpi3
	.if byte1(@3)
		cpiz3	@0, @1, @2, @3, @4
	.else
		cpi2	@1, @2, @3 >> 8, @4
	.endif
.endmacro

; Subtract any 16-bit immediate from a register pair (@0:@1 -= @2), no Z flag
.macro sbi2
	.if byte1(@2)
		subi	@0, byte1(@2)
		sbci	@1, byte2(@2)
	.else
		subi	@1, byte2(@2)
	.endif
.endmacro

; Smaller version for r24 and above, Z flag not reliable
.macro sbiwx
	.if !(@2 & 0xff) || (@2) & ~0x3f
		sbi2	@0, @1, @2
	.else
		sbiw	@0, @2
	.endif
.endmacro

; Load 2-byte immediate
.macro ldi2
		ldi	@0, byte1(@2)
		ldi	@1, byte2(@2)
.endmacro

; Load 3-byte immediate
.macro ldi3
		ldi	@0, byte1(@3)
		ldi	@1, byte2(@3)
		ldi	@2, byte3(@3)
.endmacro

; Register out to any address (memory-mapped if necessary)
.macro outr
	.if @0 < 64
		out	@0, @1
	.else
		sts	@0, @1
	.endif
.endmacro

; Register in from any address (memory-mapped if necessary)
.macro inr
	.if @1 < 64
		in	@0, @1
	.else
		lds	@0, @1
	.endif
.endmacro

; Immediate out to any port (possibly via @2 as a temporary)
.macro outi
	.if @1
		ldi	@2, @1
		outr	@0, @2
	.else
		outr	@0, ZH
	.endif
.endmacro
