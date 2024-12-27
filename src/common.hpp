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
        float x, y;
    public:
        Position2D(float x, float y): x{x}, y{y}{}
        ~Position2D() = default;

        float getX() const;
        float getY() const;

        std::tuple<float, float> coords();

        bool operator==(const Position2D& other);

        friend std::ostream& operator<<(std::ostream& os, Position2D& pos);
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

extern const std::unordered_map<int, ALLEGRO_COLOR> BRICK_COLORS;
extern const std::unordered_map<int, int> BRICK_HP;
extern const std::unordered_map<int, int> BRICK_VALUE;

extern int GAME_FRAMERATE;
extern float BOX_WALLS_THICKNESS;
extern float BALL_RADIUS;
extern float BALL_SPEED;
extern float LASER_THICKNESS;
extern float LASER_LENGTH;
extern float BONUS_SIZE;
extern Position2D BONUS_DEFAULT_POS;
extern float BONUS_FALLING_SPEED;
extern float BONUS_RESIZE_FACTOR;