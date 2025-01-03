#pragma once

#include <string>
#include <vector>

class LevelReader {

public:

    static std::vector<std::string> readFile(const std::string& filePath);
    static std::vector<std::vector<std::string>> parseRawFile(const std::vector<std::string>& raw);
    static void initializeGameBoard(const std::vector<std::vector<std::string>>& tiles);
    
};
