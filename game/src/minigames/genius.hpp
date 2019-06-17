#ifndef MINIGAMES_HPP
	#include "minigames.hpp"
#endif
#define GENIUS_HPP 1
#include<bits/stdc++.h>
using namespace std;

class genius : public minigames {
public:
	enum class color : int {red = 0,yellow,green,blue};
private:
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
