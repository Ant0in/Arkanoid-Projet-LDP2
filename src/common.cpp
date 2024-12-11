#include "game/common.hpp"

class Position2D{
    private:
        float x, y;
    public:
        Position2D(float x, float y): x{x}, y{y}{}

        float getX() {return x;}
        float getY() {return y;}

        std::tuple<float, float> coords() {return std::make_tuple(getX(), getY());}

        friend std::ostream& operator<<(std::ostream& os, Position2D& pos);
};

std::ostream& operator<<(std::ostream& os, Position2D& pos) {
        auto [x,y] = pos.coords();
        os << "{" << x << "," << y << "}";
        return os;
    }


