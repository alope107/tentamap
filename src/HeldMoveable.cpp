#include "aub/tribool.h"

#include "HeldMoveable.h"


namespace tent {

bn::fixed_point HeldMoveable::nextPosition()  {
    return _sprite.position() + bn::fixed_point{
        aub::triboolHeld(bn::keypad::key_type::RIGHT, bn::keypad::key_type::LEFT, _speed),
        aub::triboolHeld(bn::keypad::key_type::DOWN, bn::keypad::key_type::UP, _speed),
    };
}

}