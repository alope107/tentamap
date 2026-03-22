#pragma once

#include <bn_fixed.h>
#include <bn_keypad.h>

namespace aub {

    template<typename T>
    inline T tribool(bool p, bool q, T magnitude) {
        return p ? magnitude : q ? -magnitude : T{};
    }

    template<typename T>
    inline T triboolHeld(bn::keypad::key_type p, bn::keypad::key_type q, T magnitude) {
        return tribool(bn::keypad::held(p), bn::keypad::held(q), magnitude);
    }

    template<typename T>
    inline T triboolPressed(bn::keypad::key_type p, bn::keypad::key_type q, T magnitude) {
        return tribool(bn::keypad::pressed(p), bn::keypad::pressed(q), magnitude);
    }

}

