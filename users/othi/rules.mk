SRC += othi.c \
       process_records.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += tap_dance.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	SRC += rgb_light.c
endif
EXTRAFLAGS += -flto			# Used to make code smaller

