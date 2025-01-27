#pragma once

#include <cmath>
#include <tuple>

#include "ball.hpp"
#include "common.hpp"
#include "game_box.hpp"
#include "player.hpp"
#include "solid_shapes.hpp"


class GameBox;
class Player;

class BonusInterface {
   private:
    int            _active_duration;
    float          _falling_speed;
    bool           _is_active;
    bool           _is_spawned;
    SolidRectangle _hitbox;
    BonusType      _bonus_type;

   public:
    BonusInterface(const Position2D& pos,
                   float             size,
                   int               active_duration,
                   float             falling_speed,
                   bool              is_active  = false,
                   bool              is_spawned = false,
                   BonusType         bonus_type = BonusType::NONE)
        : _active_duration{active_duration},
          _falling_speed{falling_speed},
          _is_active{is_active},
          _is_spawned{is_spawned},
          _hitbox{SolidRectangle(pos, size, size)},
          _bonus_type{bonus_type} {
    }

    virtual ~BonusInterface() = default;

    SolidRectangle&         getHitbox();
    const SolidRectangle&   getHitbox() const;
    float                   getSize() const;
    void                    setSize(float s);
    Position2D              getPosition() const;
    void                    setPosition(const Position2D& p);
    bool                    isSpawned() const;
    void                    setSpawned(bool flag);
    bool                    isActive() const;
    void                    setActive(bool flag);
    int                     getDuration() const;
    void                    setDuration(int d);
    float                   getFallingSpeed() const;
    void                    setFallingSpeed(float s);
    void                    incrementDuration(int incr);
    BonusType               getBonusType();
    void                    spawnBonus(const Position2D& p);
    Position2D              getGravityPosition();
    bool                    hasBonusDurationExpired() const;
    bool                    operator==(BonusInterface* other) const;
    virtual void            applyLogic(GameBox& gb, Player& player);
    virtual void            revertLogic(GameBox& gb, Player& player);
    virtual BonusInterface* clone() const = 0;
};

class DuplicationBonus : public BonusInterface {
   public:
    DuplicationBonus(const Position2D& pos             = DEFAULT_CORNER_POS,
                     float             size            = BONUS_SIZE,
                     int               active_duration = BONUS_DEFAULT_DURATION,
                     float             falling_speed   = BONUS_FALLING_SPEED,
                     bool              is_active       = false,
                     bool              is_spawned      = false)
        : BonusInterface(pos,
                         size,
                         active_duration,
                         falling_speed,
                         is_active,
                         is_spawned,
                         BonusType::DUPLICATION) {
    }
    virtual ~DuplicationBonus() = default;

    static std::tuple<float, float> rotate_velocity(float vx, float vy, float alpha);
    BonusInterface*                 clone() const override {
        return new DuplicationBonus(*this);
    }

    void applyLogic(GameBox& gb, Player& player);
};

class PlayerBonus : public BonusInterface {
   public:
    PlayerBonus(const Position2D& pos             = DEFAULT_CORNER_POS,
                float             size            = BONUS_SIZE,
                int               active_duration = BONUS_DEFAULT_DURATION,
                float             falling_speed   = BONUS_FALLING_SPEED,
                bool              is_active       = false,
                bool              is_spawned      = false)
        : BonusInterface(
              pos, size, active_duration, falling_speed, is_active, is_spawned, BonusType::PLAYER) {
    }
    virtual ~PlayerBonus() = default;

    BonusInterface* clone() const override {
        return new PlayerBonus(*this);
    }
    void applyLogic(GameBox& gb, Player& player);
};

class ResizeBonus : public BonusInterface {
   public:
    ResizeBonus(const Position2D& pos             = DEFAULT_CORNER_POS,
                float             size            = BONUS_SIZE,
                int               active_duration = BONUS_DEFAULT_DURATION,
                float             falling_speed   = BONUS_FALLING_SPEED,
                bool              is_active       = false,
                bool              is_spawned      = false)
        : BonusInterface(
              pos, size, active_duration, falling_speed, is_active, is_spawned, BonusType::RESIZE) {
    }
    virtual ~ResizeBonus() = default;

    BonusInterface* clone() const override {
        return new ResizeBonus(*this);
    }
    void applyLogic(GameBox& gb, Player& player);
    void revertLogic(GameBox& gb, Player& player);
};

class GrabBonus : public BonusInterface {
   private:
    int _grabTimer;

   public:
    GrabBonus(const Position2D& pos             = DEFAULT_CORNER_POS,
              float             size            = BONUS_SIZE,
              int               active_duration = BONUS_DEFAULT_DURATION,
              float             falling_speed   = BONUS_FALLING_SPEED,
              bool              is_active       = false,
              bool              is_spawned      = false)
        : BonusInterface(
              pos, size, active_duration, falling_speed, is_active, is_spawned, BonusType::GRAB),
          _grabTimer(0) {
    }

    virtual ~GrabBonus() = default;

    BonusInterface* clone() const override {
        return new GrabBonus(*this);
    }

    int  getGrabTimer();
    void setGrabTimer(int t);
    void incrementGrabTimer(int incr);
    void applyLogic(GameBox& gb, Player& player);
    void revertLogic(GameBox& gb, Player& player);
};

class SlowBonus : public BonusInterface {
   public:
    SlowBonus(const Position2D& pos             = DEFAULT_CORNER_POS,
              float             size            = BONUS_SIZE,
              int               active_duration = BONUS_DEFAULT_DURATION,
              float             falling_speed   = BONUS_FALLING_SPEED,
              bool              is_active       = false,
              bool              is_spawned      = false)
        : BonusInterface(
              pos, size, active_duration, falling_speed, is_active, is_spawned, BonusType::SLOW) {
    }
    virtual ~SlowBonus() = default;

    BonusInterface* clone() const override {
        return new SlowBonus(*this);
    }
    void applyLogic(GameBox& gb, Player& player);
    void revertLogic(GameBox& gb, Player& player);
};

class LaserBonus : public BonusInterface {
   public:
    LaserBonus(const Position2D& pos             = DEFAULT_CORNER_POS,
               float             size            = BONUS_SIZE,
               int               active_duration = BONUS_DEFAULT_DURATION,
               float             falling_speed   = BONUS_FALLING_SPEED,
               bool              is_active       = false,
               bool              is_spawned      = false)
        : BonusInterface(
              pos, size, active_duration, falling_speed, is_active, is_spawned, BonusType::LASER) {
    }
    virtual ~LaserBonus() = default;

    BonusInterface* clone() const override {
        return new LaserBonus(*this);
    }

    void applyLogic(GameBox& gb, Player& player);
    void revertLogic(GameBox& gb, Player& player);
};