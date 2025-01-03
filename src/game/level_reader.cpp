#include "level_reader.hpp"

#include "./brick.hpp"
#include "./ball.hpp"
#include "./racket.hpp"
#include "./bonus.hpp"

#include "../common.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>


std::vector<std::string> LevelReader::readFile(const std::string& filePath) {

    std::ifstream file(filePath, std::ios::in);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    std::vector<std::string> rawLines;
    std::string line;

    while (std::getline(file, line)) {
        rawLines.push_back(line);
    }

    file.close();
    return rawLines;

}

std::vector<std::vector<std::string>> LevelReader::parseRawFile(const std::vector<std::string>& raw) {

    std::vector<std::vector<std::string>> board;

    for (const auto& line : raw) {
        std::istringstream stream(line);
        std::vector<std::string> row;
        std::string brick;

        while (stream >> brick) {
            row.push_back(brick);
        }

        board.push_back(row);
    }

    return board;
}

GameBox* LevelReader::initializeGameBoard(const std::vector<std::vector<std::string>>& tiles) {

    // initializing racket and then gamebox (spawning balls is not important yet)
    Racket* r = new Racket(RACKET_DEFAULT_POSITION, RACKET_WIDTH, RACKET_HEIGHT, RACKET_DEFAULT_SENSIBILITY);
    GameBox* gamebox = new GameBox(DEFAULT_CORNER_POS, GAME_WIDTH, GAME_HEIGHT, r);

    // lets then grab the matrix size (no padding, expect coherent dim)
    int brickRowSize = static_cast<int>(tiles.size());
    int brickLineSize = tiles.empty() ? 0 : static_cast<int>(tiles[0].size());

    // calculate offsets (for vertical offset, we use the upper 2.5 part of the screen to display bricks)
    float horizontalOffset = (gamebox->getWidth() - (BRICK_WIDTH * (static_cast<float>(brickLineSize))))
                                / (static_cast<float>(brickLineSize) + 1);
    float verticalOffset = ((gamebox->getHeight() / 2.5f) - (BRICK_HEIGHT * (static_cast<float>(brickRowSize))))
                                / (static_cast<float>(brickRowSize) + 1);

    for (int y = 0; y < brickRowSize; ++y) {
        for (int x = 0; x < brickLineSize; ++x) {

            // (x, y) is the relative position, not in term of pixels. we will calculate abs x, y.
            float abs_x = static_cast<float>(x) * (BRICK_WIDTH + horizontalOffset) + horizontalOffset;
            float abs_y = static_cast<float>(y) * (BRICK_HEIGHT + verticalOffset) + verticalOffset;

            BrickType brickType = BRICK_ID.at(tiles[y][x][0] - '0');

            BonusInterface* bonus = nullptr;
            char bonusID = tiles[y][x][1];

            switch (bonusID) {

                case DUPLICATION_BONUS_IDENTIFIER: bonus = new DuplicationBonus(Position2D(abs_x, abs_y)); break;
                case PLAYER_BONUS_IDENTIFIER: bonus = new PlayerBonus(Position2D(abs_x, abs_y)); break;
                case RESIZE_BONUS_IDENTIFIER: bonus = new ResizeBonus(Position2D(abs_x, abs_y)); break;

                default: break;
            }

            Brick* b = new Brick(
                Position2D(abs_x, abs_y),
                BRICK_WIDTH,
                BRICK_HEIGHT,
                brickType,
                bonus);
            
            gamebox->addBrick(b);

        }

    }

    return gamebox;
}
