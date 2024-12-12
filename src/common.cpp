#include "game/common.hpp"

class Position2D{
    private:
        float x, y;
    public:
        Position2D(float x, float y): x{x}, y{y}{}

        float getX() const {return x;}
        float getY() const {return y;}

        std::tuple<float, float> coords() {return std::make_tuple(getX(), getY());}

        bool operator==(const Position2D& other){
            return (getX() == other.getX()) && (getY() == other.getY());
        }

        friend std::ostream& operator<<(std::ostream& os, Position2D& pos);
};

std::ostream& operator<<(std::ostream& os, Position2D& pos) {
    auto [x,y] = pos.coords();
    os << "{" << x << "," << y << "}";
    return os;
}


