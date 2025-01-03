#include "level_reader.hpp"

#include "../../src/game/game_box.hpp"
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


void LevelReader::initializeGameBoard(const std::vector<std::vector<std::string>>& tiles) {


    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            std::cout << tile << " ";
        }
        std::cout << std::endl;
    }

}
