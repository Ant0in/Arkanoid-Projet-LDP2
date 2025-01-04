#include "bonus.hpp"

SolidRectangle& BonusInterface::getHitbox() {
    return _hitbox;
}
const SolidRectangle& BonusInterface::getHitbox() const {
    return _hitbox;
}

float BonusInterface::getSize() const {
    assert(getHitbox().getHeight() == getHitbox().getWidth());
    return getHitbox().getHeight();  // arbitrairement height
}
void BonusInterface::setSize(float s) {
    getHitbox().setHeight(s);
    getHitbox().setWidth(s);
}

Position2D BonusInterface::getPosition() const {
    return getHitbox().getPosition();
}
void BonusInterface::setPosition(const Position2D& p) {
    getHitbox().setPosition(p);
}

bool BonusInterface::isSpawned() const {
    return _is_spawned;
}
void BonusInterface::setSpawned(bool flag) {
    _is_spawned = flag;
}

bool BonusInterface::isActive() const {
    return _is_active;
}
void BonusInterface::setActive(bool flag) {
    _is_active = flag;
}

int BonusInterface::getDuration() const {
    return _active_duration;
}
void BonusInterface::setDuration(int d) {
    _active_duration = d;
}

float BonusInterface::getFallingSpeed() const {
    return _falling_speed;
}
void BonusInterface::setFallingSpeed(float s) {
    _falling_speed = s;
}

void BonusInterface::incrementDuration(int incr) {
    _active_duration = getDuration() + incr;
}

BonusType BonusInterface::getBonusType() {
    return _bonus_type;
}

void BonusInterface::spawnBonus(const Position2D& p) {
    setPosition(p);
    setSpawned(true);
}

Position2D BonusInterface::getGravityPosition() {
    // using x(t) = x0 + velocity*t, for t=1 (bc calculated each frame)
    Position2D t1 = getPosition();
    float      x  = t1.getX();
    float      y  = t1.getY() + getFallingSpeed();
    return Position2D(x, y);
}

bool BonusInterface::hasBonusDurationExpired() const {
    return getDuration() <= 0;
}

bool BonusInterface::operator==(BonusInterface* other) const {
    return (getPosition() == other->getPosition()) && (getHitbox() == other->getHitbox()) &&
           (getSize() == other->getSize()) && (getDuration() == other->getDuration()) &&
           (getFallingSpeed() == other->getFallingSpeed());
}

void BonusInterface::applyLogic(GameBox& gb, Player& player) {
    // abstract method, needs to be implement for all children bonuses
    (void) gb;
    (void) player;
    throw std::runtime_error("Not Implemented Error");
}

void BonusInterface::revertLogic(GameBox& gb, Player& player) {
    // pass, might be useful to implement for certain bonus, not for others
    (void) gb;
    (void) player;
}

std::tuple<float, float> DuplicationBonus::rotate_velocity(float vx, float vy, float alpha) {
    float alpha_rad = alpha * static_cast<float>(M_PI) / 180.0f;
    float nvx       = vx * cosf(alpha_rad) - vy * sinf(alpha_rad);
    float nvy       = vx * sinf(alpha_rad) + vy * cosf(alpha_rad);
    return std::make_tuple(nvx, nvy);
}

void DuplicationBonus::applyLogic(GameBox& gb, Player& player) {
    // If bonus is not active or has expired, we skip logic
    if (!isActive() || hasBonusDurationExpired()) {
        return;
    }

    (void) player;

    // If bonus is active and not expired, we will proceed to apply logic for a frame
    // (usually making the bonus vanish) and then decrement TTL
    Ball* ref     = gb.getBalls()[0];
    auto [vx, vy] = ref->getVelocity();

    Ball* b1 = new Ball(ref->getCenterPosition(), ref->getRadius(), ref->getSpeed());
    Ball* b2 = new Ball(ref->getCenterPosition(), ref->getRadius(), ref->getSpeed());

    auto [vx1, vy1] = rotate_velocity(vx, vy, 120);
    auto [vx2, vy2] = rotate_velocity(vx, vy, -120);
    b1->setVelocity(vx1, vy1);
    b2->setVelocity(vx2, vy2);

    gb.addBall(b1);
    gb.addBall(b2);

    // decrement TTL (for dupe, 1 logic cycle will be applied since it has TTL of 1)
    incrementDuration(-1);
}

