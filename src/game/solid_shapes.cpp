#include "solid_shapes.hpp"


Position2D SolidRectangle::getPosition() const {return position;}
void SolidRectangle::setPosition(const Position2D& pos) {position = pos;}

float SolidRectangle::getHeight() const {return height;}
float SolidRectangle::getWidth() const {return width;}

void SolidRectangle::setHeight(float h) {height = h;}
void SolidRectangle::setWidth(float w) {width = w;}

std::vector<Position2D> SolidRectangle::getCorners() const {
    Position2D top_left = getPosition();
    Position2D top_right = Position2D(top_left.getX() + getWidth(), top_left.getY());
    Position2D bottom_left = Position2D(top_left.getX(), top_left.getY() - getHeight());
    Position2D bottom_right = Position2D(top_left.getX() + getWidth(), top_left.getY() - getHeight());
    return {top_left, top_right, bottom_left, bottom_right};
}

bool SolidRectangle::isPointInSolid(const Position2D& point) const{
    Position2D top_left = getPosition();
    return (
        top_left.getX() <= point.getX() && point.getX() <= (top_left.getX() + getWidth()) &&
        top_left.getY() <= point.getY() && point.getY() <= (top_left.getY() + getHeight())
    );
}

bool SolidRectangle::operator==(const SolidInterface& other) const {
    const SolidRectangle* rect = dynamic_cast<const SolidRectangle*>(&other);
    if (!rect) return false;
    return (getPosition() == rect->getPosition()) && 
        (getWidth() == rect->getWidth()) && 
        (getHeight() == rect->getHeight());
}


Position2D SolidCircle::getPosition() const {return position;}
void SolidCircle::setPosition(const Position2D& pos) {position = pos;}

float SolidCircle::getRadius() const {return radius;};
void SolidCircle::setRadius(float rad) {radius = rad;}

bool SolidCircle::isPointInSolid(const Position2D& point) const {
    Position2D center = getPosition();
    float distance_squared = pow((point.getX() - center.getX()), 2) + pow((point.getY() - center.getY()), 2);
    return distance_squared <= pow(getRadius(), 2);
}

bool SolidCircle::operator==(const SolidInterface& other) const {
    const SolidCircle* circle = dynamic_cast<const SolidCircle*>(&other);
    if (!circle) return false;
    return (getPosition() == circle->getPosition()) && (getRadius() == circle->getRadius());
}
