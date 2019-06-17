#ifndef GENIUS_HPP 
	#include "genius.hpp"
#endif
#ifndef MINIGAMES_HPP
	#include "minigames.hpp"
#endif

genius::genius(void):minigames(){
	level = difficulty::easy;
}

void genius::start(void){
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
}

void genius::stop(void){
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
	level = difficulty::easy;
	this->trys++;
}
