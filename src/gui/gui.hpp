#pragma once

#include "../game/game_box.hpp"
#include "../physics/solid_shapes.hpp"
#include "../common.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <vector>
#include <string>
#include <chrono>

class GameGUI{

    private:

        ALLEGRO_DISPLAY* _display;
        GameBox* _gamebox;
        Player* _player;
        std::chrono::high_resolution_clock::time_point _last_update;

    public:

        GameGUI(ALLEGRO_DISPLAY* display, GameBox* gamebox, Player* player):
            _display{display},
            _gamebox{gamebox},
            _player{player},
            _last_update{std::chrono::high_resolution_clock::now()} {}
        
        ~GameGUI() = default;

        ALLEGRO_DISPLAY* getAllegroDisplay();
        GameBox* getGameBox();
        Player* getPlayer();
        std::chrono::high_resolution_clock::time_point getLastUpdate();
        void drawRectangle(const SolidRectangle& rect, ALLEGRO_COLOR color);
        void drawCircle(const SolidCircle& circle, ALLEGRO_COLOR color);
        void updateFPS();
        void updateGUI();
};
