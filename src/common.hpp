#pragma once

#include <tuple>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <string>
#include <limits>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


class Position2D{

    private:

        float _x, _y;

    public:

        Position2D(float x, float y): _x{x}, _y{y} {}
        ~Position2D() = default;

        float getX() const;
        float getY() const;
        std::tuple<float, float> coords();
        bool operator==(const Position2D& other);
        friend std::ostream& operator<<(std::ostream& os, const Position2D& pos);
};


enum class BrickType{
    NONE = 0,
    WHITE = 1,
    ORANGE = 2,
    CYAN = 3,
    GREEN = 4,
    RED = 5,
    BLUE = 6,
    MAGENTA = 7,
    YELLOW = 8,
    SILVER = 9,
    GOLD = 10
};

enum class Action{
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
};

enum class WallType{
    NONE = 0,
    LEFT = 1,
    RIGHT = 2,
    BOTTOM = 3,
    TOP = 4
};

extern const std::unordered_map<int, Action> DEFAULT_CONFIG;
extern const std::unordered_map<int, ALLEGRO_COLOR> BRICK_COLORS;
extern const std::unordered_map<int, int> BRICK_HP;
extern const std::unordered_map<int, int> BRICK_VALUE;

extern const int GAME_FRAMERATE;
extern const int GAME_WIDTH;
extern const int GAME_HEIGHT;

extern const Position2D DEFAULT_CORNER_POS;
extern const Position2D DEFAULT_MOUSE_POS;
extern const int PLAYER_DEFAULT_HEALTH;

extern const float BALL_X_VELOCITY_DEFAULT;
extern const float BALL_Y_VELOCITY_DEFAULT;
extern const float BALL_RADIUS;
extern const float BALL_SPEED;
extern const Position2D DEFAULT_SPAWN_POSITION;

extern const float BOX_WALLS_THICKNESS;

extern const int BONUS_DEFAULT_DURATION;
extern const float BONUS_SIZE;
extern const float BONUS_FALLING_SPEED;
extern const float BONUS_RESIZE_FACTOR;

extern const float LASER_THICKNESS;
extern const float LASER_LENGTH;

extern const int WHITE_BRICK_HP;
extern const int ORANGE_BRICK_HP;
extern const int CYAN_BRICK_HP;
extern const int GREEN_BRICK_HP;
extern const int RED_BRICK_HP;
extern const int BLUE_BRICK_HP;
extern const int MAGENTA_BRICK_HP;
extern const int YELLOW_BRICK_HP;
extern const int SILVER_BRICK_HP;

