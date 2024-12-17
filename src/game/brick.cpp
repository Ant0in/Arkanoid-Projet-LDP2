#include "brick.hpp"

int Brick::attributeBrickHpByType(BrickType type){
    switch (type) {
        case BrickType::GOLD:
            return std::numeric_limits<int>::max();
        case BrickType::SILVER:
            return 2; 
        default:
            return 1; 
    }
}

Position2D Brick::getPosition() const {return position;}
void Brick::setPosition(const Position2D& pos) {position = pos;}

float Brick::getHeight() const {return height;}
float Brick::getWidth() const {return width;}

void Brick::setHeight(float h) {height = h;}
void Brick::setWidth(float w) {width = w;}

BrickType Brick::getBrickType() const {return btype;}

int Brick::getHP() const {return hp;}
void Brick::setHP(int v) {hp =v;}

SolidRectangle& Brick::getHitbox() {return hitbox;}
const SolidRectangle& Brick::getHitbox() const {return hitbox;}

void Brick::moveToCoordinates(const Position2D& coord){
    // Move brick with its hitbox
    setPosition(coord);
    getHitbox().setPosition(coord);
}

void Brick::makeBrickLoseHP(int loss){
    int new_hp = getHP() - loss;
    setHP(new_hp);
}

bool Brick::isBroken() const {
    return getHP() <= 0;
}

int Brick::getBrickValue(){
    switch (getBrickType()) {
        case BrickType::WHITE: return 50;
        case BrickType::ORANGE: return 60;
        case BrickType::CYAN: return 70;
        case BrickType::GREEN: return 80;
        case BrickType::RED: return 90;
        case BrickType::BLUE: return 100;
        case BrickType::MAGENTA: return 110;
        case BrickType::YELLOW: return 120;
        case BrickType::SILVER: return 200;
        default: 
            std::cerr << "Brick type not implemented" << std::endl;
            return 0;
    }
}

bool Brick::operator==(const Brick& other) const {
    return (getPosition().getX() == other.getPosition().getX()) && (getPosition().getY() == other.getPosition().getY());
}
