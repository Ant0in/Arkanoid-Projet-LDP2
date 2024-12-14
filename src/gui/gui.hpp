#include "game/solid_shapes.hpp"
#include "game/game_box.hpp"
#include "game/common.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <unordered_map>
#include <string>

std::unordered_map<int, std::string> BRICK_COLORS;

void initialize_brick_colors();

class GameGUI{
    
};