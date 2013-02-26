#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class HowToPlayScene:public CCLayerColor
{
public:
	static CCScene* scene();
	bool init();
  void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	CREATE_FUNC(HowToPlayScene);

private:
	CCSize winSize;
	CCSprite* howtoplay;
};