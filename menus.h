#pragma once

#include <string>

#include "graphics.h"
#include "input.h"
#include "Int2.h"
#include "Quad.h"

//=============================================//

enum Menu {
    Actions,
    Options
};

// the currently active/interactable menu
Menu active_menu = Actions;

// the positions of the selection arrows in the actions and options menus
int selection_arrow_pos = 0;
int option_arrow_pos = 0;

int num_options = 0;

// the qaud representing the actions menu
Quad actions_quad = Quad::from_xywh(60, 3, 13, 8);
// the qaud representing the options menu
Quad options_quad = Quad::from_xyXY(73, 3, 119, 0).with_height(8);
// the qaud representing the info 'box' in-game
Quad info_quad = Quad::from_xyXY(60, 11, 119, 29);

//=============================================//

namespace menus {
    // prints the start-screen, asking the player to appropriately size the game window
    void start_screen() {
        Quad game_area = Quad::from_xywh(0, 0, graphics::WIDTH, graphics::HEIGHT);
        graphics::draw_empty_outlined_quad(game_area);

        graphics::draw(25, 12, "                 Welcome to my little terminal game.");
        graphics::draw(25, 14, "Please resize the window until you can see a rectangle around the edges,");
        graphics::draw(25, 16, "                    then press ENTER to continue.");

        input::wait_for_enter();
    }
    
    // prints a menu asking the player to pick the colour of their character
    int pick_pc_colour() {
        int colours[20][12];
        Quad colour_qaud = Quad::from_xywh(0, 0, 20, 12);
        
        int x = 0;
        int y = 0;
        for (int col = 1; col < 256; col++, x++) {
            if (col == 16) { col = 21; } // colours in range 16 through 20 are too dark
            if (col == 231) { col = 241; } // colours in range 231 through 240 are too dark
            
            if (x >= 20) {
                x = 0;
                y++;
            }

            colours[x][y] = col;

            graphics::draw((x * 6) + 1, y, std::to_string(col), col);
        }

        graphics::draw(33, 16, "Use the arrow keys to pick the colour of your character.");
        graphics::draw(33, 18, "           Then press ENTER to continue.");

        Int2 pos(0, 0); // position of the selection arrow
        graphics::draw(pos.x * 6, pos.y, ">");
        while (true) {
            Int2 movement = input::arrow_keys();
            if (movement != Int2::ZERO) {
                Int2 new_pos = pos + movement;

                if (colour_qaud.inclusive_contains(new_pos)) {
                    graphics::draw(pos.x * 6, pos.y, " ");
                    pos = new_pos;
                    graphics::draw(pos.x * 6, pos.y, ">");
                }
            }
            
            if (input::key_state(0x0D)) {
				graphics::clear_terminal();
				return colours[pos.x][pos.y];
			}
        }
    }

    // prints the tutorial info in the 'tutorial' box in the game (the info box has been relabelled 'tutorial' in this case)
    void tutorial() {
        graphics::draw_empty_outlined_quad(info_quad);
        graphics::draw_in_quad(info_quad, Int2(3, 0), "TUTORIAL");
        //                                                                    ┌──TUTORIAL────────────────────────────────────────────────┐
        graphics::draw_in_quad(info_quad, Int2(1, 1), graphics::BULLET_POINT + "Use WASD to move your character");
        graphics::draw_in_quad(info_quad, Int2(1, 2), graphics::BULLET_POINT + "Use the up and down arrow keys to navitage the ACTIONS");
        graphics::draw_in_quad(info_quad, Int2(1, 3),                          " and OPTIONS menus.");
        graphics::draw_in_quad(info_quad, Int2(1, 4), graphics::BULLET_POINT + "Use ENTER to select actions and options.");
        graphics::draw_in_quad(info_quad, Int2(1, 5), graphics::BULLET_POINT + "Use ESCAPE to cancel picking an option.");

        graphics::draw_in_quad(info_quad, Int2(1, 6), graphics::BULLET_POINT + "Button presses are processed only once they have been");
        graphics::draw_in_quad(info_quad, Int2(1, 7),                          " released.");
        graphics::draw_in_quad(info_quad, Int2(1, 8), graphics::BULLET_POINT + "Instead of holding a button down, it must be tapped");
        graphics::draw_in_quad(info_quad, Int2(1, 9),                          " repeatedly.");
        
        graphics::draw_in_quad(info_quad, Int2(1, 12),                         " Handling input with the Windows API is hard...");
    }


    const int NUM_ACTIONS = 4;
    // prints the actions available to the player in the 'actions' menu.
    void display_actions() {
        graphics::draw_quad_outline(actions_quad);
        graphics::draw_in_quad(actions_quad, Int2(3, 0), "ACTIONS");
        
        graphics::draw_in_quad(actions_quad, Int2(1, 1), graphics::BULLET_POINT + "ATTACK");
        graphics::draw_in_quad(actions_quad, Int2(1, 2), graphics::BULLET_POINT + "INSPECT");
        graphics::draw_in_quad(actions_quad, Int2(1, 3), graphics::BULLET_POINT + "TALK");
        graphics::draw_in_quad(actions_quad, Int2(1, 4), graphics::BULLET_POINT + "INVENTORY");

        graphics::draw_in_quad(actions_quad, Int2(1, 1 + selection_arrow_pos), '>');
    }

