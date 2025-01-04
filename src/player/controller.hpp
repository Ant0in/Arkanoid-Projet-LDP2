#pragma once

#include <allegro5/allegro5.h>

#include <iostream>
#include <string>
#include <unordered_map>

#include "../common.hpp"

class GameController {
   private:
    std::unordered_map<int, Action> _config;
    Action                          _currentAction;
    Position2D                      _currentMousePosition;
    bool                            _hasMouseMoved;

   public:
    GameController(const std::unordered_map<int, Action>& userConfig = DEFAULT_CONFIG)
        : _config{userConfig},
          _currentAction{Action::NONE},
          _currentMousePosition{DEFAULT_MOUSE_POS},
          _hasMouseMoved{false} {
    }

    ~GameController() = default;

    Action                                 getCurrentAction();
    void                                   setCurrentAction(const Action& action);
    Position2D                             getCurrentMousePosition();
    void                                   setCurrentMousePosition(const Position2D& pos);
    bool                                   hasMouseMoved();
    void                                   setHasMouseMoved(bool flag);
    const std::unordered_map<int, Action>& getConfig() const;
    void                                   updateUserAction(int keyCode = 0);
    void                                   updateMousePosition(const Position2D& position);
};