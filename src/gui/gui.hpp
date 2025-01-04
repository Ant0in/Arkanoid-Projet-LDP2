#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include <chrono>
#include <string>
#include <vector>

#include "../common.hpp"
#include "../game/game_box.hpp"
#include "../physics/solid_shapes.hpp"
#include "./texture_manager.hpp"

class GameGUI {
   private:
    ALLEGRO_DISPLAY*                               _display;
    ALLEGRO_FONT*                                  _font;
    GameBox*                                       _gamebox;
    Player*                                        _player;
    std::chrono::high_resolution_clock::time_point _last_update;
    bool                                           _isInGameOverState;

   public:
    GameGUI(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, GameBox* gamebox, Player* player)
        : _display{display},
          _font{font},
          _gamebox{gamebox},
          _player{player},
          _last_update{std::chrono::high_resolution_clock::now()},
          _isInGameOverState{false} {
    }

    ~GameGUI() = default;

    ALLEGRO_DISPLAY*                               getAllegroDisplay();
    ALLEGRO_FONT*                                  getAllegroFont();
    GameBox*                                       getGameBox();
    Player*                                        getPlayer();
    std::chrono::high_resolution_clock::time_point getLastUpdate();
    void setLastUpdate(std::chrono::high_resolution_clock::time_point up);
    bool isInGameOverState();
    void setIsInGameOverState(bool flag);

    void drawRectangle(const SolidRectangle& rect, ALLEGRO_COLOR color);
    void drawRectangleWithTexture(const SolidRectangle& rect, const std::string& texturePath);
    void drawCircle(const SolidCircle& circle, ALLEGRO_COLOR color);
    void drawText(const Position2D& pos, std::string text);
    void updateFPS();
    void clearScreen();
    void handleGameoverState();

    void drawStatistics();
    void drawBoard();
    void drawBricks();
    void drawBalls();
    void drawRacket();
    void drawBonuses();
    void drawLasers();
    void drawGameOver();

    void updateGUI();
};
