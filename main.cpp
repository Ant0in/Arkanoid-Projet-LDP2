#include "src/player/controller.hpp"
#include "src/game/game_box.hpp"
#include "src/game/ball.hpp"
#include "src/game/racket.hpp"
#include "src/game/brick.hpp"
#include "src/common.hpp"
#include "src/gui/gui.hpp"
#include "src/player/player.hpp"
#include "src/physics/engine.hpp"
#include "src/levels/level_reader.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

int main() {

    if (!al_init()) {
        fprintf(stderr, "Erreur : Impossible d'initialiser Allegro.\n");
        return -1;
    }
    
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_DISPLAY* display = al_create_display(static_cast<int>(GAME_WIDTH), static_cast<int>(GAME_HEIGHT));
    if (!display) {
        fprintf(stderr, "Erreur : Impossible de créer la fenêtre.\n");
        return -1;
    }

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / GAME_FRAMERATE);

    if (!event_queue || !timer) {
        fprintf(stderr, "Erreur : Problème avec Allegro (timer ou event queue).\n");
        al_destroy_display(display);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    GameBox* gamebox = new GameBox(
        DEFAULT_CORNER_POS, GAME_WIDTH, GAME_HEIGHT,
        std::vector<Ball*>{new Ball(DEFAULT_SPAWN_POSITION)},
        new Racket(RACKET_DEFAULT_POSITION, RACKET_WIDTH, RACKET_HEIGHT, RACKET_DEFAULT_SENSIBILITY));

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (float i = 0; i < 12; ++i) {
        for (float y = 50 + i * 25, x = 30; x < 770; x += 50) {
            
            int randomType = (std::rand() % 10) + 1;  //random brick type
            BonusInterface* bonus = nullptr;

            if ((std::rand() % 100) < 40) { // 40% chance to get a bonus
                int bonusType = std::rand() % 3;
                if (bonusType == 0) {
                    bonus = new DuplicationBonus(Position2D(x, y));
                } else if (bonusType == 1) {
                    bonus = new PlayerBonus(Position2D(x, y));
                } else {
                    bonus = new ResizeBonus(Position2D(x, y));
                }
            }
            // Create brick with or without bonus
            Brick* b = new Brick(Position2D(x, y), 48, 20, BrickType(randomType), bonus);
            gamebox->addBrick(b);
        }
    }

    GameController controller = GameController();
    Player* player = new Player(PLAYER_DEFAULT_HEALTH, controller);
    GameGUI gui = GameGUI(display, gamebox, player);

    bool running = true;
    while (running) {

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // on quit
            running = false;

        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            // on key press
            player->getController().updateUserAction(event.keyboard.keycode); 

        } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            // on key release
            player->getController().updateUserAction(0); 

        } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            // on mouse move
            player->getController().updateMousePosition(
                Position2D(
                    static_cast<float>(event.mouse.x),
                    static_cast<float>(event.mouse.y)
                )
            );

        } else if (event.type == ALLEGRO_EVENT_TIMER) {
            // on timer (handling game physics)
            GameEngine::handleRoutine(*gamebox, *player);
            gui.updateGUI();
            al_flip_display();
        }
    }

    std::cout << "reached here" << std::endl;

    // Destroying stuff at the end
    al_destroy_event_queue(event_queue);
    al_uninstall_keyboard();
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_uninstall_system();

    delete gamebox;
    delete player;

    return 0;

}
