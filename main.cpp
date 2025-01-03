#include "src/player/controller.hpp"
#include "src/game/game_box.hpp"
#include "src/game/ball.hpp"
#include "src/game/racket.hpp"
#include "src/game/brick.hpp"
#include "src/common.hpp"
#include "src/gui/gui.hpp"
#include "src/player/player.hpp"
#include "src/physics/engine.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {

    if (!al_init()) {
        fprintf(stderr, "Erreur : Impossible d'initialiser Allegro.\n");
        return -1;
    }
    
    al_init_primitives_addon();
    al_install_keyboard();

    const int WIDTH = 800, HEIGHT = 800;

    ALLEGRO_DISPLAY* display = al_create_display(WIDTH, HEIGHT);
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
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    GameBox* gamebox = new GameBox(Position2D(0, 0), WIDTH, HEIGHT,
        std::vector<Ball*>{new Ball(Position2D(400, 450))},
        new Racket(Position2D(300, 700), 200, 20, 10));

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
    Player player = Player(3, controller);
    GameGUI gui = GameGUI(display, gamebox);

    bool running = true;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            player.getController().updateUserAction(event.keyboard.keycode); 
        } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            player.getController().updateUserAction(0); 
        } else if (event.type == ALLEGRO_EVENT_TIMER) {
            GameEngine::handleRoutine(*gamebox, player);
            gui.updateGUI();
            al_flip_display();
        }
    }

    delete gamebox;

    al_destroy_event_queue(event_queue);
    al_uninstall_keyboard();
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_uninstall_system();

    return 0;
}
