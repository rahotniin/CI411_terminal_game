#pragma once

#include "int2.h"

// represents a qaudrilateral with integer vertex coordinates
class Quad {
public:
// vertex coordinate bounds
    int x_min;
    int y_min;
    int x_max;
    int y_max;

    //==========================//

private:
    Quad(int x_min, int y_min, int x_max, int y_max) {
        this->x_min = x_min;
        this->y_min = y_min;
        this->x_max = x_max;
        this->y_max = y_max;
    }

public:
    // returns a quad with (x, y) as its origin/top-left corner. With the specific width and height
    static Quad from_xywh(int x, int y, int width, int height) {
        return Quad(x, y, x + width - 1, y + height - 1);
    }

    // returns a quad with the specified bounds
    static Quad from_xyXY(int x_min, int y_min, int x_max, int y_max) {
        return Quad(x_min, y_min, x_max, y_max);
    }

    //==========================//

    // returns the width of the qaud
    int width() {
        return x_max - x_min + 1;
    }

    // return the height of a qaud
    int height() {
        return y_max - y_min + 1;
    }

    // sets the height of a quad. Returns the quad so it can be chained to the end of a constructor
    Quad with_height(int height) {
        this->y_max = this->y_min + height - 1;
        return *this; // not sure if this is safe
    }

    //==========================//

    // these are poorly named for neatness:

    /// @brief top left corner
    Int2 top_l() {
        return Int2(x_min, y_min);
    }

    /// @brief top right corner
    Int2 top_r() {
        return Int2(x_max, y_min);
    }

    /// @brief bottom left corner
    Int2 btm_l() {
        return Int2(x_min, y_max);
    }

    /// @brief bottom right corner
    Int2 btm_r() {
        return Int2(x_max, y_max);
    }

    // returns the point at the centre of the quad
    Int2 midpoint() {
        return top_l() + (btm_r() - top_l()) / 2;
    }

    //==========================//

    /// @brief Determines if  apoint is inside the qaud.
    /// Returns true even for points on the quad's edge.
    bool inclusive_contains(int x, int y) {
        return x >= x_min && x <= x_max && y >= y_min && y <= y_max;
    }
    /// @brief  Returns true even for points on the quad's edge.
    bool inclusive_contains(Int2 pos) {
        return inclusive_contains(pos.x, pos.y);
    }

    //==========================//

    /// @brief Determines if  apoint is inside the qaud.
    /// Returns false for points on the quad's edge.
    bool exclusive_contains(int x, int y) {
        return x > x_min && x < x_max && y > y_min && y < y_max;
    }
    
    /// @brief Determines if  apoint is inside the qaud.
    /// Returns false for points on the quad's edge.
    bool exclusive_contains(Int2 pos) {
        return exclusive_contains(pos.x, pos.y);
    }

    //==========================//
};