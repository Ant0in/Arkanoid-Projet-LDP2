#pragma once

#include <tuple>
#include <iostream>
#include <limits>

class Position2D{
    private:
        float x, y;
    public:
        Position2D(float x, float y);

        float getX() const;
        float getY() const;

        std::tuple<float, float> coords();

        bool operator==(const Position2D& other);

        friend std::ostream& operator<<(std::ostream& os, Position2D& pos);
};


enum class BrickType{
    NONE = 0,
    WHITE = 1,
    ORANGE = 2,
    CYAN = 3,
    GREEN = 4,
    RED = 5,
    BLUE = 6,
    MAGENTA = 7,
    YELLOW = 8,
    SILVER = 9,
    GOLD = 10
};


enum class Action{
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
};