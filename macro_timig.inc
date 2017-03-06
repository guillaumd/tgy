

; Short cycle delay without clobbering flags
.equ	MAX_BUSY_WAIT_CYCLES	= 32
.macro cycle_delay
.if @0 >= MAX_BUSY_WAIT_CYCLES
.error "cycle_delay too long"
.endif
.if @0 > 0
	.if @0 & 1
		nop
	.endif
	.if @0 & 2
		rjmp	PC + 1
	.endif
	.if @0 & 4
		rjmp	PC + 1
		rjmp	PC + 1
	.endif
	.if @0 & 8
		nop
		rcall	wait_ret		; 3 cycles to call + 4 to return
	.endif
	.if @0 & 16
		rjmp	PC + 1
		rcall	wait_ret
		rcall	wait_ret
	.endif
.endif
.endmacro
