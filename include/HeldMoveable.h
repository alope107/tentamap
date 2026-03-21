#pragma once

#include "Moveable.h"

namespace tent {
class HeldMoveable : public Moveable {
    public:
        HeldMoveable(bn::sprite_ptr sprite, bn::fixed speed) : Moveable(sprite, speed) {};
        
        bn::fixed_point nextPosition() override;
};

}