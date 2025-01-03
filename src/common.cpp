#include "common.hpp"

float Position2D::getX() const {return _x;}
float Position2D::getY() const {return _y;}

std::tuple<float, float> Position2D::coords() {return std::make_tuple(getX(), getY());}

bool Position2D::operator==(const Position2D& other){
    return (getX() == other.getX()) && (getY() == other.getY());
}

std::ostream& operator<<(std::ostream& os, const Position2D& pos) {
    float x = pos.getX();
    float y = pos.getY();
    os << "{" << x << "," << y << "}";
    return os;
}

const std::unordered_map<int, ALLEGRO_COLOR> BRICK_COLORS = {
    {static_cast<int>(BrickType::NONE), al_map_rgb(0x00, 0x00, 0x00)},
    {static_cast<int>(BrickType::WHITE), al_map_rgb(0xFF, 0xFF, 0xFF)},
    {static_cast<int>(BrickType::ORANGE), al_map_rgb(0xFF, 0xA5, 0x00)},
    {static_cast<int>(BrickType::CYAN), al_map_rgb(0x00, 0xFF, 0xFF)},
    {static_cast<int>(BrickType::GREEN), al_map_rgb(0x00, 0x80, 0x00)},
    {static_cast<int>(BrickType::RED), al_map_rgb(0xFF, 0x00, 0x00)},
    {static_cast<int>(BrickType::BLUE), al_map_rgb(0x00, 0x00, 0xFF)},
    {static_cast<int>(BrickType::MAGENTA), al_map_rgb(0xFF, 0x00, 0xFF)},
    {static_cast<int>(BrickType::YELLOW), al_map_rgb(0xFF, 0xFF, 0x00)},
    {static_cast<int>(BrickType::SILVER), al_map_rgb(0xC0, 0xC0, 0xC0)},
    {static_cast<int>(BrickType::GOLD), al_map_rgb(0xFF, 0xD7, 0x00)}
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

const std::unordered_map<int, Action> DEFAULT_CONFIG{
    {static_cast<int>(ALLEGRO_KEY_LEFT), Action::LEFT},
    {static_cast<int>(ALLEGRO_KEY_RIGHT), Action::RIGHT},
};



const int GAME_FRAMERATE = 60;

const float BOX_WALLS_THICKNESS = 10.0;
const Position2D DEFAULT_CORNER_POS = Position2D(0, 0);
const int PLAYER_DEFAULT_HEALTH = 3;

const float BALL_X_VELOCITY_DEFAULT = 0.0;
const float BALL_Y_VELOCITY_DEFAULT = 1.0;
const float BALL_RADIUS = 10.0;
const float BALL_SPEED = 15.0;
const Position2D DEFAULT_SPAWN_POSITION = Position2D(400, 350);

const int BONUS_DEFAULT_DURATION = 1;
const float BONUS_SIZE = 25.0;
const float BONUS_FALLING_SPEED = 10.0;
const float BONUS_RESIZE_FACTOR = 1.5;

const float LASER_THICKNESS = 10.0;
const float LASER_LENGTH = 1000.0;

const int WHITE_BRICK_HP = 50;
const int ORANGE_BRICK_HP = 60;
const int CYAN_BRICK_HP = 70;
const int GREEN_BRICK_HP = 80;
const int RED_BRICK_HP = 90;
const int BLUE_BRICK_HP = 100;
const int MAGENTA_BRICK_HP = 110;
const int YELLOW_BRICK_HP = 120;
const int SILVER_BRICK_HP = 200;

