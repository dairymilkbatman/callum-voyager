#include QMK_KEYBOARD_H
// #pragma once // do i need this?

#include "oneshot.h"
#include "swapper.h"

#define HOME G(KC_LEFT)
#define END G(KC_RGHT)

// I will use these
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TAB_L G(S(KC_LBRC))
#define TAB_R G(S(KC_RBRC))
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)

#define SPACE_L A(G(KC_LEFT))
#define SPACE_R A(G(KC_RGHT))

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,

    FUN, //add fun layer
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT, //option
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
    // RGB_SLD,
    // SW_LANG, // Switch to next input language (ctl-spc) not needed
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_voyager(
        XXXXXXX, KC_Q,    KC_W,    KC_F,    KC_P,      KC_B,        KC_J, KC_L, KC_U,    KC_Y,      KC_QUOT, XXXXXXX,
        XXXXXXX, KC_A,    KC_R,    KC_S,    KC_T,      KC_G,        KC_M, KC_N, KC_E,    KC_I,      KC_O,    XXXXXXX,
        XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_D,      KC_V,        KC_K, KC_H, KC_COMM, KC_DOT,    KC_SLSH, XXXXXXX,
        XXXXXXX, _______, _______, _______, KC_ESC,    _______,     _______, KC_BSPC, _______, _______, _______,  XXXXXXX,
                                            LA_NAV,    KC_LSFT,     KC_SPACE, LA_SYM
    ),

    [NAV] = LAYOUT_voyager(
        _______, KC_ESC,   SW_WIN,  TAB_L,   TAB_R,   CW_TOGG,         KC_PAGE_UP, KC_HOME, KC_UP,   KC_END,   KC_CAPS,   _______,
        _______, OS_SHFT,  OS_CTRL, OS_ALT,  OS_CMD,  KC_RALT,         KC_PGDN,    KC_LEFT, KC_DOWN, KC_RIGHT, KC_DELETE, _______,
        _______, KC_UNDO,  KC_COPY, KC_CUT,  KC_RGUI, KC_PASTE,        KC_INSERT,  KC_BSPC, KC_TAB,  KC_APP,   KC_PSCR,   _______,
        _______, _______,  _______, _______, KC_ESC,  _______,         _______,    _______, _______, _______,  _______,   _______,
                                             _______, _______,         KC_ENTER, QK_REPEAT_KEY
    ),

    [FUN] = LAYOUT_voyager(
        _______, KC_MPRV,  KC_MSTP,  KC_MPLY,          KC_MNXT, KC_BRMU,                  KC_F12,   KC_F7,    KC_F8,   KC_F9,   RGB_TOG, _______,
        _______, KC_LSFT,  KC_LCTL,  KC_LALT,          KC_LGUI, KC_BRMD,                  KC_F11,   KC_F4,    KC_F5,   KC_F6,   _______, _______,
        _______, KC_MUTE,  KC_VOLD,  LGUI(LSFT(KC_C)), KC_VOLU, LGUI(LSFT(KC_V)),         KC_F10,   KC_F1,    KC_F2,   KC_F3,   _______, _______,
        _______, _______,  _______,  _______,          _______, _______,                  _______,  _______,  _______, _______, _______, _______,
                                                      _______,  _______,                  KC_ENTER, _______
    ),

    [SYM] = LAYOUT_voyager(
        _______, KC_EXLM,        KC_AT,     KC_HASH,    KC_DLR,   KC_PERC,                KC_GRAVE, KC_EQUAL, KC_COLN, KC_SCLN, KC_PLUS, _______,
        _______, KC_LSFT,        KC_LCTL,   KC_LALT,    KC_LGUI,  KC_CIRC,                KC_MINUS, KC_LPRN,  KC_LCBR, KC_LBRC, KC_ASTR, _______,
        _______, KC_LABK,        KC_PIPE,   KC_BSLS,    KC_RABK,  KC_AMPR,                KC_UNDS,  KC_RPRN,  KC_RCBR, KC_RBRC, KC_TILD, _______,
        _______, _______,        _______,   _______,    _______,  _______,                _______,  KC_BSPC,  _______, _______, _______, _______,
                                                        _______,  _______,                _______,  _______
    ),

    [NUM] = LAYOUT_voyager(
        _______, KC_KP_EQUAL,    KC_7,      KC_8,       KC_9,     KC_KP_PLUS,             XXXXXXX,   _______, _______, _______, _______, _______,
        _______, KC_PAST,        KC_4,      KC_5,       KC_6,     KC_KP_MINUS,            KC_RALT,  KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,
        _______, KC_0,           KC_1,      KC_2,       KC_3,     KC_KP_SLASH,            _______,  KC_BSPC, KC_TAB,  _______, KC_APP,  _______,
        _______, _______,        _______,   _______,    KC_DOT,   _______,                _______,  _______, _______, _______, _______, _______,
                                                        _______,  _______,                KC_ENTER, _______

    ),
};



