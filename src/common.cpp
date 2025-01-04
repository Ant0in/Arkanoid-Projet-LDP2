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

const std::unordered_map<int, Action> DEFAULT_CONFIG{
    {static_cast<int>(ALLEGRO_KEY_A), Action::LEFT},
    {static_cast<int>(ALLEGRO_KEY_D), Action::RIGHT},
    {static_cast<int>(ALLEGRO_KEY_Q), Action::LEFT},
    {static_cast<int>(ALLEGRO_KEY_P), Action::RIGHT}
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

const std::unordered_map<int, BrickType> BRICK_ID {
    {1, BrickType::WHITE},
    {2, BrickType::ORANGE},
    {3, BrickType::CYAN},
    {4, BrickType::GREEN},
    {5, BrickType::RED},
    {6, BrickType::BLUE},
    {7, BrickType::MAGENTA},
    {8, BrickType::YELLOW},
    {9, BrickType::SILVER},
    {0, BrickType::GOLD}
};

const std::unordered_map<BrickType, std::string> BRICK_TEXTURE_PATH = {
    {BrickType::WHITE, "./assets/bricks/white.png"},
    {BrickType::ORANGE, "./assets/bricks/orange.png"},
    {BrickType::CYAN, "./assets/bricks/cyan.png"},
    {BrickType::GREEN, "./assets/bricks/green.png"},
    {BrickType::RED, "./assets/bricks/red.png"},
    {BrickType::BLUE, "./assets/bricks/blue.png"},
    {BrickType::MAGENTA, "./assets/bricks/magenta.png"},
    {BrickType::YELLOW, "./assets/bricks/yellow.png"},
    {BrickType::SILVER, "./assets/bricks/silver.png"},
    {BrickType::GOLD, "./assets/bricks/gold.png"}
};

extern const std::string HIGH_SCORE_FILE = "./highscore.txt";

const int GAME_FRAMERATE = 60;
const float GAME_WIDTH = 800;
const float GAME_HEIGHT = 800;
const std::string BACKGROUND_TEXTURE_PATH = "./assets/background/bg.png";
const std::string SIDE_WALLS_TEXTURE_PATH = "./assets/background/side_wall.png";
const std::string TOP_WALL_TEXTURE_PATH = "./assets/background/top_wall.png";

const ALLEGRO_COLOR DEFAULT_BACKGROUND_COLOR = al_map_rgb(0x00, 0x00, 0x00);
const ALLEGRO_COLOR DEFAULT_FONT_COLOR = al_map_rgb(0xff, 0xff, 0xff);

const float BOX_WALLS_THICKNESS = 45.0;
const Position2D DEFAULT_CORNER_POS = Position2D(0, 0);
const Position2D DEFAULT_MOUSE_POS = Position2D(GAME_WIDTH / 2, GAME_HEIGHT / 2);
const int PLAYER_DEFAULT_HEALTH = 3;

const float RACKET_WIDTH = 200;
const float RACKET_HEIGHT = 20;
const Position2D RACKET_DEFAULT_POSITION = Position2D((GAME_WIDTH - RACKET_WIDTH) / 2, (GAME_HEIGHT / 8) * 7);
const float RACKET_DEFAULT_SENSIBILITY = 10;
const std::string RACKET_TEXTURE_PATH = "./assets/racket.png";

const float BALL_X_VELOCITY_DEFAULT = 0.0;
const float BALL_Y_VELOCITY_DEFAULT = 1.0;
const float BALL_RADIUS = 10.0;
const float BALL_SPEED = 15.0;
const Position2D DEFAULT_SPAWN_POSITION = Position2D(GAME_WIDTH / 2, GAME_HEIGHT / 2);
const ALLEGRO_COLOR DEFAULT_BALL_COLOR = al_map_rgb(0xFF, 0x00, 0x00);

const float BRICK_WIDTH = 50.0;
const float BRICK_HEIGHT = 20.0;

const int BONUS_DEFAULT_DURATION = 1;
const float BONUS_SIZE = 32.0;
const float BONUS_FALLING_SPEED = 10.0;
const float BONUS_RESIZE_FACTOR = 1.5;

const std::string DUPLICATION_BONUS_TEXTURE = "./assets/bonus/duplication_bonus.png";
const std::string GRAB_BONUS_TEXTURE = "./assets/bonus/grab_bonus.png";
const std::string LASER_BONUS_TEXTURE = "./assets/bonus/laser_bonus.png";
const std::string PLAYER_BONUS_TEXTURE = "./assets/bonus/player_bonus.png";
const std::string RESIZE_BONUS_TEXTURE = "./assets/bonus/resize_bonus.png";
const std::string SLOW_BONUS_TEXTURE = "./assets/bonus/slow_bonus.png";


const float LASER_THICKNESS = 10.0;
const float LASER_LENGTH = 1000.0;

const int WHITE_BRICK_REWARD = 50;
const int ORANGE_BRICK_REWARD = 60;
const int CYAN_BRICK_REWARD = 70;
const int GREEN_BRICK_REWARD = 80;
const int RED_BRICK_REWARD = 90;
const int BLUE_BRICK_REWARD = 100;
const int MAGENTA_BRICK_REWARD = 110;
const int YELLOW_BRICK_REWARD = 120;
const int SILVER_BRICK_REWARD = 200;

