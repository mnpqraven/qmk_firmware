## Othi's User-defined configs

###TODO:
- Led in "/home/othi/qmk_firmware/tmk_core/protocol/arm_atsam/led_matrix.c:L409" and backlight support for upcoming Zeal60 PCBs
- Check for EEPROM writing leaks in own's userspace codebase

### Goals
- Colemak layout. If you don't use Colemak then you'll need to also change the arrow key bindigns in other layers

- Vim-like navigation layer so you can use vim binding arrowkeys in non-vim environment

- Good modifier support so you don't have to hold 14 modifier keys at the same time

- RGB indicating layer change(only work with plain colors so far, don't put your rgb to pulsing or any non static animation)

### Layers
- **CL:**

	The base layer, default is Colemak

- **NM_MODE:**

	Vim-like arrowkeys in the home row, it's `LHNE` for *JENK Colemak* and `HJKL` for *QWERTY*

	Also `HOME`, `END` and next/prev word (`Ctrl + Left/Right`) in `0, 4, w, b` like in vim

- **VI_MODE:**

	The same as `NM_MODE` but with `KC_LSFT` held down for mostly highlighting

- **ACCENT + ACCENT_CAP:**

	Function keys on the numrow and Unicode characters

- **FNUM**

	Just funtion keys on the numrow,nothing fancy

- **BRCKS**

	Brackets on the home row
### Modifiers and Tap Dance keys
**LHS:**

- Any Tap Dance key with the format of `TD(XXX_NM)` act as normal XXX modifier upon hold, but will hold **and** put you to `NM_MODE` when double hold(a tap before the hold)(eg you can produce `Alt + PgUp` by pressing `Alt + Alt + U`). Triple holding holds both XXX and Control because the control button is not presented on the HHKB keyboards

- `KC_TAB` acts as both `KC_TAB` on tap and `KC_LGUI` on hold

- R3 Caps Lock sends Control on tap/hold, and sends Backspace on doubles and hammerings

- Holding `KC_Q` also puts you into `NM_MODE`

- Holding Escape turns numrow into function rows

**RHS:**

- 3 keys `KC_SCLN`, `KC_DOT` and `KC_SLSH` in `CL` layer can also be held down for respectively `KC_LCTL`, `KC_LSFT`, `KC_LALT` for easier 2-hand modifier holding

- Right modifiers hold the selected modifier with `KC_LGUI` at the same time, mainly for i3wm, you can change this to whatever combination you want

### Misc. functionalities

**Unicode:**

- Default input mode: Linux

- In case the keyboard output the 4-digit codepoint instead of the actual unicode, you need to change the rewrite input mode of the keyboard into the EEPROM(you only have to do this if the EEPROM was cleared or your current machine use another unicode compose method other than IBus/Linux's `Ctrl + Shift + U`). Change the corresponding Input `void eeconfig_init_user(void)` in `othi.c` . See [this](https://docs.qmk.fm/#/feature_unicode) for availble input modes.

- **NOTE:** make sure to keep your qmk env up to date with upstream