// Both NAV and SYM -on the base layer- can cancel oneshot modifiers.
// This defines keys that are able to cancel a queued OSM. Returns true if the key is a cancel key, false otherwise.
bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

// Determines if a key should be ignored by oneshot modifiers.
// Why is the NUM layer missing from this function? because NUM is a layer activated by tri-layer func and is not a key.
bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:   // Left thumb shift should be ignored by oneshot modifiers.
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
// bool sw_lang_active = false;
// bool lshift_pressed = false;

// Initializes initial oneshot states.
oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

// The below function processes user key events and updates the state of the oneshot modifiers.
// It checks if the key is ignored by oneshot modifiers and updates the state of the oneshot modifiers accordingly.
// I think this function defines SW_WIN, OS_SHIFT, OS_CTRL, OS_ALT, OS_CMD
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    ); // Turns on the window swap modifier when the key is pressed and turns it off when the key is released.

    // I do not need this function, not using language swap.
    // update_swapper(
    //     &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
    //     keycode, record
    // );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    ); // Turns on the shift modifier when the key is pressed and turns it off when the key is released.
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    ); // Turns on the control modifier when the key is pressed and turns it off when the key is released.
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    ); // Turns on the alt modifier when the key is pressed and turns it off when the key is released.
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    ); // Turns on the command modifier when the key is pressed and turns it off when the key is released.

    // redundant with os_shft_state? what if this is null? why should it not be initialized?
    // if (keycode == KC_LSFT) {
    //     lshift_pressed = record->event.pressed;
    // }

    return true;
}


// Sets the layer state based on the current state and the key pressed.
// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, SYM, NAV, NUM);
//     state = update_tri_layer_state(state, SYM, NAV, NUM);
//     state = update_tri_layer_state(state, KC_LSFT, SYM, FUN); // new layer, this method does not accept keycodes.
//     return state;
// }

// this sucks
// layer_state_t layer_state_set_user(layer_state_t state) {
//     state = update_tri_layer_state(state, SYM, NAV, FUN);

//     // Check if any form of shift is active (physical or oneshot)
//     bool shift_active = lshift_pressed ||
//                        (os_shft_state == os_down_unused) ||
//                        (os_shft_state == os_down_used) ||
//                        (os_shft_state == os_up_queued);


//     if (!(layer_state & (1UL << NUM))) {
//         state |= (1UL << FUN);
//     }
//     // Custom logic: SYM + thumb Shift = NUM
//     if (layer_state_cmp(state, SYM) && shift_active) {
//         state |= (1UL << NUM);  // Activate layer
//     } else {
//         state &= ~(1UL << NUM); // Deactivate layer
//     }

//     return state;
// }

// Better way?
// layer_state_t layer_state_set_user(layer_state_t state) {
//     // Update tri-layer state (SYM, NAV, FUN)
//     state = update_tri_layer_state(state, SYM, NAV, FUN);

//     // Check if SYM is active
//     if (layer_state_cmp(state, SYM)) {
//         // If lshift is pressed, and current state is SYM, activate NUM by setting bitmask.
//         if (os_shft_state == os_down_unused) ||
//            (os_shft_state == os_down_used){
//             state |= (1UL << NUM);
//         }

//         // If NAV is active, activate FUN (SYM + NAV)
//         if (layer_state_cmp(state, NAV)) {
//             state |= (1UL << FUN);
//         }
//     } else {
//         // If SYM is not active, deactivate NUM and FUN
//         state &= ~(1UL << NUM);
//         state &= ~(1UL << FUN);
//     }

//     return state;
// }

// final form?
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, SYM, NAV, FUN);

    if (layer_state_cmp(state, SYM)) {
        if (os_shft_state == os_down_unused || os_shft_state == os_down_used) {
            state |= (1UL << NUM);
        }
    } else {
        state &= ~(1UL << NUM);
    }
    return state;
}
