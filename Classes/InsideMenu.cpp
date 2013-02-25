#include "InsideMenu.h"
#include "Constants.h"

InsideMenu::InsideMenu(CCSize size, CCLayer* layer)
{
	this->WinSize = size;
	this->mLayer = layer;

	mResumeGame = CCSprite::create("menu_resume.png");
	mResumeGame->setScale(kScaleRatio);
	mResumePoint = ccp(WinSize.width/2, WinSize.height+kStartPointY);
	mResumeGame->setPosition(mResumePoint);
	mLayer->addChild(mResumeGame,80);

	mResetGame = CCSprite::create("menu_reset.png");
	mResetGame->setScale(kScaleRatio);
	mResetPoint = ccp(WinSize.width/2, WinSize.height+kStartPointY);
	mResetGame->setPosition(mResetPoint);
	mLayer->addChild(mResetGame,80);

	mQuitGame = CCSprite::create("menu_quit.png");
	mQuitGame->setScale(kScaleRatio);
	mQuitPoint = ccp(WinSize.width/2, WinSize.height+kStartPointY);
	mQuitGame->setPosition(mQuitPoint);
	mLayer->addChild(mQuitGame,80);
}

void InsideMenu::actionForMenu()
{
	CCFiniteTimeAction* moveResume = CCMoveTo::create(
		kMenuOpenDuration,ccp(WinSize.width/2,
		WinSize.height/2+kResumeOpenPoint));
	mResumeGame->runAction(moveResume);

	CCFiniteTimeAction* moveReset = CCMoveTo::create(
		kMenuOpenDuration,ccp(WinSize.width/2,
		WinSize.height/2+kResetOpenPoint));
	mResetGame->runAction(moveReset);

	CCFiniteTimeAction* moveQuit = CCMoveTo::create(
		kMenuOpenDuration,ccp(WinSize.width/2,
		WinSize.height/2+kQuitOpenPoint));
	mQuitGame->runAction(moveQuit);
}

void InsideMenu::actionInvertToResume()
{
	CCFiniteTimeAction* moveResume = CCMoveTo::create(
		kMenuCloseDuration,mResumePoint);
	mResumeGame->runAction(moveResume);

	CCFiniteTimeAction* moveReset = CCMoveTo::create(
		kMenuCloseDuration,mResetPoint);
	mResetGame->runAction(moveReset);

	CCFiniteTimeAction* moveQuit = CCMoveTo::create(
		kMenuCloseDuration,mQuitPoint);
	mQuitGame->runAction(moveQuit);
}
