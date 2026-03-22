#include <bn_regular_bg_map_cell_info.h>

#include "aub/tribool.h"

#include "bn_sprite_items_boxette.h"

#include "Boxette.h"

// TODO: Move the map logic to a better map class
namespace {
int validTileIdx(bn::regular_bg_map_item& map, bn::point& emptyLoc) {
    bn::regular_bg_map_cell validCell = map.cell(emptyLoc);
    return bn::regular_bg_map_cell_info(validCell).tile_index();
}
}

namespace tent {
Boxette::Boxette(bn::regular_bg_map_item& map, bn::point emptyLoc, bn::fixed_point startPos, bn::fixed speed) :
    _sprite(bn::sprite_items::boxette.create_sprite(startPos)),
    _speed(speed),
    _map(map),
    _validTileIdx(validTileIdx(map, emptyLoc)) {}

void Boxette::update() {
    bn::fixed_point delta = { 
        aub::triboolHeld(bn::keypad::key_type::RIGHT, bn::keypad::key_type::LEFT, _speed),
        aub::triboolHeld(bn::keypad::key_type::DOWN, bn::keypad::key_type::UP, _speed)
    };

    bn::fixed_point newPos = {_sprite.position() + delta};

    // Sticky, considers both dimesions at once
    // Does not allow movement if either of them are blocked.
    // if(_validLoc(newPos)) _sprite.set_position(newPos);

    //Hacky glide?
    // TODO: I think this can be done in no more than half the checks
    bn::fixed_point newXPos = {newPos.x(), _sprite.y()};
    if(_validLoc(newXPos)) {
        _sprite.set_position(newXPos);
    } 
    bn::fixed_point newYPos = {_sprite.x(), newPos.y()};
    if(_validLoc(newYPos)) {
        _sprite.set_position(newYPos);
    } 
}

// TODO: consider horiz and vert separately to avoid stickyness?
bool Boxette::_validLoc(bn::fixed_point& newPos) {
    bn::fixed_point subgrid = (newPos + bn::fixed_point{-4 + (256/2), -4 + (256/2)})/8; // TODO: name magic numbers

    // The 4 cells that will be occupied
    // TODO: consider what would need to be done to generalize to larger player sprites
    bn::regular_bg_map_cell mapCells[] = {
        _map.cell(subgrid.x().floor_integer(), subgrid.y().floor_integer()),
        _map.cell(subgrid.x().floor_integer(), subgrid.y().ceil_integer()),
        _map.cell(subgrid.x().ceil_integer(), subgrid.y().floor_integer()),
        _map.cell(subgrid.x().ceil_integer(), subgrid.y().ceil_integer())
    };

    // esnure there's no overlap on any
    for(bn::regular_bg_map_cell mapCell : mapCells) {
        int cellIdx = bn::regular_bg_map_cell_info(mapCell).tile_index();
        if(cellIdx != _validTileIdx) {
            return false;
        }
    }

    return true;
}

}