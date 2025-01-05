#include "../../include/gui.hpp"

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

bool GameGUI::isInGameOverState() {
    return _isInGameOverState;
}

void GameGUI::setIsInGameOverState(bool flag) {
    _isInGameOverState = flag;
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

void GameGUI::handleGameoverState() {
    setIsInGameOverState(getPlayer()->isDead());
}

void GameGUI::drawStatistics() {
    std::string score     = "Score: " + std::to_string(getPlayer()->getScore().getValue());
    std::string lives     = "Lives: " + std::to_string(getPlayer()->getHp());
    std::string highScore = "High Score: " + std::to_string(getPlayer()->getHighScore().getValue());

    drawText(Position2D(GAME_WIDTH * 0.25f + BOX_WALLS_THICKNESS, BOX_WALLS_THICKNESS / 2), score);
    drawText(Position2D(GAME_WIDTH * 0.5f + BOX_WALLS_THICKNESS, BOX_WALLS_THICKNESS / 2), lives);
    drawText(Position2D(GAME_WIDTH * 0.75f + BOX_WALLS_THICKNESS, BOX_WALLS_THICKNESS / 2),
             highScore);
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

        // and then draw the letter on the brick
        if (brick->doesBrickContainBonus()) {
            drawText(Position2D(brick->getCenterPosition().getX() + BOX_WALLS_THICKNESS,
                                brick->getCenterPosition().getY() + BOX_WALLS_THICKNESS),
                     std::string(1, BONUS_IDENTIFIER.at(brick->getBonus()->getBonusType())));
        }
    }
}

void GameGUI::drawBalls() {
    // Balls are simple. Be like balls. Be simple, please.
    for (auto& ball : getGameBox()->getBalls()) {
        drawCircle(ball->getHitbox(), DEFAULT_BALL_COLOR);
    }
}

void GameGUI::drawRacket() {
    // drawing the racket
    drawRectangleWithTexture(getGameBox()->getRacket()->getHitbox(), RACKET_TEXTURE_PATH);
    // and then the sticky ball if the player is holding a ball
    if (getPlayer()->hasBallStored()) {
        drawCircle(
            SolidCircle(Position2D(getGameBox()->getRacket()->getCenterPosition().getX(),
                                   getGameBox()->getRacket()->getPosition().getY() - BALL_RADIUS),
                        BALL_RADIUS),
            DEFAULT_BALL_COLOR);
    }
}

void GameGUI::drawBonuses() {
    for (auto& bonus : getGameBox()->getBonuses()) {
        if (!bonus->isActive()) {
            drawRectangleWithTexture(bonus->getHitbox(),
                                     BONUS_TEXTURE_PATH.at(bonus->getBonusType()));
        }
    }
}

void GameGUI::drawLasers() {
    for (auto& laser : getGameBox()->getLasers()) {
        drawRectangleWithTexture(laser->getHitbox(), LASER_TEXTURE_PATH);
    }
}

void GameGUI::drawGameOver() {
    std::string gameOverText = "GAME OVER - Press ENTER to try again";
    std::string scoreText    = "Your Score: " + std::to_string(getPlayer()->getScore().getValue());
    std::string highScoreText =
        "Your Best Score: " + std::to_string(getPlayer()->getHighScore().getValue());

    float textHeight = static_cast<float>(al_get_font_line_height(_font));
    float spacing    = textHeight * 2;
    float startY     = (GAME_HEIGHT / 2) - spacing;

    // Dessiner les textes avec un espacement proportionnel
    drawText(Position2D(GAME_WIDTH / 2 + BOX_WALLS_THICKNESS, startY + BOX_WALLS_THICKNESS),
             gameOverText);
    drawText(
        Position2D(GAME_WIDTH / 2 + BOX_WALLS_THICKNESS, startY + spacing + BOX_WALLS_THICKNESS),
        scoreText);
    drawText(Position2D(GAME_WIDTH / 2 + BOX_WALLS_THICKNESS,
                        startY + 2 * spacing + BOX_WALLS_THICKNESS),
             highScoreText);
}

void GameGUI::updateGUI() {
    clearScreen();
    handleGameoverState();

    if (!isInGameOverState()) {
        drawBoard();
        drawRacket();
        drawBalls();
        drawBricks();
        drawStatistics();
        drawBonuses();
        drawLasers();
    } else {
        drawGameOver();
    }

    updateFPS();
    al_flip_display();
}