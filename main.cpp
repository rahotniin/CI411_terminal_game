#include <iostream>
#include <string>
#include <vector>

// My files
#include "graphics.h"
#include "input.h"
#include "int2.h"
#include "Quad.h"
#include "GameObject.h"
#include "menus.h"

//=============================================//

// the bounded area the player can move around inside
Quad play_area = Quad::from_xywh(0, 0, 60, 30);

// quad representing the stat block in-game
Quad stat_quad = Quad::from_xywh(60, 0, 60, 3);

//=============================================//

// prints the stat-block to the terminal
void display_stats() {
    graphics::draw_quad_outline(stat_quad);

    graphics::draw(63, 0, "STATS");

    graphics::draw(70, 1, "HEALTH:");
    graphics::draw(78, 1, "100", 124);

    graphics::draw(86, 1, "STAMINA:");
    graphics::draw(95, 1, "100", 34);
    
    graphics::draw(104, 1, "MANA:");
    graphics::draw(110, 1, "100", 26);
}

//=============================================//

void move_gameobject(GameObject& obj, Int2 new_pos) {
    graphics::draw(obj.pos, graphics::EMPTY);
    obj.pos = new_pos;
    graphics::draw_gameobject(obj);
}

//=============================================//

// the player character
GameObject pc("Player Character", (char)219, 255, play_area.midpoint());

namespace character_controller {
    // moves the player character given WASD input
    void handle_movement() {
        Int2 movement = input::wasd();
        if (movement != Int2::ZERO) {
            Int2 new_pos = pc.pos + movement;
            if (play_area.exclusive_contains(new_pos)) {
                move_gameobject(pc, new_pos);
            }
        }
    }
}

//=============================================//

int main() {
    graphics::set_terminal_size();
    graphics::hide_cursor();

    menus::start_screen();
    pc.colour = menus::pick_pc_colour();

    //=============================================//

    graphics::draw_quad_outline(play_area);
    
    display_stats();
    
    menus::display_actions();
    graphics::draw_quad_outline(options_quad);
    graphics::draw_quad_outline(info_quad);
    graphics::draw_in_quad(info_quad, Int2(3, 0), "INFO");

    //=============================================//

    graphics::draw_gameobject(pc);

    menus::tutorial();

    //=============================================//

    // main loop
    while(true) {
        menus::handle_menus();
        character_controller::handle_movement();
    }
}
