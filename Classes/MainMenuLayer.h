#ifndef __MAINMENU_LAYER_H__
#define __MAINMENU_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
class MainMenuLayer:public CCLayerColor
{
public:

	static CCScene* scene();
	bool init();

	CREATE_FUNC(MainMenuLayer);

private:

	CCSize winSize;

	CCSprite* newGame;
	CCPoint newGamePoint;

	CCSprite* highScore;
	CCPoint highScorePoint;

	CCSprite* howtoPlay;
	CCPoint howtoPlayPoint;

	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	void actionforMenu();

	void actionInvertForNewGame();
	void openNewGame(CCNode* sender);

	void actionInvertForHighScore();
	void openHighScore(CCNode* sender);

	void actionInvertForHowtoPlay();
	void openHowtoPlay(CCNode* sender);

};

#endif
