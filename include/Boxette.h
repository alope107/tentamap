#pragma once

#include <bn_sprite_ptr.h>
#include <bn_fixed_point.h>
#include <bn_point.h>
#include <bn_regular_bg_map_item.h>

namespace tent {
class Boxette {
    public:
        Boxette(bn::regular_bg_map_item& map, bn::point emptyLoc={0, 0},  bn::fixed_point startPos={0, 0}, bn::fixed speed=1);

        void update();

    private:
        bn::sprite_ptr _sprite;
        bn::fixed _speed;
        bn::regular_bg_map_item& _map;
        int _validTileIdx;

        bool _validLoc(bn::fixed_point& newPos);
};
}