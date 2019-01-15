# UniGo66 receiver

	make UniGo66:default

	dfu-programmer atmega32u4 erase --force
	dfu-programmer atmega32u4 flash .build/UniGo66_default.hex
	dfu-programmer atmega32u4 reset