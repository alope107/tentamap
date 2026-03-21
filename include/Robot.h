#pragma once

#include "HeldMoveable.h"

#include "bn_sprite_items_robot.h"

namespace tent {
class Robot : public HeldMoveable {
    public:
        static constexpr bn::fixed DEFAULT_SPEED = 2;
        Robot(bn::fixed speed=DEFAULT_SPEED) : 
            HeldMoveable(bn::sprite_items::robot.create_sprite(), speed) {};
};

}