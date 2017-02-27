# This Makefile is compatible with both BSD and GNU make

ASM?= avra
SHELL = /bin/bash

.SUFFIXES: .inc .hex


ALL_TARGETS = afro afro2 afro_hv nfet arctictiger birdie70a bs_nfet bs bs40a dlu40a dlux dys_nfet hk200a hm135a hxt200a kda kda_8khz kda_nfet kda_nfet_ni mkblctrl1 rb50a rb70a rb70a2 rct50a tbs tbs_hv tp tp_8khz tp_i2c tp_nfet tp70a tgy6a tgy_8mhz tgy
AUX_TARGETS = afro_pr0 afro_pr1 diy0

all: $(ALL_TARGETS)

$(ALL_TARGETS):
	$(ASM) -fI -o $@ -D $@_esc -e $@.eeprom -d $@.obj tgy.asm

$(AUX_TARGETS): 

test: all

clean:
	-rm -rf $(ALL_TARGETS) *.cof *.obj *.eep.hex *.eeprom

binary_zip: $(ALL_TARGETS)
	TARGET="tgy_`date '+%Y-%m-%d'`_`git rev-parse --verify --short HEAD`"; \
	mkdir "$$TARGET" && \
	cp $(ALL_TARGETS) "$$TARGET" && \
	git archive -9 --prefix="$$TARGET/" -o "$$TARGET".zip HEAD && \
	zip -9 "$$TARGET".zip "$$TARGET"/*.hex && ls -l "$$TARGET".zip; \
	rm -f "$$TARGET"/*.hex; \
	rmdir "$$TARGET"

program_tgy_%: %.hex
	avrdude -c stk500v2 -b 9600 -P /dev/ttyUSB0 -u -p m8 -U flash:w:$<:i

program_usbasp_%: %.hex
	avrdude -c usbasp -B.5 -p m8 -U flash:w:$<:i

program_avrisp2_%: %.hex
	avrdude -c avrisp2 -p m8 -U flash:w:$<:i

program_jtag3isp_%: %.hex
	avrdude -c jtag3isp -p m8 -U flash:w:$<:i

program_dragon_%: %.hex
	avrdude -c dragon_isp -p m8 -P usb -U flash:w:$<:i

program_dapa_%: %.hex
	avrdude -c dapa -p m8 -U flash:w:$<:i

program_uisp_%: %.hex
	uisp -dprog=dapa --erase --upload --verify -v if=$<

bootload_usbasp:
	avrdude -c usbasp -u -p m8 -U hfuse:w:`avrdude -c usbasp -u -p m8 -U hfuse:r:-:h | sed -n '/^0x/{s/.$$/a/;p}'`:m

read: read_tgy

read_tgy:
	avrdude -c stk500v2 -b 9600 -P /dev/ttyUSB0 -u -p m8 -U flash:r:flash.hex:i -U eeprom:r:eeprom.hex:i

read_usbasp:
	avrdude -c usbasp -u -p m8 -U flash:r:flash.hex:i -U eeprom:r:eeprom.hex:i

read_avrisp2:
	avrdude -c avrisp2 -p m8 -P usb -v -U flash:r:flash.hex:i -U eeprom:r:eeprom.hex:i

read_jtag3isp:
	avrdude -c jtag3isp -p m8 -P usb -v -U flash:r:flash.hex:i -U eeprom:r:eeprom.hex:i

read_dragon:
	avrdude -c dragon_isp -p m8 -P usb -v -U flash:r:flash.hex:i -U eeprom:r:eeprom.hex:i

read_dapa:
	avrdude -c dapa -p m8 -v -U flash:r:flash.hex:i -U eeprom:r:eeprom.hex:i

read_uisp:
	uisp -dprog=dapa --download -v of=flash.hex
