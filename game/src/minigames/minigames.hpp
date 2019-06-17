#include<bits/stdc++.h>
using namespace std;

class minigame{
private:
	int trys,place;
public:
	enum class status:int {stoped,started,finished};
	status my_status;
	
	minigame(void);
	virtual void start();
	virtual void finish();
};

minigame::minigame(void){
	this->trys = 0;
	this->place = -1;
	this->my_status = minigame::status::stoped;
}

enum class difficulty {easy,medium,hard};
