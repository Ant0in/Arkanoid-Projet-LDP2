
#include "src/game/game_box.hpp"
#include "src/game/level_reader.hpp"
#include "src/player/controller.hpp"
#include "src/player/player.hpp"

#include "src/common.hpp"

#include "src/gui/gui.hpp"

#include "src/physics/engine.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

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
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_DISPLAY* display = al_create_display(
        static_cast<int>(GAME_WIDTH + 2 * BOX_WALLS_THICKNESS),
        static_cast<int>(GAME_HEIGHT + BOX_WALLS_THICKNESS)
    );
    
    if (!display) {
        fprintf(stderr, "Erreur : Impossible de créer la fenêtre.\n");
        return -1;
    }

    ALLEGRO_FONT* font = al_create_builtin_font();

    if (!font) {
        fprintf(stderr, "Erreur : Impossible de créer la police.\n");
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


    GameBox* gamebox = LevelReader::initializeGameBoard(LevelReader::parseRawFile(LevelReader::readFile("./src/maps/1.map")));
    GameController controller = GameController();
    Player* player = new Player(PLAYER_DEFAULT_HEALTH, controller);
    GameGUI gui = GameGUI(display, font, gamebox, player);

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

    std::cout << "Exiting..." << std::endl;

    // Destroying stuff at the end
    al_destroy_event_queue(event_queue);
    al_uninstall_keyboard();
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_uninstall_system();

    delete gamebox;
    delete player;

    // TODO : fix le segfault du release des bitmaps
    TextureManager::releaseAllTextures();

    return 0;

}
