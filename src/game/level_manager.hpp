#pragma once

#include "./game_box.hpp"

class LevelManager {
   private:
    std::vector<std::string> _LevelsFilepaths;
    int                      _currentLevelIndex;

   public:
    LevelManager(std::vector<std::string> levelsFilepaths)
        : _LevelsFilepaths{levelsFilepaths}, _currentLevelIndex{0} {
    }

    ~LevelManager() = default;
    std::vector<std::string> getLevelsFilepaths();
    int                      getCurrentLevelIndex();
    void                     setCurrentLevelIndex(int idx);
    void                     goToNextLevel();
    void                     goToPreviousLevel();
    GameBox*                 generateCurrentLevelGamebox();
};