#include "definitions.h"

bool is_mac = false;
bool is_russian = false;
enum LAYERS active_default_layer = U_BASE;
// bool is_snipe_mode = false;
os_variant_t current_os = OS_WINDOWS;


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
                   register_code16(LCTL(S(KC_C))); // Send Left Control + C
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
                    register_code16(G(KC_Z));// Send Left GUI (Command) + Z
                } else {
                    register_code16(C(KC_Z)); // Send Left Control + Z
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
                if (is_mac) { unregister_code16(G(KC_C)); } else { unregister_code16(LCTL(S(KC_C)));}
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
                if (is_mac) { unregister_code16(G(KC_Z)); } else { unregister_code16(C(KC_Z)); }
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
