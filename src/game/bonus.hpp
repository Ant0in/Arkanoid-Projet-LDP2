#pragma once

#include "ball.hpp"
#include "../physics/solid_shapes.hpp"
#include "../common.hpp"
#include "game_box.hpp"
#include "../player/player.hpp"
#include <tuple>
#include <cmath>

class GameBox;
class Player;

class BonusInterface{
    private:
        Position2D pos;
        float size;
        int active_duration;
        float falling_speed;
        bool is_active;
        bool is_spawned;
        SolidRectangle hitbox;

    public:
        BonusInterface(const Position2D& pos, float size, int active_duration, float falling_speed, bool is_active = false, bool is_spawned = false): pos{pos}, size{size}, active_duration{active_duration}, falling_speed{falling_speed}, is_active{is_active}, is_spawned{is_spawned}, hitbox{SolidRectangle(pos, size, size)}{}
        ~BonusInterface() = default;

        SolidRectangle& getHitbox();
        const SolidRectangle& getHitbox() const;
        
        float getSize() const;
        void setSize(float s);

        Position2D getPosition() const;
        void setPosition(Position2D p);

        bool isSpawned() const;
        void setSpawned(bool flag);

        bool isActive() const;
        void setActive(bool flag);

        int getDuration() const;
        void setDuration(int d);

        float getFallingSpeed() const;
        void setFallingSpeed(float s);

        void incrementDuration(int incr);

        void spawnBonus(Position2D p);

        Position2D getGravityPosition() const;

        bool hasBonusDurationExpired() const;

        virtual void applyLogic(GameBox& gb, Player& player);
};

class DuplicationBonus: public BonusInterface{
    public:
        DuplicationBonus(const Position2D& pos = BONUS_DEFAULT_POS, float size = BONUS_SIZE, int active_duration = 1, float falling_speed = BONUS_FALLING_SPEED, bool is_active = false, bool is_spawned = false)
        : BonusInterface(pos, size, active_duration, falling_speed, is_active, is_spawned){}
        ~DuplicationBonus() = default;

        static std::tuple<float, float> rotate_velocity(float vx, float vy, float alpha);

        void applyLogic(GameBox& gb, Player& player);

        bool operator==(const BonusInterface& other);

};

class PlayerBonus: public BonusInterface{
    public:
        PlayerBonus(const Position2D& pos = BONUS_DEFAULT_POS, float size = BONUS_SIZE, int active_duration = 1, float falling_speed = BONUS_FALLING_SPEED, bool is_active = false, bool is_spawned = false)
        : BonusInterface(pos, size, active_duration, falling_speed, is_active, is_spawned){}
        ~PlayerBonus() = default;

        void applyLogic(GameBox& gb, Player& player);

        bool operator==(const BonusInterface& other);
};

class ResizeBonus: public BonusInterface{
    public:
        ResizeBonus(const Position2D& pos = BONUS_DEFAULT_POS, float size = BONUS_SIZE, int active_duration = 1, float falling_speed = BONUS_FALLING_SPEED, bool is_active = false, bool is_spawned = false)
        : BonusInterface(pos, size, active_duration, falling_speed, is_active, is_spawned){}
        ~ResizeBonus() = default;
    
        void applyLogic(GameBox& gb, Player& player);

        bool operator==(const BonusInterface& other);
};