#ifndef _INSIDE_MENU_H_ 
#define _INSIDE_MENU_H_

#include "cocos2d.h"

using namespace cocos2d;

class InsideMenu : public CCNode
{
	CC_SYNTHESIZE_READONLY(CCSprite*, mResumeGame, Resume);
	CC_SYNTHESIZE_READONLY(CCSprite*, mResetGame, Reset);
	CC_SYNTHESIZE_READONLY(CCSprite*, mQuitGame, Quit);
public:
	InsideMenu(CCSize size, CCLayer* layer);
	void actionForMenu();
	void actionInvertToResume();
private:
	CCSize WinSize;
	CCLayer* mLayer;

	CCPoint mResumePoint;
	CCPoint mResetPoint;
	CCPoint mQuitPoint;
};

#endif