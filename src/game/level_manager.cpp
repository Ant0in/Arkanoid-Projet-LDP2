#include "../../include/level_manager.hpp"
#include "../../include/level_reader.hpp"

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
    // we make sure we dont go out of bounds
    int levelCount = static_cast<int>(getLevelsFilepaths().size());
    setCurrentLevelIndex((getCurrentLevelIndex() + 1) % levelCount);
}

void LevelManager::goToPreviousLevel() {
    // going back when at the first level is going to the last level, for some reason (I like that
    // idea, as an og mario speedrunner, minus world, allat lol)
    int levelCount = static_cast<int>(getLevelsFilepaths().size());
    int new_idx =
        (getCurrentLevelIndex() - 1 < 0) ? (levelCount - 1) : (getCurrentLevelIndex() - 1);
    setCurrentLevelIndex(new_idx);
}

GameBox* LevelManager::generateCurrentLevelGamebox() {
    // read the level file, parse it and then initialize the game board
    return LevelReader::initializeGameBoard(LevelReader::parseRawFile(
        LevelReader::readFile(getLevelsFilepaths().at(getCurrentLevelIndex()))));
}