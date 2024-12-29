#include "bonus.hpp"

SolidRectangle& BonusInterface::getHitbox(){return hitbox;}
const SolidRectangle& BonusInterface::getHitbox() const{return hitbox;}

float BonusInterface::getSize() const{
    assert (getHitbox().getHeight() == getHitbox().getWidth()); 
    return getHitbox().getHeight();
}
void BonusInterface::setSize(float s){
    getHitbox().setHeight(s);
    getHitbox().setWidth(s);
}

Position2D BonusInterface::getPosition() const{return getHitbox().getPosition();}
void BonusInterface::setPosition(Position2D p){getHitbox().setPosition(p);}

bool BonusInterface::isSpawned() const{return is_spawned;}
void BonusInterface::setSpawned(bool flag){is_spawned = flag;}

bool BonusInterface::isActive() const{return is_active;}
void BonusInterface::setActive(bool flag){is_active = flag;}

int BonusInterface::getDuration() const{return active_duration;}
void BonusInterface::setDuration(int d){active_duration = d;}

float BonusInterface::getFallingSpeed() const{return falling_speed;}
void BonusInterface::setFallingSpeed(float s){falling_speed = s;}

void BonusInterface::incrementDuration(int incr){active_duration = getDuration() + incr;}

void BonusInterface::spawnBonus(Position2D p){
    setPosition(p);
    setSpawned(true);
}

Position2D BonusInterface::getGravityPosition() const{
    // using x(t) = x0 + velocity*t, for t=1 (bc calculated each frame)
    Position2D t1 = getPosition();
    float x = t1.getX();
    float y = t1.getY() + getFallingSpeed();
    return Position2D(x, y);
}

bool BonusInterface::hasBonusDurationExpired() const{return getDuration() <= 0;}

bool BonusInterface::operator==(BonusInterface* other) const {
    return (getPosition() == other->getPosition()) && (getHitbox() == other->getHitbox()) && (getSize() == other->getSize()) &&
        (getDuration() == other->getDuration()) && (getFallingSpeed() == other->getFallingSpeed());
}

void BonusInterface::applyLogic(GameBox& gb, Player& player){
    throw std::runtime_error("Not Implemented Error");
}


std::tuple<float, float> DuplicationBonus::rotate_velocity(float vx, float vy, float alpha){
    float alpha_rad = alpha * M_PI / 180.0f;
    float nvx = static_cast<float>(vx * cos(alpha_rad) - vy * sin(alpha_rad));
    float nvy = static_cast<float>(vx * sin(alpha_rad) + vy * cos(alpha_rad));
    return std::make_tuple(nvx, nvy);
}

void DuplicationBonus::applyLogic(GameBox& gb, Player& player){
    // If bonus is not active or has expired, we skip logic
    if (! isActive() || hasBonusDurationExpired()){return;}
    
    // If bonus is active and not expired, we will proceed to apply logic for a frame 
    // (usually making the bonus vanish) and then decrement TTL
    Ball* ref = gb.getBalls()[0];
    auto [vx, vy] = (*ref).getVelocity();

    Ball* b1 = new Ball((*ref).getCenterPosition(), (*ref).getRadius(), (*ref).getSpeed());
    Ball* b2 = new Ball((*ref).getCenterPosition(), (*ref).getRadius(), (*ref).getSpeed());

    auto [vx1, vy1] = rotate_velocity(vx, vy, 120);
    auto [vx2, vy2] = rotate_velocity(vx, vy, -120);
    (*b1).setVelocity(vx1, vy1);
    (*b2).setVelocity(vx2, vy2);

    gb.addBall(b1);
    gb.addBall(b2);

    // decrement TTL (for dupe, 1 logic cycle will be applied since it has TTL of 1)
    incrementDuration(-1);
}


void PlayerBonus::applyLogic(GameBox& gb, Player& player){
    // If bonus is not active or has expired, we skip logic
    if (! isActive() || hasBonusDurationExpired()){return;}

    player.incrementHp(1);

    // decrement TTL (for player bonus, 1 logic cycle will be applied since it has TTL of 1)
    incrementDuration(-1);
}


void ResizeBonus::applyLogic(GameBox& gb, Player& player){
    // If bonus is not active or has expired, we skip logic
    if (! isActive() || hasBonusDurationExpired()){return;}

    gb.resizeRacket(BONUS_RESIZE_FACTOR);

    // decrement TTL (for player bonus, 1 logic cycle will be applied since it has TTL of 1)
    incrementDuration(-1);
}
