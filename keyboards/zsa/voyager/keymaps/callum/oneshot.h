#pragma once

#include QMK_KEYBOARD_H

// Represents the four states a oneshot key can be in
typedef enum {
    os_up_unqueued,
    os_up_queued,
    os_down_unused,
    os_down_used,
} oneshot_state;

// Custom oneshot mod implementation that doesn't rely on timers. If a mod is
// used while it is held it will be unregistered on keyup as normal, otherwise
// it will be queued and only released after the next non-mod keyup.
void update_oneshot(
    oneshot_state *state, // A pointer to the oneshot_state variable that holds the current state of the oneshot key
    uint16_t mod, // The keycode of the modifier key., eg KC_LCTL
    uint16_t trigger, // The keycode of the trigger key, eg., KC_TAB
    uint16_t keycode, // The keycode of the currently pressed key.
    keyrecord_t *record // A pointer to the keyrecord_t structure for the current key event.
);

// To be implemented by the consumer. Defines keys to cancel oneshot mods.
// Takes a keycode as an argument and returns true if the key should cancel the oneshot mod.
bool is_oneshot_cancel_key(uint16_t keycode);

// To be implemented by the consumer. Defines keys to ignore when determining
// whether a oneshot mod has been used. Setting this to modifiers and layer
// change keys allows stacking multiple oneshot modifiers, and carrying them
// between layers.
bool is_oneshot_ignored_key(uint16_t keycode);
