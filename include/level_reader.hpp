#pragma once

#include <string>
#include <vector>

#include "game_box.hpp"

class LevelReader {
   public:
    static std::vector<std::string>              readFile(const std::string& filePath);
    static std::vector<std::vector<std::string>> parseRawFile(const std::vector<std::string>& raw);
    static GameBox* initializeGameBoard(const std::vector<std::vector<std::string>>& tiles);
    static std::vector<std::string> findEveryMapFilepathInFolder(const std::string& filePath);
};
