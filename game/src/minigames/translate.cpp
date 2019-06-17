#include<bits/stdc++.h>
#include "minigames.hpp"
using namespace std;

class translate : protected minigames{
private:
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    string str, criptStr;
    difficulty level;
public:
    translate();
    void setup();
    void next_level();
    void run();
    void start();
    void finish();
    void stop();
};

translate::translate():minigames(){
    this->level = difficulty::easy;
    this->setup();
}

void translate::setup(){
    int sizeCript, shift;
    if(this->level == difficulty::easy){
        sizeCript = 13;
        shift = 1;
    }
    if(this->level == difficulty::medium){
        sizeCript = 19;
        shift = 4;
    }
    if(this->level == difficulty::hard){
        sizeCript = 27;
        shift = 6;
    }
    criptStr.clear();
    random_device dev;
    for(int i = 0; i < sizeCript; i++){
        int aux = (dev() % (alpha.size() - 1));
        criptStr.push_back(alpha[aux]);
    }
    str = criptStr;
    cout << criptStr << endl;
    for(int i = 0; i < sizeCript; i++){
        criptStr[i] += shift;
        if(criptStr[i] > 122) criptStr[i] -= 26;
    }

    cout << criptStr << endl;
}

void translate::next_level(void){
    cout << "A" << endl;
	if(level == difficulty::easy) level = difficulty::medium;
	else if(level == difficulty::medium) level = difficulty::hard;
	else if(level == difficulty::hard) this->finish();
}

void translate::run(){
    string ans;
    this->trys = 1;
    do{
        cin >> ans;
        cout << trys << endl;
        if(ans == str){
            this->next_level();
            this->setup();
        }
        else 
            trys++;
    }while(trys <= 3);
    cout << "perdeu se fodeu" << endl;
    this->stop();
}


void translate::start(){
    this->my_status = minigames::status::started;
}

void translate::stop(){
    this->my_status = minigames::status::stoped;
}

void translate::finish(){
    this->my_status = minigames::status::finished;
}

int main(){
    translate a;
    a.run();
    return 0;
}