#include "brick.hpp"


int Brick::getBrickHpByType(const BrickType& btype){
    auto it = BRICK_HP.find(static_cast<int>(btype));
    if (it != BRICK_HP.end()) {
        return it->second;
    } else {
        throw std::runtime_error("[E] Error for brick type: " + std::to_string(static_cast<int>(btype)));
    }
}

SolidRectangle& Brick::getHitbox() {return hitbox;}
const SolidRectangle& Brick::getHitbox() const {return hitbox;}

Position2D Brick::getPosition() const {return getHitbox().getPosition();}
void Brick::setPosition(const Position2D& pos) {getHitbox().setPosition(pos);}

float Brick::getHeight() const {return getHitbox().getHeight();}
float Brick::getWidth() const {return getHitbox().getWidth();}

void Brick::setHeight(float h) {getHitbox().setHeight(h);}
void Brick::setWidth(float w) {getHitbox().setWidth(w);}

BrickType Brick::getBrickType() const {return btype;}

int Brick::getHP() const {return hp;}
void Brick::setHP(int v) {hp =v;}

BonusInterface* Brick::getBonus() const{return bonus;}
void Brick::setBonus(BonusInterface* b) {bonus = b;}

bool Brick::doesBrickContainBonus() const{return (bonus);}

Position2D Brick::getCenterPosition() const{return getHitbox().getCenterPosition();}

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

bool Brick::operator==(Brick* other) const {
    return (getPosition() == other->getPosition()) && (getHeight() == other->getHeight()) && (getWidth() == other->getWidth()) 
    && (getBrickType() == other->getBrickType()) && (getBonus() == other->getBonus()) && (getHP() == other->getHP()) && (getHitbox() == other->getHitbox());
}
