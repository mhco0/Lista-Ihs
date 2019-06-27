#include <bits/stdc++.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <unistd.h>
#include <fcntl.h>
#define FPS 60.0
#define HEIGHT 1080.0
#define WIDTH 1920.0
using namespace std;


//############################ GLOBAIS ########################
enum OPS {HEXPORT,INPORT,DISPLAY,RED_LEDS,GREEN_LEDS,KEYS,SWITCHES};

ALLEGRO_TIMER *timer = nullptr;
ALLEGRO_EVENT_QUEUE *qu = nullptr;
ALLEGRO_DISPLAY *disp = nullptr;
ALLEGRO_FONT *font = nullptr;
uint32_t number = 0x45604560;//0x30307878;//0x40407979;
uint64_t number2 = 2; // core dump
int dev; 

//##################################################FUNÇÕES##########################################################

bool al_init_everything(void){
	if(!al_init()) return false;
    if(!al_install_keyboard()) return false;
	if(!al_init_image_addon()) return false;
	if(!al_init_font_addon())  return false;
	if(!al_init_ttf_addon()) return false;
	return true;
}

bool al_destroy_everything(void){
	al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(qu);

    return true;
}

void real_write(int debug,int dev,unsigned char * buffer,int opt){
	int ret;
	al_rest(0.1);
	ret = write(dev,buffer,opt);
	ret = write(dev,buffer,opt);
	if( ret != -1) printf("ok -> %d\n",debug);
}

void real_read(int debug,int dev,char *buffer,int opt){
	int ret = read(dev,buffer,opt);
	
	if(ret == -1) cout << "error in genius true read ->"<< debug << endl;
}


//################################CLASSES###################################
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

