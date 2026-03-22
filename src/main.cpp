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

#include "Robot.h"



int main() {
    bn::core::init();

    tent::Robot robby = tent::Robot();

    auto robot = bn::sprite_items::boxette.create_sprite();

    auto boxette = bn::sprite_items::boxette.create_sprite();

 
    auto bg = bn::regular_bg_items::platforms.create_bg();
    auto map = bn::regular_bg_items::platforms.map_item();
    bn::regular_bg_map_cell validCell = map.cell(0, 0);
    int validTileIndex = bn::regular_bg_map_cell_info(validCell).tile_index();

    bn::point bPos = {10, 10};

    bn::fixed speed = 1;

    while(true) {
        bn::fixed_point delta = { 
            aub::triboolHeld(bn::keypad::key_type::RIGHT, bn::keypad::key_type::LEFT, speed),
            aub::triboolHeld(bn::keypad::key_type::DOWN, bn::keypad::key_type::UP, speed)
        };

        bn::fixed_point newPos = {robot.position() + delta};
        bn::fixed_point subgrid = (newPos + bn::fixed_point{-4 + (256/2), -4 + (256/2)})/8;

        // bn::fixed subgridx = ((newPos.x() - 4 + (256/2))/8);
        // bn::fixed subgridy = ((newPos.y() - 4 + (256/2))/8);
        bn::regular_bg_map_cell mapCells[] = {
            map.cell(subgrid.x().floor_integer(), subgrid.y().floor_integer()),
            map.cell(subgrid.x().floor_integer(), subgrid.y().ceil_integer()),
            map.cell(subgrid.x().ceil_integer(), subgrid.y().floor_integer()),
            map.cell(subgrid.x().ceil_integer(), subgrid.y().ceil_integer())
        };

        

        bool allClear = true;

        for(bn::regular_bg_map_cell mapCell : mapCells) {
             int cellIdx = bn::regular_bg_map_cell_info(mapCell).tile_index();
             if(cellIdx != validTileIndex) {
                allClear = false;
                break;
             }
        }

        if(allClear) {
            robot.set_position(newPos);
        }


        // if(cellIdx != validTileIndex) {
        //     if(bn::keypad::any_pressed()) {
        //         BN_LOG("Boop ", newPos.x(), " ", snapX);
        //         BN_LOG("Boop", newPos.y(), " ", snapY);
        //     }
            
        // } else {
        //     if(bn::keypad::any_pressed()) {
        //         BN_LOG("nah", newPos.x(), " ", snapX);
        //         BN_LOG("nah", newPos.y(), " ", snapY);
        //     }
        //     robot.set_position(newPos);
        // }


        // bn::regular_bg_map_cell_info(bCell).

        auto newBpos = bPos;

        newBpos += {
            aub::triboolPressed(bn::keypad::key_type::RIGHT, bn::keypad::key_type::LEFT, 1),
            aub::triboolPressed(bn::keypad::key_type::DOWN, bn::keypad::key_type::UP, 1)
        };

        int newTile = bn::regular_bg_map_cell_info(map.cell(newBpos)).tile_index();

        if (newTile == validTileIndex) {
            bPos = newBpos;
        }

        boxette.set_position(bPos*8 - bn::point((256/2) - 4, (256/2) - 4));

        // auto newBCell = {
        //     bCell.x()
        // };

        robby.update();
        bn::core::update();
    }
}
