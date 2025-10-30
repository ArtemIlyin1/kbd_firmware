#include "definitions.h"

bool is_russian = false;
enum LAYERS active_default_layer = U_BASE;
// bool is_snipe_mode = false;
os_variant_t current_os = OS_WINDOWS;


//
// --- Tap Dance Logic ---
// //
// tap_dance_action_t tap_dance_actions[TAP_DANCE_ACTIONS_SIZE] = {
//     // The bootloader/reset function is unique, so we keep it as is.
//     [U_TD_BOOT]     = ACTION_TAP_DANCE_FN(u_td_fn_boot),
//     // All layer setters now use our generic function and helper macro.
//     [U_TD_U_BASE]   = TD_SET_LAYER(U_BASE),
//     [U_TD_U_EXTRA]  = TD_SET_LAYER(U_EXTRA),
//     [U_TD_U_TAP]    = TD_SET_LAYER(U_TAP),
//     [U_TD_U_BUTTON] = TD_SET_LAYER(U_BUTTON),
//     [U_TD_U_NAV]    = TD_SET_LAYER(U_NAV),
//     [U_TD_U_MOUSE]  = TD_SET_LAYER(U_MOUSE),
//     [U_TD_U_MEDIA]  = TD_SET_LAYER(U_MEDIA),
//     [U_TD_U_NUM]    = TD_SET_LAYER(U_NUM),
//     [U_TD_U_SYM]    = TD_SET_LAYER(U_SYM),
//     [U_TD_U_FUN]    = TD_SET_LAYER(U_FUN)
// };

void install_tap_dance_entries(void) {
    vial_tap_dance_entry_t td0 = { KC_NO, // Change layers
                                   KC_NO,
                                   QK_BOOT,
                                   KC_NO,
                                   TAPPING_TERM };
    vial_tap_dance_entry_t td1 = { KC_NO, // / [ ? ]
                                   KC_NO,
                                   DF(U_BASE),
                                   KC_NO,
                                   TAPPING_TERM };
    vial_tap_dance_entry_t td2 = { KC_NO, // / [ ? ]
                                   KC_NO,
                                   DF(U_EXTRA),
                                   KC_NO,
                                   TAPPING_TERM };
    vial_tap_dance_entry_t td3 = { KC_NO, // / [ ? ]
                                   KC_NO,
                                   DF(U_TAP),
                                   KC_NO,
                                   TAPPING_TERM };
    vial_tap_dance_entry_t td4 = { KC_NO, // / [ ? ]
                                   KC_NO,
                                   DF(U_BUTTON),
                                   KC_NO,
                                   TAPPING_TERM };
    vial_tap_dance_entry_t td5 = { KC_NO, // / [ ? ]
                                   KC_NO,
                                   DF(U_NAV),
                                   KC_NO,
                                   TAPPING_TERM };
    vial_tap_dance_entry_t td6 = { KC_NO, // / [ ? ]
                                   KC_NO,
                                   DF(U_MOUSE),
                                   KC_NO,
                                   TAPPING_TERM };
    vial_tap_dance_entry_t td7 = { KC_NO, // / [ ? ]
                                   KC_NO,
                                   DF(U_MEDIA),
                                   KC_NO,
                                   TAPPING_TERM };
    vial_tap_dance_entry_t td8 = { KC_NO, // / [ ? ]
                                   KC_NO,
                                   DF(U_NUM),
                                   KC_NO,
                                   TAPPING_TERM };
    vial_tap_dance_entry_t td9 = { KC_NO, // / [ ? ]
                                   KC_NO,
                                   DF(U_SYM),
                                   KC_NO,
                                   TAPPING_TERM };
    vial_tap_dance_entry_t td10 = { KC_NO, // / [ ? ]
                                   KC_NO,
                                   DF(U_FUN),
                                   KC_NO,
                                   TAPPING_TERM };
    vial_tap_dance_entry_t td11 = { KC_NO, // / [ ? ]
                                   KC_NO,
                                   LANG_SW,
                                   KC_NO,
                                   TAPPING_TERM };


    dynamic_keymap_set_tap_dance(0, &td0); // the first value corresponds to the TD(i) slot
    dynamic_keymap_set_tap_dance(1, &td1);
    dynamic_keymap_set_tap_dance(2, &td2);
    dynamic_keymap_set_tap_dance(3, &td3);
    dynamic_keymap_set_tap_dance(4, &td4);
    dynamic_keymap_set_tap_dance(5, &td5);
    dynamic_keymap_set_tap_dance(6, &td6);
    dynamic_keymap_set_tap_dance(7, &td7);
    dynamic_keymap_set_tap_dance(8, &td8);
    dynamic_keymap_set_tap_dance(9, &td9);
    dynamic_keymap_set_tap_dance(10, &td10);
    dynamic_keymap_set_tap_dance(11, &td11);
}

