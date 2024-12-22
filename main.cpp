#include "src/player/controller.hpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "src/game/game_box.hpp"
#include "src/game/ball.hpp"
#include "src/game/racket.hpp"
#include "src/game/brick.hpp"
#include "src/player/score.hpp"
#include "src/common.hpp"

using namespace std;

void must_init(bool test, const char* description) {
  if (test) return;

  std::cerr << "couldn't initialize" << description << '\n';
  exit(1);
}

int main(int /* argc */, char** /* argv */) {

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY* disp = al_create_display(800, 800);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool          done = false;
    ALLEGRO_EVENT event;
    GameController controller;

    al_start_timer(timer);
    while (!done) {
        al_wait_for_event(queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_KEY_DOWN: 
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        controller.getUserAction(ALLEGRO_KEY_LEFT);
                        done = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        controller.getUserAction(ALLEGRO_KEY_RIGHT);
                        break;
                }
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:  // Si la fenêtre est fermée
                done = true;
                break;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}