#include "game/common.hpp"

float Position2D::getX() const {return x;}
float Position2D::getY() const {return y;}

std::tuple<float, float> Position2D::coords() {return std::make_tuple(getX(), getY());}

bool Position2D::operator==(const Position2D& other){
    return (getX() == other.getX()) && (getY() == other.getY());
}

std::ostream& operator<<(std::ostream& os, Position2D& pos) {
    auto [x,y] = pos.coords();
    os << "{" << x << "," << y << "}";
    return os;
}


