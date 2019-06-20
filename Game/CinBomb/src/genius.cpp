#ifndef GENIUS_HPP 
#include "header/genius.h"
#endif

genius::genius(void):minigames(){
	level = difficulty::easy;
	string pre = "";
	string name = "img/bomb_placeholder";
	string suf = ".png";
	for(int i=0;i<5;i++){
		pre = to_string(i);
		string path = name+pre+suf;
		this->frames[i] = al_load_bitmap(path.c_str());
		cout << path.c_str() << endl;
		if(this->frames[i] == nullptr) cout << "pau" << endl;
	}
}

void genius::read(bool op){
	if(op){
		
	}else{
		bool youdidit = false;
		for(int i=0;i<sequal.size();i++){
			int input;
			cin >> input;
			if(input != static_cast<int>(sequal[i])){
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
	uniform_int_distribution<int> colorrange(0,3);
	
	if(level == difficulty::easy){	
		sequal.resize(4);
	
		for(int i=0;i<4;i++){
			color att = static_cast<genius::color>(colorrange(dev));
			sequal[i] = att;
		}	
	}else if(level  == difficulty::medium){
		sequal.resize(6);
	
		for(int i=0;i<6;i++){
			color att = static_cast<genius::color>(colorrange(dev));
			sequal[i] = att;
		}
	}else{
		sequal.resize(8);
	
		for(int i=0;i<8;i++){
			color att = static_cast<genius::color>(colorrange(dev));
			sequal[i] = att;
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
	float w,h;
	
	for(int i=0;i<sequal.size();i++){
		w = (float)al_get_bitmap_width(frames[(int)sequal[i]]);
		h = (float)al_get_bitmap_height(frames[(int)sequal[i]]);
		al_draw_bitmap(frames[(int)sequal[i]],(float)(al_get_display_width(cur)/2)-w/2,(float)(al_get_display_height(cur)/2)-h/2,0);
		al_flip_display();
		al_rest(0.3);
	}
	
	al_draw_bitmap(frames[(int)sequal[4]],(float)(al_get_display_width(cur)/2)-w/2,(float)(al_get_display_height(cur)/2)-h/2,0);
	al_flip_display();
}