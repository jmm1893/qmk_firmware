
#include QMK_KEYBOARD_H

#define _BASE 0

enum custom_keycodes {
    // COPY = SAFE_RANGE,
    PASTE = SAFE_RANGE,
    TIMESTAMP,
    LATLONG,
    LEDSWITCH
};

// double tap kemap
enum double_tap {
  COPY, LOG
};

void dance_copy_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count ==1){
    register_code16(KC_LGUI);
    register_code16(KC_C);
  }
    else{
      register_code16(KC_S);
    }
  }

void dance_copy_reset(qk_tap_dance_state_t  *state, void *user_data) {
  if (state->count == 1) {
    unregister_code16(KC_LGUI);
    unregister_code16(KC_C);
  }
    else {
      unregister_code16(KC_S);
    }
}

void dance_log_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count ==1){
    register_code16(KC_LCTL);
    register_code16(KC_LSFT);
    register_code16(KC_L);
  }
    else{
      register_code16(KC_LCTL);
      register_code16(KC_LSFT);
      register_code16(KC_SLSH);
    }
  }

void dance_log_reset(qk_tap_dance_state_t  *state, void *user_data) {
  if (state->count == 1) {
    unregister_code16(KC_LCTL);
    unregister_code16(KC_LSFT);
    unregister_code16(KC_L);
  }
    else {
      unregister_code16(KC_LCTL);
      unregister_code16(KC_LSFT);
      unregister_code16(KC_SLSH);
    }
}



qk_tap_dance_action_t tap_dance_actions[] = {
  [COPY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_copy_finished, dance_copy_reset),
  [LOG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_log_finished, dance_log_reset),
};


bool toggle = true;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case COPY:
        if (record->event.pressed) {
            register_code(KC_LGUI);
            register_code(KC_C);
        } else {
            unregister_code(KC_LGUI);
            unregister_code(KC_C);

        }
        break;

    case PASTE:
        if (record->event.pressed) {

            register_code(KC_LCTL);
            register_code(KC_V);
            // register_code(KC_ENT);
        } else {
            unregister_code(KC_LCTL);
            unregister_code(KC_V);
            // unregister_code(KC_ENT);

        }
        break;

    // case LOG:
    //     if (record->event.pressed) {
    //
    //          register_code(KC_LCTL);
    //          register_code(KC_LSFT);
    //          register_code(KC_L);
    //        }
    //        else
    //        {
    //          unregister_code(KC_LCTL);
    //          unregister_code(KC_LSFT);
    //          unregister_code(KC_L);
    //        }
    //        break;

    case TIMESTAMP:
        if (record->event.pressed) {

            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_S);
          }
          else
          {
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_S);
          }
          break;

    case LEDSWITCH:
        if (record->event.pressed) {

            set_scramble_LED(LED_ON);
          }
          else
          {

          }
          break;


    // case LATLONG:
    //     if (record->event.pressed) {
    //
    //         register_code(KC_LCTL);
    //         register_code(KC_LSFT);
    //         register_code(KC_SLSH);
    //       }
    //       else
    //       {
    //         unregister_code(KC_LCTL);
    //         unregister_code(KC_LSFT);
    //         unregister_code(KC_SLSH);
    //       }
    //       break;


    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    TD(COPY), PASTE, LEDSWITCH,
    TD(LOG), TIMESTAMP, KC_SPC
)

};

void matrix_init_user(void) {
  set_scramble_LED(LED_OFF);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
          tap_code16(LCTL(KC_RIGHT));
      } else {
          tap_code16(LCTL(KC_LEFT));
      }
      return true;
}
