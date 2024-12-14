#include "controller.hpp"
#include "common.hpp"

class GameController{
    private:
        std::unordered_map<int, int> DEFAULT;
        std::unordered_map<int, int> config;
    public:
        GameController(const std::unordered_map<int, int>& userConfig): config{userConfig}{}
        GameController(){
            DEFAULT[ALLEGRO_KEY_LEFT] = static_cast<int>(Action::LEFT);
            DEFAULT[ALLEGRO_KEY_RIGHT] = static_cast<int>(Action::RIGHT);
            config = DEFAULT;
        }

        const std::unordered_map<int, int>& getConfig() const {return config;}

        const int getUserAction() const{
            // For every key, check if player is pressing it (polling)

            // MARCHE PASSSSSSSSSSSSSSSSSSS


            ALLEGRO_KEYBOARD_STATE keyState;
            al_get_keyboard_state(&keyState);
            for (const auto& [key, value] : config){
                if (al_key_down(&keyState, key)){
                    std::cout<<"yo";
                    return value;
                }
            }
            return static_cast<int>(Action::NONE);
        }
};  