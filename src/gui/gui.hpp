#pragma once

#include "../game/game_box.hpp"
#include "../physics/solid_shapes.hpp"
#include "../common.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <chrono>

class GameGUI{
    private:
        ALLEGRO_DISPLAY* display;
        GameBox* gamebox;
        std::chrono::high_resolution_clock::time_point last_update;
    public:
        GameGUI(ALLEGRO_DISPLAY* display, GameBox* gamebox): display{display}, gamebox{gamebox}, last_update{std::chrono::high_resolution_clock::now()}{}
        ~GameGUI() = default;

        void drawRectangle(const SolidRectangle& rect, ALLEGRO_COLOR color);
        void drawCircle(const SolidCircle& circle, ALLEGRO_COLOR color);

        void updateFPS();

        void updateGUI();
};
