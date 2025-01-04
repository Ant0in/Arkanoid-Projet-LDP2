#include "solid_shapes.hpp"

Position2D SolidRectangle::getPosition() const {
    return _position;
}
void SolidRectangle::setPosition(const Position2D& pos) {
    _position = pos;
}

float SolidRectangle::getHeight() const {
    return _height;
}
float SolidRectangle::getWidth() const {
    return _width;
}

void SolidRectangle::setHeight(float h) {
    _height = h;
}
void SolidRectangle::setWidth(float w) {
    _width = w;
}

std::vector<Position2D> SolidRectangle::getCorners() const {
    Position2D top_left    = getPosition();
    Position2D top_right   = Position2D(top_left.getX() + getWidth(), top_left.getY());
    Position2D bottom_left = Position2D(top_left.getX(), top_left.getY() - getHeight());
    Position2D bottom_right =
        Position2D(top_left.getX() + getWidth(), top_left.getY() - getHeight());
    return {top_left, top_right, bottom_left, bottom_right};
}

bool SolidRectangle::isPointInSolid(const Position2D& point) const {
    Position2D top_left = getPosition();
    return (top_left.getX() <= point.getX() && point.getX() <= (top_left.getX() + getWidth()) &&
            top_left.getY() <= point.getY() && point.getY() <= (top_left.getY() + getHeight()));
}

Position2D SolidRectangle::getCenterPosition() const {
    float cx = getPosition().getX() + (getWidth() / 2);
    float cy = getPosition().getY() + (getHeight() / 2);
    return Position2D(cx, cy);
}

bool SolidRectangle::operator==(const SolidRectangle& other) const {
    return (getPosition() == other.getPosition()) && (getWidth() == other.getWidth()) &&
           (getHeight() == other.getHeight());
}

Position2D SolidCircle::getPosition() const {
    return _position;
}
void SolidCircle::setPosition(const Position2D& pos) {
    _position = pos;
}

float SolidCircle::getRadius() const {
    return _radius;
};
void SolidCircle::setRadius(float rad) {
    _radius = rad;
}

bool SolidCircle::isPointInSolid(const Position2D& point) const {
    Position2D center           = getPosition();
    float      dx               = point.getX() - center.getX();
    float      dy               = point.getY() - center.getY();
    float      distance_squared = dx * dx + dy * dy;
    float      radius_squared   = getRadius() * getRadius();
    return distance_squared <= radius_squared;
}

bool SolidCircle::operator==(const SolidCircle& other) const {
    return (getPosition() == other.getPosition()) && (getRadius() == other.getRadius());
}
