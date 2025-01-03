#include "gui.hpp"


ALLEGRO_DISPLAY* GameGUI::getAllegroDisplay() {return _display;}
ALLEGRO_FONT* GameGUI::getAllegroFont() {return _font;}

GameBox* GameGUI::getGameBox() {return _gamebox;}

Player* GameGUI::getPlayer() {return _player;}

std::chrono::high_resolution_clock::time_point GameGUI::getLastUpdate() {return _last_update;}

void GameGUI::setLastUpdate(std::chrono::high_resolution_clock::time_point up) {_last_update = up;}



void GameGUI::drawRectangle(const SolidRectangle& rect, ALLEGRO_COLOR color){
    float x1 = rect.getPosition().getX() + LEFT_BORDER_WIDTH;
    float y1 = rect.getPosition().getY() + UPPER_BORDER_HEIGHT;
    float x2 = x1 + rect.getWidth();
    float y2 = y1 + rect.getHeight();
    al_draw_filled_rectangle(x1, y1, x2, y2, color);
}

void GameGUI::drawRectangleWithTexture(const SolidRectangle& rect, const std::string& texturePath){
    
    float x1 = rect.getPosition().getX() + LEFT_BORDER_WIDTH;
    float y1 = rect.getPosition().getY() + UPPER_BORDER_HEIGHT;

    ALLEGRO_BITMAP* racketTexture = TextureManager::getTexture(texturePath);
    if (racketTexture) {
    al_draw_scaled_bitmap(
        racketTexture, 0, 0,
        al_get_bitmap_width(racketTexture), al_get_bitmap_height(racketTexture),
        x1, y1, rect.getWidth(), rect.getHeight(), 0);
    }
}

void GameGUI::drawCircle(const SolidCircle& circle, ALLEGRO_COLOR color){
    float x = circle.getPosition().getX() + LEFT_BORDER_WIDTH;
    float y = circle.getPosition().getY() + UPPER_BORDER_HEIGHT;
    float radius = circle.getRadius();
    al_draw_filled_circle(x, y, radius, color);
}

void GameGUI::drawText(const Position2D& pos, std::string text) {
    al_draw_text(getAllegroFont(), DEFAULT_FONT_COLOR, pos.getX(), pos.getY(), ALLEGRO_ALIGN_CENTER, text.c_str());
}

void GameGUI::updateFPS(){
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> delta = currentTime - getLastUpdate();
    float fps = (delta.count() > 0) ? (1.0f / delta.count()) : 0.0f;
    al_set_window_title(getAllegroDisplay(), ("Arkanoid - FPS: " + std::to_string(fps)).c_str());
    setLastUpdate(currentTime);
}

void GameGUI::clearScreen() {
    al_clear_to_color(DEFAULT_BACKGROUND_COLOR);
}

void GameGUI::updateGUI(){

    clearScreen();
    
    std::string score = "Score: " + std::to_string(getPlayer()->getScore().getValue());
    std::string lives = "Lives: " + std::to_string(getPlayer()->getHp());
    drawText(Position2D(350, 10), score);
    drawText(Position2D(250, 10), lives);

    // drawRectangle(getGameBox()->getRacket()->getHitbox(), al_map_rgb(0, 0, 255));
    drawRectangleWithTexture(getGameBox()->getRacket()->getHitbox(), "./assets/racket.png");

    for (auto& ball : getGameBox()->getBalls()) {
        drawCircle(ball->getHitbox(), al_map_rgb(255, 0, 0));
    }

    for (auto& brick : getGameBox()->getBricks()) {
        drawRectangle((*brick).getHitbox(), BRICK_COLORS.at(static_cast<int>((*brick).getBrickType())));

        const char* letter = nullptr;

        if (dynamic_cast<ResizeBonus*>(brick->getBonus())) {
            letter = "R";
        } else if (dynamic_cast<PlayerBonus*>(brick->getBonus())) {
            letter = "P";
        } else if (dynamic_cast<DuplicationBonus*>(brick->getBonus())) {
            letter = "D";
        }

        if (letter) {
            SolidRectangle hitbox = brick->getHitbox();
            float centerX = hitbox.getPosition().getX() + hitbox.getWidth() / 2;
            float centerY = hitbox.getPosition().getY() + hitbox.getHeight() / 2;

            al_draw_text(getAllegroFont(), al_map_rgb(255, 255, 255), centerX, centerY, ALLEGRO_ALIGN_CENTER, letter);
        }
    }

    for (auto& bonus : getGameBox()->getBonuses()) {

        if (dynamic_cast<ResizeBonus*>(bonus)) {
            drawRectangle((*bonus).getHitbox(), al_map_rgb(0, 0, 255)); 
        } else if (dynamic_cast<PlayerBonus*>(bonus)) {
            drawRectangle((*bonus).getHitbox(), al_map_rgb(128, 128, 128)); 
        } else if (dynamic_cast<DuplicationBonus*>(bonus)) {
            drawRectangle((*bonus).getHitbox(), al_map_rgb(43, 255, 255));
        }
    }

    updateFPS();
    al_flip_display();
}