#include "./level_manager.hpp"
#include "./level_reader.hpp"

std::vector<std::string> LevelManager::getLevelsFilepaths() {
    return _LevelsFilepaths;
}

int LevelManager::getCurrentLevelIndex() {
    return _currentLevelIndex;
}

void LevelManager::setCurrentLevelIndex(int idx) {
    _currentLevelIndex = idx;
}

void LevelManager::goToNextLevel() {
    int levelCount = static_cast<int>(getLevelsFilepaths().size());
    setCurrentLevelIndex((getCurrentLevelIndex() + 1) % levelCount);
}

void LevelManager::goToPreviousLevel() {
    int levelCount = static_cast<int>(getLevelsFilepaths().size());
    int new_idx =
        (getCurrentLevelIndex() - 1 < 0) ? (levelCount - 1) : (getCurrentLevelIndex() - 1);
    setCurrentLevelIndex(new_idx);
}

GameBox* LevelManager::generateCurrentLevelGamebox() {
    return LevelReader::initializeGameBoard(LevelReader::parseRawFile(
        LevelReader::readFile(getLevelsFilepaths().at(getCurrentLevelIndex()))));
}