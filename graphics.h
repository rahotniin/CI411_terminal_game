#pragma once

#include "windows.h"
#include <string>

#include "int2.h"
#include "GameObject.h"
#include "Quad.h"

namespace graphics {
	// the width and height of the terminal window (in characters) assumed by the game
	const int WIDTH = 120;
	const int HEIGHT = 30;

	//=============================================//
	// constants

	const static char EMPTY = ' ';

	const static char TL_CORNER_CHAR = (char)218; // top left
	const static char TR_CORNER_CHAR = (char)191; // top right
	const static char BL_CORNER_CHAR = (char)192; // bottom left
	const static char BR_CORNER_CHAR = (char)217; // bottom right

	const static char TB_SIDE_CHAR = (char)196; // top and bottom
	const static char LR_SIDE_CHAR = (char)179; // left and right

	const std::string BULLET_POINT{(char)250};
	//=============================================//

	void set_terminal_size() {
		// source: https://stackoverflow.com/questions/42169105/programmatically-expand-terminal-to-a-specific-size
		std::cout << "\e[8;" << HEIGHT << ";" << WIDTH << "t";
	}

	//=============================================//
	
	void set_cursor_visibility(bool showFlag) {
		// source: https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt

		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO     cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
	}

	void hide_cursor() {
		set_cursor_visibility(false);
	}

	//=============================================//

	void set_cursor_pos(int x, int y) {
		// source: https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
		
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout.flush();
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hOut, coord);

		// tried to do the same with ansi escape codes, 
		// but it doesn't seem to work
		//std::cout << "\033[" << y << ";" << x << "H";
		//std::cout.flush();
	}

	//=============================================//

	/// @brief Draws the specified string at the position, in the colour.
	/// For a list of colours see the section on 256 colours:
	/// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
	void draw(int x, int y, std::string str, int colour = 255) {
		set_cursor_pos(x, y);
		std::cout << "\033[38;5;" << colour << "m";
		std::cout << str;
		std::cout << "\033[38;5;255m";
		std::cout.flush();
	}
	
	/// @brief Draws the specified string at the position, in the colour.
	/// For a list of colours see the section on 256 colours:
	/// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
	void draw(Int2 pos, std::string str, int colour = 255) {
		draw(pos.x, pos.y, str, colour);
	}

	/// @brief Draws the specified string at the position, in the colour.
	/// For a list of colours see the section on 256 colours:
	/// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
	void draw(int x, int y, char c, int colour = 255) {
		draw(x, y, std::string{c}, colour);
	}

	/// @brief Draws the specified string at the position, in the colour.
	/// For a list of colours see the section on 256 colours:
	/// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
	void draw(Int2 pos, char c, int colour = 255) {
		draw(pos.x, pos.y, std::string{c}, colour);
	}

	//=============================================//

	// clears the contents of the terminal by filling it with the space char
	void clear_terminal() {
		set_cursor_pos(0, 0);
		for (int x = 0; x < WIDTH; x++) {
			for (int y = 0; y < HEIGHT; y++) {
				draw(x, y, " ");
			}
		}
	}

	//=============================================//

	// draws a gameobject onto the terminal
	void draw_gameobject(GameObject obj) {
		draw(obj.pos, obj.symbol, obj.colour);
	}

	//=============================================//

	// draws the outline of a quad with lines directly between its vertices.
	void draw_quad_outline(Quad quad) {
		graphics::draw(quad.top_l(), TL_CORNER_CHAR); // top left corner
		graphics::draw(quad.top_r(), TR_CORNER_CHAR); // top right corner
		graphics::draw(quad.btm_l(), BL_CORNER_CHAR); // bottom left corner
		graphics::draw(quad.btm_r(), BR_CORNER_CHAR); // bottom right corner
		
		// top side
		for (int x = quad.x_min + 1, y = quad.y_min; x < quad.x_max; x++) {
			graphics::draw(x, y, TB_SIDE_CHAR);
		}

		// bottom side
		for (int x = quad.x_min + 1, y = quad.y_max; x < quad.x_max; x++) {
			graphics::draw(x, y, TB_SIDE_CHAR);
		}

		// left side
		for (int y = quad.y_min + 1, x = quad.x_min; y < quad.y_max; y++) {
			graphics::draw(x, y, LR_SIDE_CHAR);
		}

		// right side
		for (int y = quad.y_min + 1, x = quad.x_max; y < quad.y_max; y++) {
			graphics::draw(x, y, LR_SIDE_CHAR);
		}
	}

	// draws the outline of a quad with lines directly between its vertices. Also clears the contents of the quad
	void draw_empty_outlined_quad(Quad quad) {
		draw_quad_outline(quad);

		for (int x = 1; x < quad.width() - 1; x++) {
			for (int y = 1; y < quad.height() - 1; y++) {
				Int2 pos = quad.top_l() + Int2(x, y);
				draw(pos, ' ');
			}
		}
	}

	// prints a string at the given position, relative the qauds top-left corner/origin
	void draw_in_quad(Quad quad, Int2 local_pos, std::string text) {
		draw(quad.top_l() + local_pos, text);
	}

	// prints a string at the given position, relative the qauds top-left corner/origin
	void draw_in_quad(Quad quad, Int2 local_pos, char c) {
		draw(quad.top_l() + local_pos, c);
	}

	//=============================================//
};

