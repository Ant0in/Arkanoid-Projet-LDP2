#include "../../include/brick.hpp"

int Brick::getBrickHpByType(const BrickType& btype) {
    auto it = BRICK_HP.find(static_cast<int>(btype));
    if (it != BRICK_HP.end()) {
        return it->second;
    } else {
        throw std::runtime_error("[E] Error for brick type: " +
                                 std::to_string(static_cast<int>(btype)));
    }
}

Brick::~Brick() {
    if (_bonus) {
        delete _bonus;
    }
};

SolidRectangle& Brick::getHitbox() {
    return _hitbox;
}
const SolidRectangle& Brick::getHitbox() const {
    return _hitbox;
}

Position2D Brick::getPosition() const {
    return getHitbox().getPosition();
}
void Brick::setPosition(const Position2D& pos) {
    getHitbox().setPosition(pos);
}

float Brick::getHeight() const {
    return getHitbox().getHeight();
}
float Brick::getWidth() const {
    return getHitbox().getWidth();
}

void Brick::setHeight(float h) {
    getHitbox().setHeight(h);
}
void Brick::setWidth(float w) {
    getHitbox().setWidth(w);
}

BrickType Brick::getBrickType() const {
    return _btype;
}

int Brick::getHP() const {
    return _hp;
}
void Brick::setHP(int v) {
    _hp = v;
}

BonusInterface* Brick::getBonus() const {
    return _bonus;
}
void Brick::setBonus(BonusInterface* b) {
    if (_bonus) {
        delete _bonus;
    }
    _bonus = b;
}

bool Brick::doesBrickContainBonus() const {
    return (_bonus);
}

Position2D Brick::getCenterPosition() const {
    return getHitbox().getCenterPosition();
}

void Brick::makeBrickLoseHP(int loss) {
    int new_hp = getHP() - loss;
    setHP(new_hp);
}

bool Brick::isBroken() const {
    return getHP() <= 0;
}

int Brick::getBrickValue() {
    switch (getBrickType()) {
        case BrickType::WHITE:
            return WHITE_BRICK_REWARD;
        case BrickType::ORANGE:
            return ORANGE_BRICK_REWARD;
        case BrickType::CYAN:
            return CYAN_BRICK_REWARD;
        case BrickType::GREEN:
            return GREEN_BRICK_REWARD;
        case BrickType::RED:
            return RED_BRICK_REWARD;
        case BrickType::BLUE:
            return BLUE_BRICK_REWARD;
        case BrickType::MAGENTA:
            return MAGENTA_BRICK_REWARD;
        case BrickType::YELLOW:
            return YELLOW_BRICK_REWARD;
        case BrickType::SILVER:
            return SILVER_BRICK_REWARD;
        default:
            std::cerr << "Brick type not implemented" << std::endl;
            return 0;
    }
}

bool Brick::operator==(Brick* other) const {
    // written to help with removing brick from a vector
    return (getPosition() == other->getPosition()) && (getHeight() == other->getHeight()) &&
           (getWidth() == other->getWidth()) && (getBrickType() == other->getBrickType()) &&
           (getBonus() == other->getBonus()) && (getHP() == other->getHP()) &&
           (getHitbox() == other->getHitbox());
}
