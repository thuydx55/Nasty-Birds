#pragma once
#include "cocos2d.h"
#include "fstream"
#include "iostream"
#include "vector"

using namespace cocos2d;
using namespace std;

struct Gamer
{
	string name; int score;
	Gamer(string name, int score){
		this->name = name;
		this->score = score;
	}
};

class Database
{
public:
	Database(void);
	vector<Gamer*> loadHighScore();
	void saveHighScore(Gamer* player);
	vector<Gamer*> gamePlayer;
};

