#pragma once

#include <tuple>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <string>
#include <limits>

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

const std::unordered_map<int, const std::string> BRICK_COLORS = {
    {static_cast<int>(BrickType::NONE), "#000000"},
    {static_cast<int>(BrickType::WHITE), "#FFFFFF"},
    {static_cast<int>(BrickType::ORANGE), "#FFA500"},
    {static_cast<int>(BrickType::CYAN), "#00FFFF"},
    {static_cast<int>(BrickType::GREEN), "#008000"},
    {static_cast<int>(BrickType::RED), "#FF0000"},
    {static_cast<int>(BrickType::BLUE), "#0000FF"},
    {static_cast<int>(BrickType::MAGENTA), "#FF00FF"},
    {static_cast<int>(BrickType::YELLOW), "#FFFF00"},
    {static_cast<int>(BrickType::SILVER), "#C0C0C0"},
    {static_cast<int>(BrickType::GOLD), "#FFD700"}
};

const std::unordered_map<int, int> BRICK_HP{
    {static_cast<int>(BrickType::NONE), NULL},
    {static_cast<int>(BrickType::WHITE), 1},
    {static_cast<int>(BrickType::ORANGE), 1},
    {static_cast<int>(BrickType::CYAN), 1},
    {static_cast<int>(BrickType::GREEN), 1},
    {static_cast<int>(BrickType::RED), 1},
    {static_cast<int>(BrickType::BLUE), 1},
    {static_cast<int>(BrickType::MAGENTA), 1},
    {static_cast<int>(BrickType::YELLOW), 1},
    {static_cast<int>(BrickType::SILVER), 2},
    {static_cast<int>(BrickType::GOLD), std::numeric_limits<int>::max()}
};

const std::unordered_map<int, int> BRICK_VALUE{
    {static_cast<int>(BrickType::WHITE), 50},
    {static_cast<int>(BrickType::ORANGE), 60},
    {static_cast<int>(BrickType::CYAN), 70},
    {static_cast<int>(BrickType::GREEN), 80},
    {static_cast<int>(BrickType::RED), 90},
    {static_cast<int>(BrickType::BLUE), 100},
    {static_cast<int>(BrickType::MAGENTA), 110},
    {static_cast<int>(BrickType::YELLOW), 120},
    {static_cast<int>(BrickType::SILVER), 200}
};

int GAME_FRAMERATE = 60;

float BOX_WALLS_THICKNESS = 10.0;

float BALL_RADIUS = 10.0;
float BALL_SPEED = 15.0;

float LASER_THICKNESS = 10.0;
float LASER_LENGTH = 1000.0;

float BONUS_SIZE = 25.0;
Position2D BONUS_DEFAULT_POS = Position2D(0, 0);
float BONUS_FALLING_SPEED = 10.0;
float BONUS_RESIZE_FACTOR = 1.5;