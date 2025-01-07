#pragma once

#include "windows.h"

#include "Int2.h"
#include "graphics.h"

namespace input {

	// returns true if a key has been pressed, after waiting for its release.
	bool key_state(int virtual_key_code) {
		bool pressed = false;

		// this waits until the key is no longer being pressed before continuing
		// I have lost the source for this.
		while (GetAsyncKeyState(virtual_key_code) < 0) {
			pressed = true;
		}
		
		return pressed;
	}

	// returns a vector representing the current WASD keys being pressed
	Int2 wasd() {
		Int2 dir(0, 0);

		// W
		if (key_state(0x57)) {
			dir += Int2::UP;
		}

		// A
		if (key_state(0x41)) {
			dir += Int2::LEFT;
		}

		// S
		if (key_state(0x53)) {
			dir += Int2::DOWN;
		}

		// D
		if (key_state(0x44)) {
			dir += Int2::RIGHT;
		}

		return dir;
	}

	// returns a vector representing the current arrow keys being pressed
	Int2 arrow_keys() {
		Int2 dir(0, 0);

		// UP
		if (key_state(0x26)) {
			dir += Int2::UP;
		}

		// LEFT
		if (key_state(0x25)) {
			dir += Int2::LEFT;
		}

		// DOWN
		if (key_state(0x28)) {
			dir += Int2::DOWN;
		}

		// RIGHT
		if (key_state(0x27)) {
			dir += Int2::RIGHT;
		}

		return dir;
	}

	// returns a resultant vector representing the whether up or down arrow keys are being pressed
	int up_down_arrow_keys() {
		int dir = 0;

		// UP
		if (key_state(0x26)) {
			dir -= 1;
		}

		// DOWN
		if (key_state(0x28)) {
			dir += 1;
		}

		return dir;
	}

	// wait for the enter key to be pressed before returning control to the call site
	void wait_for_enter() {
		while (true) {
			if (key_state(0x0D)) {
				graphics::clear_terminal();
				return;
			}
		}
	}

	// returns whether the enter key is currently being pressed
	bool enter_pressed() {
		return key_state(0x0D);
	}

	// returns whether the escape key is currently being pressed
	bool escape_pressed() {
		return key_state(0x1B);
	}
}