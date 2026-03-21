#pragma once

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>

namespace tent {

class Moveable {
    public:
        Moveable(bn::sprite_ptr sprite, bn::fixed speed) :
            _sprite(sprite),
            _speed(speed) 
            {};

        void update() { _sprite.set_position(nextPosition()); };

        virtual bn::fixed_point nextPosition() = 0;

        virtual ~Moveable() {};
    protected:
        bn::sprite_ptr _sprite;
        bn::fixed _speed;

        
};

}