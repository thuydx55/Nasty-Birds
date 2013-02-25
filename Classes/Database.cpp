#include "Database.h"
#include <sstream>

Database::Database(){}
vector<Gamer*> Database::loadHighScore()
{
	int firstScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("score0");
	if (firstScore== 0)
	{
		
		Gamer* one = new Gamer("Alex",100); gamePlayer.push_back(one);
		Gamer* two = new Gamer("Kent",90); gamePlayer.push_back(two);
		Gamer* three = new Gamer("Cody",80); gamePlayer.push_back(three);
		Gamer* four = new Gamer("Stefan",70); gamePlayer.push_back(four);
		Gamer* five = new Gamer("Kevin",20); gamePlayer.push_back(five);
		
		return gamePlayer;
	}else{
		for (int i=0; i<5; i++)
		{
			char name[10]; char score[10];
			sprintf(name,"human%d",i);
			sprintf(score,"score%d",i);
			if (CCUserDefault::sharedUserDefault()->getStringForKey(name).length()==0)
			{
				break;
			}
			Gamer* tmp = new Gamer(CCUserDefault::sharedUserDefault()->getStringForKey(name),CCUserDefault::sharedUserDefault()->getIntegerForKey(score));
			gamePlayer.push_back(tmp);
		}
		return gamePlayer;
	}
}

void Database::saveHighScore(Gamer* player)
{
	bool isPush = false;

	if (gamePlayer.size()==0)
	{
		gamePlayer.push_back(player);
		isPush = true;
	}else{
		for (int i=0; i<gamePlayer.size(); i++)
		{
			if (gamePlayer[i]->score < player->score)
			{
				gamePlayer.insert(gamePlayer.begin()+i,player);
				isPush = true;
				break;
			}
		}
	}

	if (gamePlayer.size()<5 && isPush==false)
	{
		gamePlayer.push_back(player);
	}

	for (int i=0; i<gamePlayer.size(); i++)
	{
		if(i==5)break;
		char name[10], score[10];
		sprintf(name,"human%d",i);
		sprintf(score,"score%d",i);
		CCUserDefault::sharedUserDefault()->setStringForKey(name,gamePlayer[i]->name.c_str());
		CCUserDefault::sharedUserDefault()->setIntegerForKey(score,gamePlayer[i]->score);
	}
	CCUserDefault::sharedUserDefault()->flush();
}