void keyboard_post_init_user(void) {
    install_tap_dance_entries();
}

void set_default_layer_td(tap_dance_state_t *state, void *user_data) {
  // We only act on a double tap, just like before.
  if (state->count == 2) {
    // The 'user_data' pointer is repurposed to carry our layer number.
    // We safely cast it back to an integer.
    uint8_t layer = (uint8_t)(uintptr_t)user_data;

    // Now we use the 'layer' variable to set the default layer.
    default_layer_set((layer_state_t)1 << layer);
    active_default_layer = layer;
  }
}

// double tap to activate
void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

void os_swap_animation(os_variant_t os) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    // This logic is now centralized here.
    if (os == OS_MACOS || os == OS_IOS) {
        // White is saturation 0, max value
        rgb_matrix_sethsv_noeeprom(HSV_CYAN);
    } else if (os == OS_WINDOWS) {
        // Blue is a hue of ~170, full saturation, max value
        rgb_matrix_sethsv_noeeprom(HSV_MAGENTA);
    } else if (os == OS_LINUX) {
        // Green is a hue of ~120, full saturation, max value
        rgb_matrix_sethsv_noeeprom(HSV_GREEN);
    } else if (os == OS_UNSURE) {
        // Yellow is a hue of ~60, full saturation, max value
        rgb_matrix_sethsv_noeeprom(HSV_RED);
    }
    uprintf("os swap\n");
#endif
}

