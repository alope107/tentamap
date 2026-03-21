#pragma once

#include <bn_fixed.h>
#include <bn_keypad.h>

namespace aub {

    inline bn::fixed tribool(bool p, bool q, bn::fixed magnitude) {
        return p ? magnitude : q ? -magnitude : 0;
    }

    inline bn::fixed triboolHeld(bn::keypad::key_type p, bn::keypad::key_type q, bn::fixed magnitude) {
        return tribool(bn::keypad::held(p), bn::keypad::held(q), magnitude);
    }

    inline bn::fixed triboolPressed(bn::keypad::key_type p, bn::keypad::key_type q, bn::fixed magnitude) {
        return tribool(bn::keypad::pressed(p), bn::keypad::pressed(q), magnitude);
    }

}

