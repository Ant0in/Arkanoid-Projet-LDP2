#include "gui.hpp"

ALLEGRO_DISPLAY* GameGUI::getAllegroDisplay() {
    return _display;
}
ALLEGRO_FONT* GameGUI::getAllegroFont() {
    return _font;
}

GameBox* GameGUI::getGameBox() {
    return _gamebox;
}

Player* GameGUI::getPlayer() {
    return _player;
}

std::chrono::high_resolution_clock::time_point GameGUI::getLastUpdate() {
    return _last_update;
}

void GameGUI::setLastUpdate(std::chrono::high_resolution_clock::time_point up) {
    _last_update = up;
}

void GameGUI::drawRectangle(const SolidRectangle& rect, ALLEGRO_COLOR color) {
    float x1 = rect.getPosition().getX() + BOX_WALLS_THICKNESS;
    float y1 = rect.getPosition().getY() + BOX_WALLS_THICKNESS;
    float x2 = x1 + rect.getWidth();
    float y2 = y1 + rect.getHeight();
    al_draw_filled_rectangle(x1, y1, x2, y2, color);
}

void GameGUI::drawRectangleWithTexture(const SolidRectangle& rect, const std::string& texturePath) {
    float x1 = rect.getPosition().getX() + BOX_WALLS_THICKNESS;
    float y1 = rect.getPosition().getY() + BOX_WALLS_THICKNESS;

    ALLEGRO_BITMAP* racketTexture = TextureManager::getTexture(texturePath);
    if (racketTexture) {
        al_draw_scaled_bitmap(racketTexture,
                              0,
                              0,
                              static_cast<float>(al_get_bitmap_width(racketTexture)),
                              static_cast<float>(al_get_bitmap_height(racketTexture)),
                              x1,
                              y1,
                              rect.getWidth(),
                              rect.getHeight(),
                              0);
    }
}

void GameGUI::drawCircle(const SolidCircle& circle, ALLEGRO_COLOR color) {
    float x      = circle.getPosition().getX() + BOX_WALLS_THICKNESS;
    float y      = circle.getPosition().getY() + BOX_WALLS_THICKNESS;
    float radius = circle.getRadius();
    al_draw_filled_circle(x, y, radius, color);
}

void GameGUI::drawText(const Position2D& pos, std::string text) {
    al_draw_text(getAllegroFont(),
                 DEFAULT_FONT_COLOR,
                 pos.getX(),
                 pos.getY(),
                 ALLEGRO_ALIGN_CENTER,
                 text.c_str());
}

void GameGUI::updateFPS() {
    auto                         currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> delta       = currentTime - getLastUpdate();
    float                        fps         = (delta.count() > 0) ? (1.0f / delta.count()) : 0.0f;
    al_set_window_title(getAllegroDisplay(), ("Arkanoid - FPS: " + std::to_string(fps)).c_str());
    setLastUpdate(currentTime);
}

void GameGUI::clearScreen() {
    al_clear_to_color(DEFAULT_BACKGROUND_COLOR);
}

void GameGUI::drawStatistics() {
    std::string score     = "Score: " + std::to_string(getPlayer()->getScore().getValue());
    std::string lives     = "Lives: " + std::to_string(getPlayer()->getHp());
    std::string highScore = "High Score: " + std::to_string(getPlayer()->getHighScore().getValue());

    // TODO : Remove magic numbers
    drawText(Position2D(350, 15), score);
    drawText(Position2D(250, 15), lives);
    drawText(Position2D(500, 15), highScore);
}

void GameGUI::drawBoard() {
    // First we do the background and then walls ans finally ceilling
    drawRectangleWithTexture(getGameBox()->getHitbox(), BACKGROUND_TEXTURE_PATH);
    drawRectangleWithTexture(getGameBox()->getLeftWall(), SIDE_WALLS_TEXTURE_PATH);
    drawRectangleWithTexture(getGameBox()->getRightWall(), SIDE_WALLS_TEXTURE_PATH);
    drawRectangleWithTexture(getGameBox()->getTopWall(), TOP_WALL_TEXTURE_PATH);
}

void GameGUI::drawBricks() {
    for (auto& brick : getGameBox()->getBricks()) {
        std::string texture;

        if (brick->getBrickType() == BrickType::SILVER &&
            brick->getHP() < Brick::getBrickHpByType(BrickType::SILVER)) {
            texture = DAMAGED_SILVER_TEXTURE;
        } else {
            texture = BRICK_TEXTURE_PATH.at(brick->getBrickType());
        }

        drawRectangleWithTexture(brick->getHitbox(), texture);

        // TODO : Write letters on bricks with bonuses.
    }
}

void GameGUI::drawBalls() {
    // Balls are simple. Be like balls. Be simple, please.
    for (auto& ball : getGameBox()->getBalls()) {
        drawCircle(ball->getHitbox(), DEFAULT_BALL_COLOR);
    }
}

void GameGUI::drawRacket() {
    drawRectangleWithTexture(getGameBox()->getRacket()->getHitbox(), RACKET_TEXTURE_PATH);
}

void GameGUI::drawBonuses() {
    for (auto& bonus : getGameBox()->getBonuses()) {
        std::string texture;

        if (dynamic_cast<ResizeBonus*>(bonus)) {
            texture = RESIZE_BONUS_TEXTURE;
        } else if (dynamic_cast<PlayerBonus*>(bonus)) {
            texture = PLAYER_BONUS_TEXTURE;
        } else if (dynamic_cast<DuplicationBonus*>(bonus)) {
            texture = DUPLICATION_BONUS_TEXTURE;
        }

        if (!bonus->isActive()) {
            drawRectangleWithTexture(bonus->getHitbox(), texture);
        }
    }
}

void GameGUI::updateGUI() {
    clearScreen();
    drawBoard();
    drawRacket();
    drawBalls();
    drawBricks();
    drawStatistics();
    drawBonuses();
    updateFPS();
    al_flip_display();
}