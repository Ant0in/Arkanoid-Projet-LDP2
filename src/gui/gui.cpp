#include "gui.hpp"

void initialize_brick_colors(){
    BRICK_COLORS[static_cast<int>(BrickType::NONE)] = "#000000";
    BRICK_COLORS[static_cast<int>(BrickType::WHITE)] = "#FFFFFF";
    BRICK_COLORS[static_cast<int>(BrickType::ORANGE)] = "#FFA500";
    BRICK_COLORS[static_cast<int>(BrickType::CYAN)] = "#00FFFF";
    BRICK_COLORS[static_cast<int>(BrickType::GREEN)] = "#008000";
    BRICK_COLORS[static_cast<int>(BrickType::RED)] = "#FF0000";
    BRICK_COLORS[static_cast<int>(BrickType::BLUE)] = "#0000FF";
    BRICK_COLORS[static_cast<int>(BrickType::MAGENTA)] = "#FF00FF";
    BRICK_COLORS[static_cast<int>(BrickType::YELLOW)] = "#FFFF00";
    BRICK_COLORS[static_cast<int>(BrickType::SILVER)] = "#C0C0C0";
    BRICK_COLORS[static_cast<int>(BrickType::GOLD)] = "#FFD700";
}