minigames::minigames(int p){
	this->trys = 0;
	this->place = -1;
	this->my_status = minigames::status::stoped;
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

//--------------------------------------------MINIGAMES-----------------------------------------------

class genius : public minigames {
private:
	ALLEGRO_BITMAP * frames[5];
	difficulty level;
	vector<color> sequal;
public:

	genius(void);
	~genius(void);
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

genius::~genius(void){
	for(int i=0;i<5;i++){
		al_destroy_bitmap(this->frames[i]);
	}
}

void genius::read(bool op){
	if(op){
		bool youdidit = false;
		
		uint64_t busy_wait = 15;
		uint64_t error = 0b111111111111111111;
		uint64_t blank = 0b000000000000000000;
		
		uint64_t fl = 0b10000000;
		uint64_t fm = 0b11000000;
		uint64_t fh = 0b11100000;
		
		if(level ==  difficulty::easy){
			real_write(0,dev,(unsigned char*)&fl,GREEN_LEDS);
		}else if(level == difficulty::medium){
			real_write(0,dev,(unsigned char*)&fm,GREEN_LEDS);
		}else{
			real_write(0,dev,(unsigned char*)&fh,GREEN_LEDS);
		}
		
		for(int i=0;i<(int)sequal.size();i++){
			
			uint64_t pick = 15;
			string ans,input;
			
			do{	
				real_read(0,dev,(char *)&pick,KEYS);
			}while(pick == busy_wait);
			
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
			
			switch(pick){
				case 7:
					input = "red";
					break;
				case 11:
					input = "blue";
					break;
				case 13:
					input = "green";
					break;
				case 14:
					input = "yellow";
					break;
				default:
					input = "";
					cout << "invalid_op" << endl;
					break;
			}
			al_rest(0.5); //because of the break or continue
			cout <<"voce selecionou :" << input << endl;
			if(input != ans){
				real_write(0,dev,(unsigned char*)&error,RED_LEDS);
				al_rest(0.1);
				real_write(0,dev,(unsigned char*)&blank,RED_LEDS);
				cout << "errado" << endl;
				break;
			}else{
				cout << "certo" << endl;
				if(i == ((int)sequal.size())-1) youdidit = true;
				continue;
			}
			

		}
		
		if(youdidit) this->next_level();
		else this->reset();
	}else{
		bool youdidit = false;
		for(int i=0;i<(int)sequal.size();i++){
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
				if(i == ((int)sequal.size())-1) youdidit = true;
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
	this->read(true);
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
	float dispw = al_get_display_width(cur), disph = al_get_display_height(cur);
	
	
	for(int i=0;i<(int)sequal.size();i++){
		switch(sequal[i]){
			case color::red:
				al_draw_bitmap(frames[1],(dispw/2)-w/2,(disph/2)-h/2,0);
				break;
			case color::yellow:
				al_draw_bitmap(frames[2],(dispw/2)-w/2,(disph/2)-h/2,0);
				break;
			case color::green:
				al_draw_bitmap(frames[3],(dispw/2)-w/2,(disph/2)-h/2,0);
				break;
			case color::blue:
				al_draw_bitmap(frames[4],(dispw/2)-w/2,(disph/2)-h/2,0);
				break;
			default:
				cout << "impossible" << endl;
				break;
		}
		
		al_flip_display();
		al_rest(0.7);

		al_draw_bitmap(frames[0],(dispw/2)-w/2,(disph/2)-h/2,0);
		al_flip_display();

		al_rest(0.3);
	}
	
	al_draw_bitmap(frames[0],(dispw/2)-w/2,(disph/2)-h/2,0);
	al_flip_display();
}
//----------------------------------------------GENIUS--------------------------------------------------

class translate : public minigames {
private:
	ALLEGRO_BITMAP * background;
	ALLEGRO_FONT * lcd_font;
	difficulty level;
	int num;
	int lcd_size;
public:

	translate(void);
	~translate(void);
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
	this->lcd_size = 100;
	this->background = al_load_bitmap("../img/bin.png");
	if(this->background == nullptr){
		cout << "error in load translate background" << endl;
	}
	
	this->lcd_font = al_load_ttf_font("../font/DS-DIGI.TTF",lcd_size,0);
	if(this->lcd_font == nullptr){
		cout << "error in load DS-DIGI font" << endl;
	}
}

translate::~translate(void){
	al_destroy_bitmap(this->background);
	al_destroy_font(this->lcd_font);
}

void translate::read(bool op){
	if(op){
		
		uint64_t pick = 0;
		do{
			real_read(0,dev,(char*)&pick,SWITCHES);
			
			al_rest(0.5);
		}while(this->num!=pick);
		
		this->next_level();
	}else{
		int usr_num;
		cin >> usr_num;

		if(usr_num ==  this->num) this->next_level();
		else this->reset();
	}
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
	this->read(true);
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
	float dispw = al_get_display_width(cur), disph = al_get_display_height(cur);
	
	al_draw_bitmap(this->background,(dispw/2)-w/2,(disph/2)-h/2,0);
	al_draw_textf(this->lcd_font,al_map_rgb(255,255,255),(dispw/2)-(float)(this->lcd_size/2),(disph/2)-(float)(this->lcd_size/2),0,"%d",this->num);
	al_flip_display();
}
//------------------------------------------------TRANSLATE---------------------------------------------

class cut_wire : public minigames{
private:
	ALLEGRO_BITMAP * wires[8];
	ALLEGRO_BITMAP * background;
	ALLEGRO_FONT * lcd_font;
	difficulty level;
	string ans;
	map<string,int> bitmask;
	int usr_lcd[4];
	int lcd_size;
public:

	cut_wire(void);
	~cut_wire(void);
	void read(bool op);
	void start(void);
	void finish(void);
	void run(void);
	void stop(void);
	void next_level(void);
	void reset(void);
	void show(void);
};


cut_wire::cut_wire(void){
	this->background = al_load_bitmap("../img/cut_wire_background.png");
	if(this->background == nullptr){
		cout << "error in load cut_wire background" << endl;
	}

	string pre = "../img/";
	string colors[8] = {
						"black",
						"red",
						"green",
						"blue",
						"ocean",
						"yellow",
						"pink",
						"white"
						};
	string suf = "_wire.png";

	this->bitmask["000"] = 0;
	this->bitmask["100"] = 1;
	this->bitmask["010"] = 2;
	this->bitmask["001"] = 3;
	this->bitmask["011"] = 4;
	this->bitmask["110"] = 5;
	this->bitmask["101"] = 6;
	this->bitmask["111"] = 7;

	this->ans = "";
	this->lcd_size = 100;

	this->lcd_font = al_load_ttf_font("../font/DS-DIGI.TTF",this->lcd_size,0);

	for(int i=0;i<8;i++){
		string filename = pre + colors[i] + suf;
		this->wires[i] = al_load_bitmap(filename.c_str());
		if(this->wires[i] ==  nullptr){
			cout << "error in load wire " + to_string(i) << endl;
		}
	}
}

cut_wire::~cut_wire(void){
	al_destroy_bitmap(this->background);
	for(int i=0;i<8;i++){
		al_destroy_bitmap(this->wires[i]);
	}
	al_destroy_font(this->lcd_font);
}

void cut_wire::read(bool op){
	if(op){
		bool got_it = false;
		int usr_ans;
		uint64_t busy_wait = 15;
		uint64_t pick = 15;
		string st = "errou";
			
		do{	
			real_read(0,dev,(char *)&pick,KEYS);
		}while(pick == busy_wait);
		
		switch(pick){
			case 7:
				usr_ans = 0;
				break;
			case 11:
				usr_ans = 1;
				break;
			case 13:
				usr_ans = 2;
				break;
			case 14:
				usr_ans = 3;
				break;
			default:
				usr_ans = -1;
				cout << "invalid_op" << endl;
				break;
		}
		
		for(int i=0;i<4;i++){
			if(this->bitmask[this->ans] == this->usr_lcd[i]){
				if(usr_ans == i){
					got_it = true;
					st = "correto";
				}
			}
		}
		al_rest(0.3);
		cout << st << endl;
		if(got_it) this->next_level();
		else this->reset();
	}else{
		int usr_ans;
		bool got_it = false;

		cin >> usr_ans;
		usr_ans--;

		for(int i=0;i<4;i++){
			if(this->bitmask[this->ans] == this->usr_lcd[i]){
				if(usr_ans == i) got_it = true;
			}
		}

		if(got_it) this->next_level();
		else this->reset();
	}
}

void cut_wire::start(void){
	if(!this->is_finish())
		this->my_status = minigames::status::started;
}

void cut_wire::run(void){
	random_device dev;
	uniform_int_distribution<int> zeroorone(0,1);
	uniform_int_distribution<int> colorrange(0,6);
	vector<int> what_wire = {0,1,2,3,4,5,6,7};
	this->ans = "";

	for(int i=0;i<3;i++){
		if(zeroorone(dev)){
			this->ans += '1';
		}else{
			this->ans += '0';
		}
	}

	swap(what_wire[this->bitmask[this->ans]],what_wire[7]);

	what_wire.pop_back();

	for(int i=0;i<4;i++){
		if(i != 3) this->usr_lcd[i] = what_wire[colorrange(dev)];
		else{
			this->usr_lcd[i] = this->bitmask[this->ans];

			random_shuffle(this->usr_lcd,this->usr_lcd+4);
		}
	}

	this->show();
	this->read(true);
}

void cut_wire::stop(void){
	if(!this->is_finish())
		this->my_status = minigames::status::stoped;
}


void cut_wire::finish(void){
	this->my_status = minigames::status::finished;
}


void cut_wire::next_level(void){
	if(level == difficulty::easy) level = difficulty::medium;
	else if(level == difficulty::medium) level = difficulty::hard;
	else if(level == difficulty::hard) this->finish();
}

void cut_wire::reset(void){
	if(!this->is_finish()){
		level = difficulty::easy;
		this->trys++;
	}
}

void cut_wire::show(void){
	ALLEGRO_DISPLAY * cur = al_get_current_display();
	if(cur == nullptr){
		cout << "error loading current display" << endl;
		return;
	}

	float w = al_get_bitmap_width(this->background),h = al_get_bitmap_height(this->background);
	float dispw = al_get_display_width(cur), disph = al_get_display_height(cur);
	
	al_draw_bitmap(this->background,(dispw/2)-w/2,(disph/2)-h/2,0);
	al_draw_textf(this->lcd_font,al_map_rgb(255,0,0),(dispw/2)-(float)(this->lcd_size)-6,(disph/4)-(float)(this->lcd_size/6)+6,0,"%c",this->ans[0]);
	al_draw_textf(this->lcd_font,al_map_rgb(0,255,0),(dispw/2)-(float)(this->lcd_size)+this->lcd_size-6,(disph/4)-(float)(this->lcd_size/6)+6,0,"%c",this->ans[1]);
	al_draw_textf(this->lcd_font,al_map_rgb(0,0,255),(dispw/2)-(float)(this->lcd_size)+2*this->lcd_size-6,(disph/4)-(float)(this->lcd_size/6)+6,0,"%c",this->ans[2]);

	w = al_get_bitmap_width(this->wires[0]), h = al_get_bitmap_height(this->wires[0]);
	float waux = al_get_bitmap_width(this->background);

	
	for(int i=0;i<4;i++){
		al_draw_bitmap(this->wires[this->usr_lcd[i]],(dispw/2)+this->lcd_size*i-waux/6-18,(disph/2)-h/2+3.0*this->lcd_size/4,0);
	}

	al_flip_display();
}

//------------------------------------------------CUT_WIRE------------------------------------------------

class arrow{
private:
	ALLEGRO_BITMAP * my_arrow; 
public:
	arrow(string s);
	~arrow(void);
};

arrow::arrow(string s){
	this->my_arrow = al_load_bitmap(s.c_str());
	if(!this->my_arrow) cout << "Error in load " << s << endl;
}

arrow::~arrow(void){
	al_destroy_bitmap(this->my_arrow);
}

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	
	if(!al_init_everything()){
		cout << "Error in init allegro memes" << endl;
		return -1;
	}
	
	dev = open("/dev/de2i150_altera", O_RDWR);
	printf("%d\n",dev);

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    timer = al_create_timer(1.0 / FPS);
    qu = al_create_event_queue();
	disp = al_create_display(WIDTH,HEIGHT);
    font = al_create_builtin_font();

    ALLEGRO_EVENT ev;
    ALLEGRO_TIMEOUT t;

    al_clear_to_color(al_map_rgb(0,0,0));
    al_init_timeout(&t,1.0/FPS);
	al_start_timer(timer);
	al_register_event_source(qu, al_get_keyboard_event_source());
	
	minigames* m = new genius();

	//real_write(0,dev,(unsigned char *)&number,RED_LEDS);

	//int ret = read(dev,(char *)&number2,SWITCHES);

	//if(ret == -1) printf("deu erro na leitura\n");

	//printf("%d\n",number2);

	m->start();
	
    while(true){
    	al_wait_for_event_until(qu, &ev,&t);
		
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
        }
    }
	
	cout << m->get_trys() << endl;

    if(!al_destroy_everything()){
		cout << "Error in destroy allegro memes" << endl;
		return -1;
	}

	close(dev);

	return 0;
}
