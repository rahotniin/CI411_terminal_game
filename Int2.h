#pragma once

class Int2 {
    //^ represents a vector with 2 integer components
public:
    int x;
    int y;

    Int2(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Int2 operator + (Int2 other) {
        return Int2(x+other.x, y+other.y);
    }

    Int2 operator - (Int2 other) {
        return Int2(x-other.x, y-other.y);
    }

    Int2 operator / (int divisor) {
        return Int2(x / divisor, y / divisor);
    }

    bool operator != (Int2 other) {
        return x != other.x || y != other.y;
    }

    void operator += (Int2 other) {
        x += other.x;
        y += other.y;
    }

    //==============================//
    // constants,

    static Int2 UP;
    static Int2 DOWN;
    static Int2 LEFT;
    static Int2 RIGHT;
    static Int2 ZERO;
};

Int2 Int2::UP = Int2(0, -1);
Int2 Int2::DOWN = Int2(0, 1);
Int2 Int2::LEFT = Int2(-1, 0);
Int2 Int2::RIGHT = Int2(1, 0);
Int2 Int2::ZERO = Int2(0, 0);