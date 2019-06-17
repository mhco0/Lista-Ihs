#ifndef GENIUS_HPP 
	#define GENIUS_HPP 1 
	#include <bits/stdc++.h>
	using namespace std;
#endif

#ifndef MINIGAMES_HPP
	#include <minigames.hpp>
#endif

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
