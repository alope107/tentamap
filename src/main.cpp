#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_regular_bg_ptr.h>
#include <bn_regular_bg_map_cell_info.h>
#include <bn_log.h>

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

    auto robot = bn::sprite_items::robot.create_sprite();

    auto bg = bn::regular_bg_items::platforms.create_bg();
    auto map = bn::regular_bg_items::platforms.map_item();
    auto validCell = map.cell(0, 0);
    int validTileIndex = bn::regular_bg_map_cell_info(validCell).tile_index();

    bn::fixed speed = 1;

    while(true) {
        bn::fixed_point delta = { 
            moveTribool(bn::keypad::key_type::RIGHT, bn::keypad::key_type::LEFT, speed),
            moveTribool(bn::keypad::key_type::DOWN, bn::keypad::key_type::UP, speed)
        };

        bn::fixed_point newPos = {robot.position() + delta};

        //
        bn::regular_bg_map_cell mapCell = map.cell({(newPos.x() / 8).round_integer() + ((256/2) / 8),
                                                    (newPos.y() / 8).round_integer() + ((256/2) / 8)});

        int cellIdx = bn::regular_bg_map_cell_info(mapCell).tile_index();


        if(cellIdx != validTileIndex) {
            BN_LOG("Boop");
        } else {
            BN_LOG("nah");
            robot.set_position(newPos);
        }
        

        bn::core::update();
    }
}
