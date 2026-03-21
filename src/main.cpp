#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_regular_bg_ptr.h>

#include "bn_regular_bg_items_platforms.h"
#include "bn_sprite_items_robot.h"

inline bn::fixed tribool(bool p, bool q, bn::fixed magnitude) {
    return p ? magnitude : q ? -magnitude : 0;
}

inline bn::fixed moveTribool(bn::keypad::key_type p, bn::keypad::key_type q, bn::fixed magnitude) {
    return tribool(bn::keypad::held(p), bn::keypad::held(q), magnitude);
}


int main() {
    bn::core::init();

    auto bg = bn::regular_bg_items::platforms.create_bg();

    auto robot = bn::sprite_items::robot.create_sprite();

    bn::fixed speed = 2;

    while(true) {
        bn::fixed_point delta = { 
            moveTribool(bn::keypad::key_type::RIGHT, bn::keypad::key_type::LEFT, speed),
            moveTribool(bn::keypad::key_type::DOWN, bn::keypad::key_type::UP, speed)
        };

        robot.set_position(robot.position() + delta);

        bn::core::update();
    }
}
