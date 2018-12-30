SRC += othi.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += tap_dance.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	SRC += rgb_light.c
endif
EXTRAFLAGS += -flto			# Used to make code smaller

# ENABLE
UNICODE_ENABLE = yes	# Used for unicode character emulation
EXTRAKEY_ENABLE = yes 	# OS signals like volume control
TAP_DANCE_ENABLE = yes
RGBLIGHT_ENABLE = yes

# DISABLE
ifndef BLUETOOTH_ENABLE
	BLUETOOTH_ENABLE = no 	# No bluetooth
endif
COMMAND_ENABLE = no			# Some bootmagic thing i dont use
BOOTMAGIC_ENABLE = no 		# Access to EEPROM settings, not needed
CONSOLE_ENABLE = no			# Allows console output with a command
SLEEP_LED_ENABLE = no  		# Breathes LED's when computer is asleep. Untested.
NKRO_ENABLE = no 			# Default is 6KRO which is plenty
MIDI_ENABLE = no 			# Untested feature
FAUXCLICKY_ENABLE = no 		# Emulates clicks using speaker
KEY_LOCK_ENABLE = no 		# Allows locking any key. Not used
API_SYSEX_ENABLE = no 		# Allows OS to send signals.

