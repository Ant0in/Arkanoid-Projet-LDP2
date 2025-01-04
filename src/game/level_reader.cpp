#include "level_reader.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "../common.hpp"
#include "./ball.hpp"
#include "./bonus.hpp"
#include "./brick.hpp"
#include "./racket.hpp"

std::vector<std::string> LevelReader::readFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::in);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    std::vector<std::string> rawLines;
    std::string              line;

    while (std::getline(file, line)) {
        rawLines.push_back(line);
    }

    file.close();
    return rawLines;
}

std::vector<std::vector<std::string>> LevelReader::parseRawFile(
    const std::vector<std::string>& raw) {
    std::vector<std::vector<std::string>> board;

    for (const auto& line : raw) {
        std::istringstream       stream(line);
        std::vector<std::string> row;
        std::string              brick;

        while (stream >> brick) {
            row.push_back(brick);
        }

        board.push_back(row);
    }

    return board;
}

GameBox* LevelReader::initializeGameBoard(const std::vector<std::vector<std::string>>& tiles) {
    // initializing racket and then gamebox (spawning balls is not important yet)
    Racket* r = new Racket(
        RACKET_DEFAULT_POSITION, RACKET_WIDTH, RACKET_HEIGHT, RACKET_DEFAULT_SENSIBILITY);
    GameBox* gamebox = new GameBox(DEFAULT_CORNER_POS, GAME_WIDTH, GAME_HEIGHT, r);

    // lets then grab the matrix size (no padding, expect coherent dim)
    int brickRowSize  = static_cast<int>(tiles.size());
    int brickLineSize = tiles.empty() ? 0 : static_cast<int>(tiles[0].size());

    // calculate offsets (for vertical offset, we use the upper 2.5 part of the screen to display
    // bricks)
    float horizontalOffset =
        (gamebox->getWidth() - (BRICK_WIDTH * (static_cast<float>(brickLineSize)))) /
        (static_cast<float>(brickLineSize) + 1);
    float verticalOffset =
        ((gamebox->getHeight() / 2.5f) - (BRICK_HEIGHT * (static_cast<float>(brickRowSize)))) /
        (static_cast<float>(brickRowSize) + 1);

    for (int y = 0; y < brickRowSize; ++y) {
        for (int x = 0; x < brickLineSize; ++x) {
            // (x, y) is the relative position, not in term of pixels. we will calculate abs x, y.
            float abs_x =
                static_cast<float>(x) * (BRICK_WIDTH + horizontalOffset) + horizontalOffset;
            float abs_y = static_cast<float>(y) * (BRICK_HEIGHT + verticalOffset) + verticalOffset;

            BrickType brickType = BRICK_ID.at(tiles[y][x][0] - '0');

            BonusInterface* bonus      = nullptr;
            char            bonus_char = tiles[y][x][1];

            if (bonus_char == BONUS_IDENTIFIER.at(BonusType::DUPLICATION)) {
                bonus = new DuplicationBonus(Position2D(abs_x, abs_y));
            } else if (bonus_char == BONUS_IDENTIFIER.at(BonusType::PLAYER)) {
                bonus = new PlayerBonus(Position2D(abs_x, abs_y));
            } else if (bonus_char == BONUS_IDENTIFIER.at(BonusType::RESIZE)) {
                bonus = new ResizeBonus(Position2D(abs_x, abs_y));
            } else if (bonus_char == BONUS_IDENTIFIER.at(BonusType::GRAB)) {
                bonus = new GrabBonus(Position2D(abs_x, abs_y));
            } else if (bonus_char == BONUS_IDENTIFIER.at(BonusType::LASER)) {
                // TODO ; lasers
                std::cout
                    << "[levelReader] Please write the bonus initialization with it's identifier!"
            } else if (bonus_char == BONUS_IDENTIFIER.at(BonusType::SLOW)) {
                // TODO ; slow
                std::cout
                    << "[levelReader] Please write the bonus initialization with it's identifier!"
            } else {
            }

            Brick* b =
                new Brick(Position2D(abs_x, abs_y), BRICK_WIDTH, BRICK_HEIGHT, brickType, bonus);

            gamebox->addBrick(b);
        }
    }

    return gamebox;
}

std::vector<std::string> LevelReader::findEveryMapFilepathInFolder(const std::string& folderPath) {
    std::vector<std::string> mapFiles;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".map") {
                mapFiles.push_back(entry.path().string());
            }
        }

        std::sort(mapFiles.begin(), mapFiles.end());
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Erreur lors de l'accès au répertoire : " << e.what() << std::endl;
    }

    return mapFiles;
}