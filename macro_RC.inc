;-- RC pulse setup and edge handling macros ------------------------------

.if USE_ICP
.macro rcp_int_enable
		in	@0, TIMSK
		sbr	@0, (1<<TICIE1)	; enable icp1_int
		out	TIMSK, @0
.endmacro
.macro rcp_int_disable
		in	@0, TIMSK
		cbr	@0, (1<<TICIE1)	; disable icp1_int
		out	TIMSK, @0
.endmacro
.macro rcp_int_rising_edge
		ldi	@0, T1CLK
		out	TCCR1B, @0
.endmacro
.macro rcp_int_falling_edge
		ldi	@0, T1CLK & ~(1<<ICES1)
		out	TCCR1B, @0
.endmacro
.elif USE_INT0
.macro rcp_int_enable
		ldi	@0, (1<<INT0)	; enable ext_int0
		out	GICR, @0
.endmacro
.macro rcp_int_disable
		out	GICR, ZH	; disable ext_int0
.endmacro
.if USE_INT0 == 1
.macro rcp_int_rising_edge
		ldi	@0, (1<<ISC01)+(1<<ISC00)
		out	MCUCR, @0	; set next int0 to rising edge
.endmacro
.macro rcp_int_falling_edge
		ldi	@0, (1<<ISC01)
		out	MCUCR, @0	; set next int0 to falling edge
.endmacro
.elif USE_INT0 == 2
.macro rcp_int_rising_edge
		ldi	@0, (1<<ISC01)
		out	MCUCR, @0	; set next int0 to falling edge
.endmacro
.macro rcp_int_falling_edge
		ldi	@0, (1<<ISC01)+(1<<ISC00)
		out	MCUCR, @0	; set next int0 to rising edge
.endmacro
.endif
.endif

