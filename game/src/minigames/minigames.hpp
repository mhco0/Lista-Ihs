#include<bits/stdc++.h>
using namespace std;


class minigame{
private:
	enum class status:int {stoped,started,finished};

	int trys,place;
	status my_status;
public:
	virtual void start();
	virtual void finish();
};