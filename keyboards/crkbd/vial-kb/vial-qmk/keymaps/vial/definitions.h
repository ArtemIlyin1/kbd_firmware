#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "quantum.h"
// #include "lib/oledkit/oledkit.h"
// #include "lib/keyball/keyball.h"
// #include "send_string_keycodes.h"

enum LAYERS  {
    U_BASE,
    U_EXTRA,
    U_TAP,
    U_BUTTON,
    U_NAV,
    U_MOUSE,
    U_MEDIA,
    U_NUM,
    U_SYM,
    U_FUN
};

enum custom_keycodes {
    // Add your layer names here if they are in a different enum
    // _BASE, _NAV, etc...

    // Universal editing keys
    U_CUT = SAFE_RANGE,
    U_CPY,
    U_PST,
    U_UND,
    U_RDO,

    // language things
    U_DOT,
    U_COMM,
    U_YO,
    LANG_SW,

    // OS Toggle Key
    OS_SWAP,

    SNIPE_MODE_TO
};

enum tapDance {
    // Tap Dance
    U_TD_BOOT,
    // Layers
    U_TD_U_BASE,
    U_TD_U_EXTRA,
    U_TD_U_TAP,
    U_TD_U_BUTTON,
    U_TD_U_NAV,
    U_TD_U_MOUSE,
    U_TD_U_MEDIA,
    U_TD_U_NUM,
    U_TD_U_SYM,
    U_TD_U_FUN
};

//
// --- Global Variable Declarations ---
// We declare the variables here with 'extern' to tell other files
// that they exist and are defined elsewhere (in logic.c).
//

extern bool is_mac;
extern bool is_russian;
extern enum LAYERS active_default_layer;
#define TAP_DANCE_ACTIONS_SIZE 11
extern tap_dance_action_t tap_dance_actions[TAP_DANCE_ACTIONS_SIZE];
extern os_variant_t current_os;

// #define KEY_OVERRIDE_COUNT 1
// extern const key_override_t *key_overrides[KEY_OVERRIDE_COUNT + 1];

#define TD_SET_LAYER(layer) \
  { .fn = { NULL, set_default_layer_td, NULL }, .user_data = (void*)(uintptr_t)layer }

void set_default_layer_td(tap_dance_state_t *state, void *user_data);
void u_td_fn_boot(tap_dance_state_t *state, void *user_data);


#endif // DEFINITIONS_H