// Process detected host OS user (requires few hundred milliseconds)
bool process_detected_host_os_user (os_variant_t detected_os) {
    // print detected os
    print("Detected OS: ");
    print(detected_os == OS_MACOS ? "MacOS" : detected_os == OS_WINDOWS ? "Windows" : detected_os == OS_LINUX ? "Linux" : "Unknown");
    os_swap_animation(detected_os);
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            // rgb_matrix_set_color_all(RGB_WHITE);
            current_os = detected_os;
            uprintf("DETECTED Mac OS");

            break;
        case OS_WINDOWS:
            // rgb_matrix_set_color_all(RGB_BLUE);
            current_os = detected_os;
            uprintf("DETECTED Windows OS");
            break;
        case OS_LINUX:
            // rgb_matrix_set_color_all(RGB_ORANGE);
            current_os = detected_os;
            uprintf("DETECTED Linux OS");
            break;
        case OS_UNSURE:
            uprintf("DETECTED Unknown OS");
            break;
    }

    return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool is_mac = current_os == OS_MACOS;
    if (record->event.pressed) { // Only run this logic when the key is pressed down
        switch (keycode) {
            case U_CPY: // Our custom copy key
                if (is_mac) {
                    register_code16(G(KC_C)); // Send Left GUI (Command) + C
                } else {
                   register_code16(LCTL(KC_C)); // Send Left Control + C
                }
                return false; // We've handled this key, don't process it further

            case U_PST: // Our custom paste key
                if (is_mac) {
                    register_code16(G(KC_V)); // Send Left GUI (Command) + V
                } else {
                    register_code16(C(KC_V)); // Send Left Control + V
                }
                return false;

            case U_CUT: // Our custom cut key
                if (is_mac) {
                    register_code16(G(KC_X)); // Send Left GUI (Command) + X
                } else {
                    register_code16(C(KC_X)); // Send Left Control + X
                }
                return false;

            case U_UND: // Our custom undo key
                if (is_mac) {
                    register_code16(G(KC_Z)); // Send Left GUI (Command) + Z
                } else {
                    register_code16(C(KC_Z)); // Send Left Control + Z
                }
                return false;

            case U_RDO: // Our custom redo key
                if (is_mac) {
                    register_code16(LSG(KC_Z));// Send Left GUI (Command) + Z
                } else {
                    register_code16(RCS(KC_Z)); // Send Left Control + Z
                }

            // case OS_SWAP: // Our OS toggle key
            //     is_mac = !is_mac; // Flip the boolean value
            //     // eeconfig_update_user_with_value(0, is_mac); // Save the new value to EEPROM
            //     // Optional: add feedback like a sound or LED change
            //     os_swap_animation(is_mac);
            //     return false;

            case U_DOT:
                if (is_mac) {
                    register_code16(S(KC_7)); // <-- REPLACE with your Mac Russian Dot keycode
                } else {
                    register_code16(KC_SLSH); // <-- REPLACE with your Windows Russian Dot keycode
                }

                return false;

            case U_COMM:
                if (is_russian) {
                    // Russian Comma Logic
                    if (is_mac) {
                        register_code16(S(KC_6)); // <-- REPLACE with your Mac Russian Comma keycode
                    } else {
                        register_code16(S(KC_SLSH)); // <-- REPLACE with your Windows Russian Comma keycode
                    }
                } else {
                    // English Comma (standard)
                    register_code16(KC_COMM);
                }
                return false;

            case LANG_SW:
                // 1. Toggle the language state
                is_russian = !is_russian;
                // eeconfig_update_user_with_value(1, is_russian); // Save to address 1

                // 2. Change the keyboard layer
                if (is_russian) {
                    default_layer_set((layer_state_t)1 << U_EXTRA);
                    active_default_layer = U_EXTRA;
                } else {
                    default_layer_set((layer_state_t)1 << U_BASE);
                    active_default_layer = U_BASE;
                }

                // 3. Send the OS command to switch language
                if (is_mac) {
                    register_code16(G(KC_SPC)); // Command + Space for macOS
                } else {
                    register_code16(A(KC_LSFT)); // Alt + Shift for Windows (check your OS settings)
                }
                return false; // We will unregister this complex key on release

            // case SNIPE_MODE_TO:
            //     if (!is_snipe_mode) {
            //         is_snipe_mode = true;
            //         // Enable Snipe Mode
            //         keyball_set_cpi(KEYBALL_CPI_SNIPE_MODE / 100); // Example: Set CPI to 800 for Snipe Mode
            //     } else {
            //         is_snipe_mode = false;
            //         // Disable Snipe Mode
            //         keyball_set_cpi(KEYBALL_CPI_DEFAULT / 100); // Reset to default CPI
            //     }

            //     return false;
        }
    } else { // On key release
         switch (keycode) {
            case U_CPY:
                if (is_mac) { unregister_code16(G(KC_C)); } else { unregister_code16(LCTL(KC_C));}
                break;
            case U_PST:
                if (is_mac) { unregister_code16(G(KC_V)); } else { unregister_code16(C(KC_V)); }
                break;
            case U_CUT:
                if (is_mac) { unregister_code16(G(KC_X)); } else { unregister_code16(C(KC_X)); }
                break;
            case U_UND:
                if (is_mac) { unregister_code16(G(KC_Z)); } else { unregister_code16(C(KC_Z)); }
                break;
            case U_RDO:
                if (is_mac) { unregister_code16(LSG(KC_Z)); } else { unregister_code16(RCS(KC_Z)); }
                break;
            case U_DOT:
                // Unregister all possibilities to be safe
                if (is_mac) {
                    unregister_code16(S(KC_7));
                } else {
                    unregister_code16(KC_SLSH);
                }
                break;
            case U_COMM:
                unregister_code16(S(KC_6));
                unregister_code16(S(KC_SLSH));
                unregister_code16(KC_COMM);
                break;
            case LANG_SW:
                // Unregister the OS switch command
                unregister_code16(G(KC_SPC));
                unregister_code16(A(KC_LSFT));
                break;
         }
    }
    return true; // Process all other keys normally
};

// Hanlding copy-paste and other OS/language-specific lkey_to_sendlkey_to_sendcommands
