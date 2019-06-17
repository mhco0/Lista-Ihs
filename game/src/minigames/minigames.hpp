#ifndef MINIGAMES_HPP
	#define MINIGAMES_HPP 1
	#include <iostream>
#endif

class minigames{
protected:
	int trys,place;
public:
	enum class status:int {stoped,started,finished};
	status my_status;
	
	minigames(void);
	minigames(int p);
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

enum class difficulty {easy,medium,hard};
