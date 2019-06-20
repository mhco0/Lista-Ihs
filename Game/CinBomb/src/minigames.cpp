#ifndef MINIGAMES_HPP
#include "header/minigames.h"
#endif

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
