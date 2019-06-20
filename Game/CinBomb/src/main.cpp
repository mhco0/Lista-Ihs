#include <bits/stdc++.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#define FPS 60.0
#define HEIGHT 1080.0
#define WIDTH 1920.0
using namespace std;


enum class difficulty {easy,medium,hard};
enum class color : int {red = 1,yellow = 2,green = 3,blue = 4};

class minigames{
protected:
	int trys,place;
public:
	enum class status: int {stoped,started,finished};
	status my_status;
	
	minigames(void);
	minigames(int p);
	int get_trys(void);
	int my_place(void);
	bool is_finish(void);
	virtual void read(bool op) = 0;
	virtual void start(void) = 0;
	virtual void finish(void) = 0;
	virtual void run(void) = 0;
	virtual void stop(void) = 0;
};

minigames::minigames(void){
	this->trys = 0;
	this->place = -1;
	this->my_status = minigames::status::stoped;
}

minigames::minigames(int p):minigames(){
	this->place = p;
}

int minigames::get_trys(void){
	return this->trys;
}

int minigames::my_place(void){
	return this->place;
}

bool minigames::is_finish(void){
	if(this->my_status == minigames::status::finished) return true;
	else return false;
}

class genius : public minigames {
private:
	difficulty level;
	vector<color> sequal;
	ALLEGRO_BITMAP * frames[5];
public:

	genius(void);
	void read(bool op);
	void start(void);
	void run(void);
	void stop(void);
	void finish(void);
	void next_level(void);
	void reset(void);
	void show(void);
};

genius::genius(void):minigames(){
	level = difficulty::easy;
	string pre = "";
	string name = "../img/bomb";
	string suf = ".png";
	for(int i=0;i<5;i++){
		pre = to_string(i);
		string path = name+pre+suf;
		this->frames[i] = al_load_bitmap(path.c_str());
		cout << path.c_str() << endl;
		if(this->frames[i] == nullptr){
			cout << "error in load image" << endl;
		}
	}
	
}

void genius::read(bool op){
	if(op){
		
	}else{
		bool youdidit = false;
		for(int i=0;i<sequal.size();i++){
			string input,ans;
			cin >> input;
			
			switch(sequal[i]){
				case color::red:
					ans = "red";
					break;
				case color::yellow:
					ans = "yellow";
					break;
				case color::green:
					ans = "green";
					break;
				case color::blue:
					ans = "blue";
					break;
				default:
					cout << "impossible" << endl;
					break;
			}
			
			if(input != ans){
				cout << "errado" << endl;
				break;
			}else{
				cout << "certo" << endl;
				if(i == sequal.size()-1) youdidit = true;
				continue;
			}
		}
		
		if(youdidit) this->next_level();
		else this->reset();
	}
}

void genius::start(void){
	if(!this->is_finish())
		this->my_status = minigames::status::started;
}

void genius::run(void){

	random_device dev;
	uniform_int_distribution<int> colorrange(1,4);
	
	if(level == difficulty::easy){	
		sequal.resize(4);
	
		for(int i=0;i<4;i++){
			switch(colorrange(dev)){
				case 1:
					sequal[i] = color::red;
					break;
				case 2:
					sequal[i] = color::yellow;
					break;
				case 3:
					sequal[i] = color::green;
					break;
				case 4:
					sequal[i] = color::blue;
					break;
				default:
					cout << "impossible" << endl;
					break;
			}
		}	
	}else if(level  == difficulty::medium){
		sequal.resize(6);
	
		for(int i=0;i<6;i++){
			switch(colorrange(dev)){
				case 1:
					sequal[i] = color::red;
					break;
				case 2:
					sequal[i] = color::yellow;
					break;
				case 3:
					sequal[i] = color::green;
					break;
				case 4:
					sequal[i] = color::blue;
					break;
				default:
					cout << "impossible" << endl;
					break;
			}
		}
	}else{
		sequal.resize(8);
	
		for(int i=0;i<8;i++){
			switch(colorrange(dev)){
				case 1:
					sequal[i] = color::red;
					break;
				case 2:
					sequal[i] = color::yellow;
					break;
				case 3:
					sequal[i] = color::green;
					break;
				case 4:
					sequal[i] = color::blue;
					break;
				default:
					cout << "impossible" << endl;
					break;
			}
		}
	}
	
	
	this->show();
	this->read(false);
}

void genius::stop(void){
	if(!this->is_finish())
		this->my_status = minigames::status::stoped;
}


void genius::finish(void){
	this->my_status = minigames::status::finished;
}


void genius::next_level(void){
	if(level == difficulty::easy) level = difficulty::medium;
	else if(level == difficulty::medium) level = difficulty::hard;
	else if(level == difficulty::hard) this->finish();
}

void genius::reset(void){
	if(!this->is_finish()){
		level = difficulty::easy;
		this->trys++;
	}
}

