#include "gui.hpp"


ALLEGRO_DISPLAY* GameGUI::getAllegroDisplay() {return _display;}
GameBox* GameGUI::getGameBox() {return _gamebox;}
Player* GameGUI::getPlayer() {return _player;}
std::chrono::high_resolution_clock::time_point GameGUI::getLastUpdate() {return _last_update;}

void GameGUI::drawRectangle(const SolidRectangle& rect, ALLEGRO_COLOR color){
    float x1 = rect.getPosition().getX();
    float y1 = rect.getPosition().getY();
    float x2 = x1 + rect.getWidth();
    float y2 = y1 + rect.getHeight();
    al_draw_filled_rectangle(x1, y1, x2, y2, color);
}
void GameGUI::drawCircle(const SolidCircle& circle, ALLEGRO_COLOR color){
    float x = circle.getPosition().getX();
    float y = circle.getPosition().getY();
    float radius = circle.getRadius();
    al_draw_filled_circle(x, y, radius, color);
}

void GameGUI::updateFPS(){
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> delta = currentTime - getLastUpdate();
    float fps = 0;
    if (delta.count() > 0){fps = 1 / delta.count();}
    al_set_window_title(getAllegroDisplay(), ("Arkanoid - FPS: " + std::to_string(fps)).c_str());
    _last_update = currentTime;  // FIX THIS TODO PLEASE MAKE A SETTER
}

void GameGUI::updateGUI(){

    al_clear_to_color(al_map_rgb(0, 0, 0));

    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font) {
        fprintf(stderr, "Erreur : Impossible de créer la police.\n");
        return;
    }
    std::string score = "Score: " + std::to_string(getPlayer()->getScore().getValue());
    std::string lives = "Lives: " + std::to_string(getPlayer()->getHp());
    al_draw_text(font, al_map_rgb(255, 255, 255), 350, 10, ALLEGRO_ALIGN_CENTER, score.c_str());
    al_draw_text(font, al_map_rgb(255, 255, 255), 250, 10, ALLEGRO_ALIGN_CENTER, lives.c_str()); 

    drawRectangle(getGameBox()->getRacket()->getHitbox(), al_map_rgb(0, 0, 255));

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

            al_draw_text(font, al_map_rgb(255, 255, 255), centerX, centerY, ALLEGRO_ALIGN_CENTER, letter);
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