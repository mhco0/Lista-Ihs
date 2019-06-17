
#include <bits/stdc++.h>
#include <minigames.hpp>

class genius : protected minigame {
private:
	enum class color : int {red = 0,yellow,green,blue};
	difficulty level;
	vector<color> sequal;
public:
	genius(void);
	void start(void);
	void run(void);
	void stop(void);
	void finish(void);
	void next_level(void);
	void reset(void);
};


genius::genius(void):minigame(){
	level = difficulty::easy;
}

void genius::start(void){
	this->my_status = minigame::status::started;
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

void genius::next_level(void){
	if(level == difficulty::easy) level = difficulty::medium;
	else if(level == difficulty::medium) level = difficulty::hard;
	else if(level == difficulty::hard) this->finish();
}

void genius::reset(void){
	level = difficulty::easy;
}
	
void genius::stop(void){
	this->my_status = minigame::status::stoped;
}

void genius::finish(void){
	this->my_status = minigame::status::finished;
}
