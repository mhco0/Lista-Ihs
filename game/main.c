#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#define FPS 60
#define MIN 0
#define SEC 15

int main() {
    srand(time(NULL));
    
    al_init();
    al_install_keyboard();

    al_set_new_display_flags(ALLEGRO_FULLSCREEN | ALLEGRO_FULLSCREEN_WINDOW);

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_DISPLAY *disp = al_create_display(800, 600);
    ALLEGRO_FONT *font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    size_t i = 0;

    size_t eta_min;
    size_t eta_sec;

    size_t password;

    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while (true){
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if (event.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)) {
            const int cycle = (MIN * 60 + SEC) * FPS;

            if (i % cycle == 0) {
                eta_min = MIN;
                eta_sec = SEC;
                
                password = rand() % 65536;
            } else if (i % FPS == 0) {
                if (eta_sec == 0) {
                    --eta_min;
                    eta_sec = 60;
                } else
                    --eta_sec;
            }



            al_clear_to_color(al_map_rgb(
                fmax(0, fmin(255, 255 * sin(M_PI * i / cycle))),
                fmax(0, fmin(255, 255 * cos(M_PI * i / cycle))),
                fmax(0, fmin(255, 255 * sin(M_PI * i / cycle) * cos(M_PI * i / cycle)))
            ));
            al_draw_textf(font, al_map_rgb(255, 255, 255), 800, 0, ALLEGRO_ALIGN_RIGHT, "%02ld:%02ld", eta_min, eta_sec);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTRE, "%ld", password);
            al_flip_display();

            ++i;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