void PlayerBonus::applyLogic(GameBox& gb, Player& player) {
    // If bonus is not active or has expired, we skip logic
    if (!isActive() || hasBonusDurationExpired()) {
        return;
    }

    (void) gb;

    player.incrementHp(1);

    // decrement TTL (for player bonus, 1 logic cycle will be applied since it has TTL of 1)
    incrementDuration(-1);
}

void ResizeBonus::applyLogic(GameBox& gb, Player& player) {
    // If bonus is not active or has expired, we skip logic
    if (!isActive() || hasBonusDurationExpired()) {
        return;
    }

    (void) player;

    gb.resizeRacket(BONUS_RESIZE_FACTOR);

    // we decrement TTL (for player bonus, 1 logic cycle will be applied since it has TTL of 1)
    incrementDuration(-1);
}

void ResizeBonus::revertLogic(GameBox& gb, Player& player) {
    (void) player;
    gb.resizeRacket(1 / BONUS_RESIZE_FACTOR);
}

int GrabBonus::getGrabTimer() {
    return _grabTimer;
}

void GrabBonus::setGrabTimer(int t) {
    _grabTimer = t;
}

void GrabBonus::incrementGrabTimer(int incr) {
    setGrabTimer(getGrabTimer() + incr);
}

void GrabBonus::applyLogic(GameBox& gb, Player& player) {
    // If bonus is not active or has expired, we skip logic
    if (!isActive() || hasBonusDurationExpired()) {
        return;
    }

    if (gb.isBallVectorEmpty() && !player.hasBallStored()) {
        return;
    }

    if (gb.doesPlayerHaveMultipleBalls()) {
        std::cerr << "Not supposed to apply grab logic with multiple balls" << std::endl;
        return;
    }

    // if grab timer is 0, then we check if ball must be grabbed
    if (getGrabTimer() == 0) {
        Ball* currentBall = gb.getBalls().at(0);

        if (CollisionHelper::isColliding(currentBall->getHitbox(), gb.getRacket()->getHitbox())) {
            // ball must be grabbed by the racket
            gb.removeBall(currentBall);
            delete currentBall;
            player.setHasBallStored(true);  // put another ball back in the held bar
            incrementGrabTimer(1);
        }

    } else {
        // if grab timer != 0, it means that there's a ball that needs to be shot in the held
        // bar. if that happens, we need to ckeck if timer is up, and if it is then shoot the
        // ball with the player action Action::SHOOT
        if (getGrabTimer() > GRAB_BONUS_MAX_GRAB_DURATION) {
            setGrabTimer(0);
            player.setHasGrabTimerExpired(true);
        } else {
            // If not, we increment the timer IF the ball has not been shooted. if it has been
            // shooted, then we will just reset the timer
            if (!player.hasBallStored()) {
                setGrabTimer(0);
            } else {
                incrementGrabTimer(1);
            }
        }
    }
}

void SlowBonus::applyLogic(GameBox& gb, Player& player){
    if (gb.isBallVectorEmpty()) {
        return;
    }
    
    Ball *currentBall = gb.getBalls().at(0);

    if (!isActive() || hasBonusDurationExpired()) {
        // if needed: restore speed
        if (currentBall->getSpeed() < BALL_SPEED) {
            float recoveryRate = 0.09f;
            float updatedSpeed = currentBall->getSpeed() + recoveryRate;

            if (updatedSpeed > BALL_SPEED) {
                updatedSpeed = BALL_SPEED;
            }

            currentBall->setSpeed(updatedSpeed);
        }
        return;
    }

    float newSpeed = currentBall->getSpeed() / SLOW_FACTOR;
    currentBall->setSpeed(newSpeed);

    incrementDuration(-1);
}

void SlowBonus::revertLogic(GameBox& gb, Player& player){
    Ball * currentBall = gb.getBalls().at(0);
    currentBall->setSpeed(BALL_SPEED);
}
