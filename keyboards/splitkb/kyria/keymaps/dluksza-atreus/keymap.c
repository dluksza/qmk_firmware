/* Copyright 2024 Dariusz Luksza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _FUNCTION,
};

// Aliases for readability
#define QWERTY DF(_QWERTY)

#define SYM MO(_SYM)
#define NAV MO(_NAV)
#define FKEYS MO(_FUNCTION)

#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT MT(MOD_LALT, KC_ENT)

// "??????" layer when hold, KC_ESC when tapped
#define SLSH_NUM LT(_SYM, KC_SLSH)
// SYM (symbol) layer when hold, KC_ENT when tapped
#define ESC_SYM LT(SYM, KC_ESC)
// navigation layer when hold, KC_SPC when tapped
#define SPC_NAV LT(_NAV, KC_SPC)
// shift when hold, KC_A when tapped
#define GRV_SFT LSFT_T(KC_GRV)
// shift when hold, KC_SCLN when tapped
#define SCLN_SFT LSFT_T(KC_SCLN)
// OPT+GUI when hold, KC_TAB when tapped
#define MOD_TAB LAG_T(KC_TAB)
// "(" on press, ")" with SFT
#define PAREN KC_LPRN
// Browser back
#define BBACK LGUI(KC_LBRC)
// Browser forward
#define BFORW LGUI(KC_RBRC)
// Previous tab
#define TPREV SGUI(KC_LBRC)
// Next tab
#define TNEXT SGUI(KC_RBRC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,--------------------------------------------.                               ,----------------------------------------------.
 * |  (  )  |   Q   |   W  |   E  |   R  |   T  |                               |   Y   |   U  |   I  |   O   |   P   |  { }   |
 * |--------+-------+------+------+------+------|                               |-------+------+------+-------+-------+--------|
 * |  `  ~  |A/LShft|   S  |   D  |   F  |   G  |                               |   H   |   J  |   K  |   L   |;/LShft|Ctrl/' "|
 * |--------+-------+------+------+------+------+--------------.  ,-------------+-------+------+------+-------+-------+--------|
 * |  Tab   |   Z   |   X  |   C  |   V  |   B  | [  {  | |  \ |  |      |  ] } |   N   |   M  | ,  < | .  >  |/ ?/NUM|   ↲    |
 * `-----------------------+------+------+------+-------+------|  |------+------+-------+------+------+------------------------'
 *                         | Ctrl | LGUI | Bksp |Esc/SYM|      |  | Del  | Ctrl |Spc/NAV| AltGr|      |
 *                         `-----------------------------------'  `-----------------------------------'
 */
    [_QWERTY] = LAYOUT(
                       PAREN  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y  ,   KC_U ,  KC_I ,   KC_O ,  KC_P  , KC_LCBR,
     GRV_SFT, KC_A,   KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H  ,   KC_J ,  KC_K ,   KC_L ,SCLN_SFT,CTL_QUOT,
     MOD_TAB, KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LBRC,KC_BSLS,     _______, KC_RBRC, KC_N  ,   KC_M ,KC_COMM, KC_DOT ,SLSH_NUM, KC_ENT ,
                               KC_LCTL, KC_LGUI, KC_BSPC, ESC_SYM,_______,      KC_DEL, KC_LCTL,SPC_NAV, KC_RALT, _______
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Home | End  |      | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |   ←  |   ↓  |   ↑  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | PgDn |M Prev|M Play|M Next| Pause|        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_END , _______,  TPREV,  TNEXT,
      _______, _______, _______, _______, _______, _______,                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT,  BBACK,  BFORW,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_MPRV, KC_MPLY, KC_MNXT,_______,_______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |   _  |  7   |  8   |  9   |  \   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |   =  |  4   |  5   |  6   |  |   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      | P_TAB| Back |  |Forwar| N_TAB|   -  |  1   |  2   |  3   |  ⇓   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |  0   |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                                LSFT(KC_MINS),   KC_7 , KC_8 , KC_9 , KC_BSLS, KC_EQL ,
     _______, _______, _______, _______, _______, _______,                                      KC_PEQL,   KC_4 , KC_5 , KC_6 , _______, KC_PLUS,
     _______, _______, _______, _______, _______, _______, TPREV  , BBACK  ,  BFORW  , TNEXT  , KC_MINS,   KC_1 , KC_2 , KC_3 , _______, _______,
                                _______, _______, _______, _______, _______,  _______, _______, _______,   KC_0, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |  F4  |  F5  |  F6  |  F11 |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |  F1  |  F2  |  F3  |  F12 |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F7, KC_F8, KC_F9, KC_F10, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F4, KC_F5, KC_F6, KC_F11, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F1, KC_F2, KC_F3, KC_F12, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

const key_override_t right_parentacy = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_RPRN);
const key_override_t curly_braces = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_RCBR);

const key_override_t **key_overrides = (const key_override_t *[]){
    &right_parentacy,
    &curly_braces,
    NULL, // Null terminate the array of overrides!
};
