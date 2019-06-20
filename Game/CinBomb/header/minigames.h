#ifndef MINIGAMES_HPP
#define MINIGAMES_HPP
#endif 
#include <iostream>

class minigames{
protected:
	int trys,place;
public:
	enum class status:int {stoped,started,finished};
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

enum class difficulty {easy,medium,hard};