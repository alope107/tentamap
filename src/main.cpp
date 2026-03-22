#include <bn_core.h>
#include <bn_point.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_regular_bg_ptr.h>
#include <bn_regular_bg_map_cell_info.h>
#include <bn_log.h>

#include "bn_regular_bg_items_platforms.h"
#include "bn_sprite_items_boxette.h"
#include "bn_sprite_items_robot.h"

#include "aub/tribool.h"

#include "Boxette.h"
#include "Robot.h"




int main() {
    bn::core::init();


    

 
    auto bg = bn::regular_bg_items::platforms.create_bg();
    auto map = bn::regular_bg_items::platforms.map_item();
    bn::regular_bg_map_cell validCell = map.cell(0, 0);
    int validTileIndex = bn::regular_bg_map_cell_info(validCell).tile_index();

    auto bb = tent::Boxette(map);

    auto snapper = bn::sprite_items::boxette.create_sprite();

    bn::point snapperPos = {10, 10};

    while(true) {
        auto newSnapperPos = snapperPos;

        newSnapperPos += {
            aub::triboolPressed(bn::keypad::key_type::RIGHT, bn::keypad::key_type::LEFT, 1),
            aub::triboolPressed(bn::keypad::key_type::DOWN, bn::keypad::key_type::UP, 1)
        };

        int newTile = bn::regular_bg_map_cell_info(map.cell(newSnapperPos)).tile_index();

        if (newTile == validTileIndex) {
            snapperPos = newSnapperPos;
        }

        snapper.set_position(snapperPos*8 - bn::point((256/2) - 4, (256/2) - 4));

        bb.update();
        bn::core::update();
    }
}
