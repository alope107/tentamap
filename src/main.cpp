#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_regular_bg_ptr.h>

#include "bn_regular_bg_items_platforms.h"
#include "bn_sprite_items_robot.h"


int main() {
    bn::core::init();

    auto bg = bn::regular_bg_items::platforms.create_bg();

    auto robot = bn::sprite_items::robot.create_sprite();

    while(true) {
        bn::core::update();
    }
}
