#pragma once

#define VIAL_KEYBOARD_UID {0x89, 0x36, 0x2A, 0xC7, 0xFA, 0xD8, 0x89, 0x45}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 10
#undef VIAL_TAP_DANCE_ENTRIES
#define VIAL_TAP_DANCE_ENTRIES 32

// default but used in macros
#undef TAPPING_TERM
#define TAPPING_TERM 200

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

#undef NO_AUTO_SHIFT_ALPHA
#define NO_AUTO_SHIFT_ALPHA
#undef AUTO_SHIFT_TIMEOUT
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#undef AUTO_SHIFT_NO_SETUP
#define AUTO_SHIFT_NO_SETUP

#define OS_DETECTION_KEYBOARD_RESET
#define OS_DETECTION_SINGLE_REPORT