void genius::show(void){
	ALLEGRO_DISPLAY * cur = al_get_current_display();
	if(cur == nullptr){
		cout << "error loading current display" << endl;
		return;
	}
	float w = al_get_bitmap_width(frames[0]),h = al_get_bitmap_height(frames[0]);
	
	
	for(int i=0;i<sequal.size();i++){
		switch(sequal[i]){
			case color::red:
				al_draw_bitmap(frames[1],(float)(al_get_display_width(cur)/2)-w/2,(float)(al_get_display_height(cur)/2)-h/2,0);
				break;
			case color::yellow:
				al_draw_bitmap(frames[2],(float)(al_get_display_width(cur)/2)-w/2,(float)(al_get_display_height(cur)/2)-h/2,0);
				break;
			case color::green:
				al_draw_bitmap(frames[3],(float)(al_get_display_width(cur)/2)-w/2,(float)(al_get_display_height(cur)/2)-h/2,0);
				break;
			case color::blue:
				al_draw_bitmap(frames[4],(float)(al_get_display_width(cur)/2)-w/2,(float)(al_get_display_height(cur)/2)-h/2,0);
				break;
			default:
				cout << "impossible" << endl;
				break;
		}
		
		al_flip_display();
		al_rest(0.7);
		al_draw_bitmap(frames[0],(float)(al_get_display_width(cur)/2)-w/2,(float)(al_get_display_height(cur)/2)-h/2,0);
		al_flip_display();
		al_rest(0.3);
	}
	
	al_draw_bitmap(frames[0],(float)(al_get_display_width(cur)/2)-w/2,(float)(al_get_display_height(cur)/2)-h/2,0);
	al_flip_display();
}


class translate : public minigames {
private:
	difficulty level;
	int num;
	int size;
	ALLEGRO_BITMAP * background;
	ALLEGRO_FONT * lcd_font;
public:

	translate(void);
	void read(bool op);
	void start(void);
	void finish(void);
	void run(void);
	void stop(void);
	void reset(void);
	void next_level(void);
	void show(void);
};

translate::translate(void): minigames(){
	this->size = 50;
	this->background = al_load_bitmap("../img/bin.png");
	if(this->background == nullptr){
		cout << "error in load translate background" << endl;
	}
	
	this->lcd_font = al_load_ttf_font("../font/DS-DIGI.TTF",size,0);
	if(this->lcd_font == nullptr){
		cout << "error in load DS-DIGI font" << endl;
	}
	
}

void translate::read(bool op){
	
}

void translate::start(void){
	if(!this->is_finish())
		this->my_status = minigames::status::started;
}

void translate::run(void){
	random_device dev;
	uniform_int_distribution<int> erange(1,100);
	uniform_int_distribution<int> mrange(101,1000);
	uniform_int_distribution<int> hrange(1001,10000);
	
	if(level == difficulty::easy){
		this->num = erange(dev);
	}else if(level == difficulty::medium){
		this->num = mrange(dev);
	}else if(level == difficulty::hard){
		this->num = hrange(dev);
	}	

	this->show();
}

void translate::stop(void){
	if(!this->is_finish())
		this->my_status = minigames::status::stoped;
}


void translate::finish(void){
	this->my_status = minigames::status::finished;
}


void translate::next_level(void){
	if(level == difficulty::easy) level = difficulty::medium;
	else if(level == difficulty::medium) level = difficulty::hard;
	else if(level == difficulty::hard) this->finish();
}

void translate::reset(void){
	if(!this->is_finish()){
		level = difficulty::easy;
		this->trys++;
	}
}

void translate::show(void){
	ALLEGRO_DISPLAY * cur = al_get_current_display();
	if(cur == nullptr){
		cout << "error loading current display" << endl;
		return;
	}
	float w = al_get_bitmap_width(this->background),h = al_get_bitmap_height(this->background);
	
	al_draw_bitmap(this->background,(float)(al_get_display_width(cur)/2)-w/2,(float)(al_get_display_height(cur)/2)-h/2,0);
	al_draw_textf(this->lcd_font,al_map_rgb(255,255,255),(float)(al_get_display_width(cur)/2)-(float)(this->size/2-25),(float)(al_get_display_height(cur)/2)-(float)(this->size/2),ALLEGRO_ALIGN_CENTRE,"%d",this->num);
}

bool al_init_everything(void){
	if(!al_init()) return false;
    if(!al_install_keyboard()) return false;
	if(!al_init_image_addon()) return false;
	if(!al_init_font_addon())  return false;
	if(!al_init_ttf_addon()) return false;
	return true;
}


int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	
	if(!al_init_everything()){
		cout << "Error in init allegro memes" << endl;
		return -1;
	}

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE *qu = al_create_event_queue();
	ALLEGRO_DISPLAY *disp = al_create_display(WIDTH,HEIGHT);
    ALLEGRO_FONT *font = al_create_builtin_font();

    ALLEGRO_EVENT ev;

	al_start_timer(timer);
	al_register_event_source(qu, al_get_keyboard_event_source());
	
	minigames* m = new translate();

	m->start();
	
    while(true){
    	al_wait_for_event(qu, &ev);
		
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			break;
		}
            
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_HOME){
			break;
		}
        	
        if (ev.type == ALLEGRO_EVENT_TIMER || al_is_event_queue_empty(qu)) {
			cout << "inside here" << endl;
			m->run();
			if(m->is_finish()){
				m->stop();
				break;
			}
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
