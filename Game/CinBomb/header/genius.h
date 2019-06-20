#ifndef MINIGAMES_HPP
	#include "minigames.h"
#endif
#ifndef GENIUS_HPP
#define GENIUS_HPP
#endif 
#include<bits/stdc++.h>
#include<allegro5/allegro.h>
using namespace std;

class genius : public minigames {
public:
	enum class color : int {red = 0,yellow,green,blue};
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
