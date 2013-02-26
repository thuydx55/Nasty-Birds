#pragma once
#include "cocos2d.h"
#include "Database.h"

using namespace cocos2d;
using namespace std;

class HighScoreLayer: public CCLayerColor
{
public:
	static CCScene* scene();
	virtual bool init();
	void showTopScore();
  void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	CREATE_FUNC(HighScoreLayer);
private:
	CCSize winSize;
	Database* database;
	vector<Gamer*>player;
	CCLabelTTF* name[5];
	CCLabelTTF* score[5];
};

