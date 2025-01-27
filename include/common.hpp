#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <unordered_map>

class Position2D {
   private:
    float _x, _y;

   public:
    Position2D(float x, float y) : _x{x}, _y{y} {
    }
    ~Position2D() = default;

    float                    getX() const;
    float                    getY() const;
    std::tuple<float, float> coords();
    bool                     operator==(const Position2D& other);
    friend std::ostream&     operator<<(std::ostream& os, const Position2D& pos);
};

enum class BrickType {
    NONE    = 0,
    WHITE   = 1,
    ORANGE  = 2,
    CYAN    = 3,
    GREEN   = 4,
    RED     = 5,
    BLUE    = 6,
    MAGENTA = 7,
    YELLOW  = 8,
    SILVER  = 9,
    GOLD    = 10
};

enum class Action {
    NONE            = 0,
    LEFT            = 1,
    RIGHT           = 2,
    SHOOT           = 3,
    NEXT_LEVEL      = 4,
    PREVIOUS_LEVEL  = 5,
    RESET_HIGHSCORE = 6,
    REMAKE          = 7
};

enum class WallType { NONE = 0, LEFT = 1, RIGHT = 2, BOTTOM = 3, TOP = 4 };

enum class BonusType {
    NONE        = 0,
    DUPLICATION = 1,
    GRAB        = 2,
    LASER       = 3,
    PLAYER      = 4,
    RESIZE      = 5,
    SLOW        = 6
};

extern const std::string DAMAGED_SILVER_TEXTURE;

extern const std::string HIGH_SCORE_FILE;

extern const std::unordered_map<int, Action> DEFAULT_CONFIG;

extern const std::unordered_map<int, ALLEGRO_COLOR>     BRICK_COLORS;
extern const std::unordered_map<int, int>               BRICK_HP;
extern const std::unordered_map<int, int>               BRICK_VALUE;
extern const std::unordered_map<int, BrickType>         BRICK_ID;
extern const std::unordered_map<BrickType, std::string> BRICK_TEXTURE_PATH;
extern const std::unordered_map<BonusType, std::string> BONUS_TEXTURE_PATH;
extern const std::unordered_map<BonusType, char>        BONUS_IDENTIFIER;

extern const int         GAME_FRAMERATE;
extern const float       GAME_WIDTH;
extern const float       GAME_HEIGHT;
extern const std::string BACKGROUND_TEXTURE_PATH;
extern const std::string SIDE_WALLS_TEXTURE_PATH;
extern const std::string TOP_WALL_TEXTURE_PATH;
extern const std::string MAP_FOLDER_PATH;

extern const float UPPER_BORDER_HEIGHT;
extern const float LOWER_BORDER_HEIGHT;
extern const float LEFT_BORDER_WIDTH;
extern const float RIGHT_BORDER_WIDTH;

extern const ALLEGRO_COLOR DEFAULT_BACKGROUND_COLOR;
extern const ALLEGRO_COLOR DEFAULT_FONT_COLOR;

extern const Position2D DEFAULT_CORNER_POS;
extern const Position2D DEFAULT_MOUSE_POS;
extern const int        PLAYER_DEFAULT_HEALTH;

extern const float       RACKET_WIDTH;
extern const float       RACKET_HEIGHT;
extern const Position2D  RACKET_DEFAULT_POSITION;
extern const float       RACKET_DEFAULT_SENSIBILITY;
extern const std::string RACKET_TEXTURE_PATH;

extern const float         BALL_X_VELOCITY_DEFAULT;
extern const float         BALL_Y_VELOCITY_DEFAULT;
extern const float         BALL_RADIUS;
extern const float         BALL_SPEED;
extern const Position2D    DEFAULT_SPAWN_POSITION;
extern const ALLEGRO_COLOR DEFAULT_BALL_COLOR;
extern const float         SLOW_FACTOR;
extern const float         RECOVERY_RATE;

extern const float BRICK_WIDTH;
extern const float BRICK_HEIGHT;

extern const float BOX_WALLS_THICKNESS;

extern const int   BONUS_DEFAULT_DURATION;
extern const float BONUS_SIZE;
extern const float BONUS_FALLING_SPEED;
extern const float BONUS_RESIZE_FACTOR;
extern const int   GRAB_BONUS_MAX_GRAB_DURATION;

extern const float       LASER_WIDTH;
extern const float       LASER_HEIGHT;
extern const float       LASER_SPEED;
extern const std::string LASER_TEXTURE_PATH;

extern const int WHITE_BRICK_REWARD;
extern const int ORANGE_BRICK_REWARD;
extern const int CYAN_BRICK_REWARD;
extern const int GREEN_BRICK_REWARD;
extern const int RED_BRICK_REWARD;
extern const int BLUE_BRICK_REWARD;
extern const int MAGENTA_BRICK_REWARD;
extern const int YELLOW_BRICK_REWARD;
extern const int SILVER_BRICK_REWARD;
