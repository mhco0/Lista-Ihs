#include<bits/stdc++.h>
#include<allegro5/allegro5.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_image.h>
#include"header/allminigames.h"
#define FPS 60.0
#define HEIGHT 1080.0
#define WIDTH 1920.0
using namespace std;

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout << "cut" << endl;
	minigames * m = new genius();

	

	al_init();
    al_install_keyboard();
	al_init_image_addon();

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE *qu = al_create_event_queue();
	ALLEGRO_DISPLAY *disp = al_create_display(WIDTH,HEIGHT);
    ALLEGRO_FONT *font = al_create_builtin_font();

    ALLEGRO_EVENT ev;

	al_start_timer(timer);
	al_register_event_source(qu, al_get_keyboard_event_source());
	m->start();
	
	ALLEGRO_BITMAP * pau;
	pau = al_load_bitmap("../img/bomb_placeholder0.png");
	

	float w = (float)al_get_bitmap_width(pau);
	float h = (float)al_get_bitmap_height(pau);
	
	
	al_draw_bitmap(pau,(float)(al_get_display_width(disp)/2)-w/2,(float)(al_get_display_height(disp)/2)-h/2,0);
	cout << "penis" << endl;
	al_flip_display();
	
	al_rest(1.0);
		
    while(true){
    	al_wait_for_event(qu, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_HOME)
        	break;

        if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(qu)) {
			m->run();
          	al_flip_display();
        }


    }
	cout << m->get_trys() << endl;

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(qu);


	return 0;
}