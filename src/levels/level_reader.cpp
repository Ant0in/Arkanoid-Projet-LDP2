#include "level_reader.hpp"

#include "../../src/game/brick.hpp"
#include "../../src/game/ball.hpp"
#include "../../src/game/racket.hpp"
#include "../../src/game/bonus.hpp"

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

    // calculate offsets
    float horizontalOffset = gamebox->getWidth() - (BRICK_WIDTH * (static_cast<float>(brickLineSize) + 1));

    for (int y = 0; y < brickRowSize; ++y) {
        for (int x = 0; x < brickLineSize; ++x) {

            // (x, y) is the relative position, not in term of pixels. useful to get btype in "tiles"
            BonusInterface* bonus = nullptr;
            
            float abs_x = static_cast<float>(x) * (horizontalOffset + BRICK_WIDTH);
            float abs_y = static_cast<float>(y) * BRICK_HEIGHT;

            Brick* b = new Brick(
                Position2D(abs_x, abs_y),
                BRICK_WIDTH,
                BRICK_HEIGHT,
                BrickType(0),
                bonus);
            
            gamebox->addBrick(b);

        }

    }

    return gamebox;
}
