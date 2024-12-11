#include <tuple>
#include <iostream>
#include <limits>

class Position2D{
    private:
        float x, y;
    public:
        Position2D(float x, float y);

        float getX();
        float getY();

        std::tuple<float, float> coords();

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


enum class BrickHp{
    NONE = 0,
    WHITE = 1,
    ORANGE = 1,
    CYAN = 1,
    GREEN = 1,
    RED = 1,
    BLUE = 1,
    MAGENTA = 1,
    YELLOW = 1,
    SILVER = 2,
    GOLD = std::numeric_limits<int>::infinity()
};


enum class Action{
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
};