    // handles the movement of the arrow used to select actions
    void handle_action_selection_arrow() {
        int menu_select_movement = input::up_down_arrow_keys();

        if (menu_select_movement != 0) {
            int new_pos = selection_arrow_pos + menu_select_movement;

            if (new_pos > -1 && new_pos < menus::NUM_ACTIONS) {
                graphics::draw_in_quad(actions_quad, Int2(1, 1 + selection_arrow_pos), graphics::BULLET_POINT);
                selection_arrow_pos = new_pos;
                graphics::draw_in_quad(actions_quad, Int2(1, 1 + selection_arrow_pos), '>');
            }
        }
    }

    // handles the movement of the arrow used to select the options of actions
    void handle_option_selection_arrow() {
        int menu_select_movement = input::up_down_arrow_keys();

        if (menu_select_movement != 0) {
            int new_pos = option_arrow_pos + menu_select_movement;

            if (new_pos > -1 && new_pos < num_options) {
                graphics::draw_in_quad(options_quad, Int2(1, 1 + option_arrow_pos), graphics::BULLET_POINT);
                option_arrow_pos = new_pos;
                graphics::draw_in_quad(options_quad, Int2(1, 1 + option_arrow_pos), '>');
            }
        }
    }

    // Moves the player to options menu of the action currently highlighted by the selection arrow
    void select_action() {
        active_menu = Options;
        graphics::draw_in_quad(actions_quad, Int2(1, 1 + selection_arrow_pos), graphics::BULLET_POINT);
        
        graphics::draw_empty_outlined_quad(options_quad);
        switch (selection_arrow_pos) {
            case 0: {
                // attack
                graphics::draw_in_quad(options_quad, Int2(3, 0), "ATTACK");

                num_options = 4;
                graphics::draw_in_quad(options_quad, Int2(1, 1), graphics::BULLET_POINT + "UP");
                graphics::draw_in_quad(options_quad, Int2(1, 2), graphics::BULLET_POINT + "DOWN");
                graphics::draw_in_quad(options_quad, Int2(1, 3), graphics::BULLET_POINT + "LEFT");
                graphics::draw_in_quad(options_quad, Int2(1, 4), graphics::BULLET_POINT + "RIGHT");
                
                break;
            }
            case 1: {
                // inspect
                graphics::draw_in_quad(options_quad, Int2(3, 0), "INSPECT");
                
                num_options = 1;
                graphics::draw_in_quad(options_quad, Int2(1, 1), graphics::BULLET_POINT + "DO NOTHING");
                
                break;
            }
            case 2: {
                // talk
                graphics::draw_in_quad(options_quad, Int2(3, 0), "TALK");
                
                num_options = 1;
                graphics::draw_in_quad(options_quad, Int2(1, 1), graphics::BULLET_POINT + "DO NOTHING");
                
                break;
            }
            case 3: {
                // inventory
                graphics::draw_in_quad(options_quad, Int2(3, 0), "INVENTORY");
                
                num_options = 1;
                graphics::draw_in_quad(options_quad, Int2(1, 1), graphics::BULLET_POINT + "DO NOTHING");
                
                break;
            }
        }

        selection_arrow_pos = 0;
        graphics::draw_in_quad(options_quad, Int2(1, 1 + option_arrow_pos), '>');
    }
    
    // performs the option currently highlighted by the selection arrow
    void select_option() {

    }

    bool ignore_enter = false; 
    bool ignore_escape = false;
    //^ for some reason, the key presses are being remembered over several frames
    // this is a hacky work-around to ignore them on subsequent frames.

    // handles menu navigation
    void handle_menus() {
        switch (active_menu) {
            case Actions: {
                handle_action_selection_arrow();

                if (input::enter_pressed() && !ignore_enter) {
                    select_action();

                    ignore_escape = true;
                }
                ignore_enter = false;
                return;
            }
            case Options: {
                handle_option_selection_arrow();
                
                select_option();

                if (input::escape_pressed() && !ignore_escape) {
                    active_menu = Actions;
                    graphics::draw_in_quad(options_quad, Int2(1, 1 + selection_arrow_pos), graphics::BULLET_POINT);
                    selection_arrow_pos = 0;
                    option_arrow_pos = 0;
                    graphics::draw_in_quad(actions_quad, Int2(1, 1 + selection_arrow_pos), '>');

                    select_option(); // does nothing for now

                    graphics::draw_empty_outlined_quad(options_quad); // clears the contents of the option menu

                    ignore_enter = true;
                }
                ignore_escape = false;
                return;
            }
        }
    }
}

