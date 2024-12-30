#include "laser.hpp"

SolidRectangle& Laser::getHitbox(){return hitbox;}
const SolidRectangle& Laser::getHitbox() const{return hitbox;}

Position2D Laser::getPosition() const{return getHitbox().getPosition();}
void Laser::setPosition(const Position2D& p){getHitbox().setPosition(p);}

void Laser::spawnLaser(const Racket& r){
    Position2D r_center = r.getCenterPosition();
    Position2D offset_center = Position2D(r_center.getX() - LASER_THICKNESS / 2, r.getPosition().getY());
    setPosition(offset_center);
}