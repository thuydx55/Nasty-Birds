#include "MainMenuLayer.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HowToPlayScene.h"
#include "GamePlayScene.h"
#include "HighScoreLayer.h"
#include "Constants.h"

using namespace cocos2d;

CCScene* MainMenuLayer::scene()
{
	CCScene *scene = CCScene::create();
	MainMenuLayer *main_menu = MainMenuLayer::create();
	scene->addChild(main_menu);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("backgroundMusic.mp3",true);
	return scene;
}

bool MainMenuLayer::init()
{
	if (! CCLayerColor::initWithColor(ccc4(255,255,255,255)))
	{
		return false;
	}
	
	winSize = CCDirector::sharedDirector()->getWinSize();
    
	CCSprite* backgound = CCSprite::create("background.png");
	backgound->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(backgound);

	newGame = CCSprite::create("newgame.png");
	newGame->setTag(1);
	newGame->setScale(kScaleRatio);
	newGamePoint = ccp(winSize.width/2 + kStartPointX,
		winSize.height + newGame->getContentSize().height);
	newGame->setPosition(newGamePoint);
	this->addChild(newGame);

	highScore = CCSprite::create("highscore.png");
	highScore->setTag(2);
	highScore->setScale(kScaleRatio);
	highScorePoint = ccp(winSize.width/2+kStartPointX,
		winSize.height + highScore->getContentSize().height);
	highScore->setPosition(highScorePoint);
	this->addChild(highScore);

	howtoPlay = CCSprite::create("howtoplay.png");
	howtoPlay->setTag(3);
	howtoPlay->setScale(kScaleRatio);
	howtoPlayPoint = ccp(winSize.width/2+kStartPointX,
		winSize.height + highScore->getContentSize().height);
	howtoPlay->setPosition(howtoPlayPoint);
	this->addChild(howtoPlay);

	actionforMenu();
	this->setTouchEnabled(true);
    
    return true;
}

void MainMenuLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)(pTouches->anyObject());
	CCPoint pointTouched = touch->getLocationInView();
	pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);

	CCSprite* newgameTemp = (CCSprite*)this->getChildByTag(1);
	CCRect newgameRect = newgameTemp->boundingBox();
	if (newgameRect.containsPoint(pointTouched))
	{
		actionInvertForNewGame();
	}

	CCSprite* highscoreTemp = (CCSprite*)this->getChildByTag(2);
	CCRect highscoreRect = highscoreTemp->boundingBox();
	if (highscoreRect.containsPoint(pointTouched))
	{
		actionInvertForHighScore();
	}

	CCSprite* howtoplayTemp = (CCSprite*)this->getChildByTag(3);
	CCRect howtoPlayRect = howtoplayTemp->boundingBox();
	if (howtoPlayRect.containsPoint(pointTouched))
	{
		actionInvertForHowtoPlay();
	}
}

void MainMenuLayer::actionforMenu()
{
	CCFiniteTimeAction *moveNewGame = CCMoveTo::create(
		kMenuOpenDuration,ccp(newGamePoint.x, winSize.height/2 + kNewGameOpenPoint));
	newGame->runAction(moveNewGame);

	CCFiniteTimeAction *moveHighScore = CCMoveTo::create(
		kMenuOpenDuration,ccp(highScorePoint.x, winSize.height/2 + kHighScoreOpenPoint));
	highScore->runAction(moveHighScore);

	CCFiniteTimeAction *moveHowtoPlay = CCMoveTo::create(
		kMenuOpenDuration,ccp(highScorePoint.x, winSize.height/2 + kHowToPlayOpenPoint));
	howtoPlay->runAction(moveHowtoPlay);
}

void MainMenuLayer::actionInvertForNewGame()
{
	CCFiniteTimeAction* moveNewGame = CCMoveTo::create(
		kMenuCloseDuration, newGamePoint);
	newGame->runAction(moveNewGame);

	CCFiniteTimeAction* moveHighScore = CCMoveTo::create(
		kMenuCloseDuration, highScorePoint);
	highScore->runAction(moveHighScore);

	CCFiniteTimeAction* moveHowtoPlay = CCMoveTo::create(
		kMenuCloseDuration, howtoPlayPoint);
	CCFiniteTimeAction* moveHowtoPlayDone = CCCallFuncN::create(
		this,callfuncN_selector(MainMenuLayer::openNewGame));
	howtoPlay->runAction(CCSequence::create(moveHowtoPlay,moveHowtoPlayDone,NULL));
}

void MainMenuLayer::openNewGame(CCNode* sender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
  CCScene* scene  = GamePlayLayer::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
}


void MainMenuLayer::actionInvertForHighScore()
{
	CCFiniteTimeAction* moveNewGame = CCMoveTo::create(
		kMenuCloseDuration, newGamePoint);
	newGame->runAction(moveNewGame);

	CCFiniteTimeAction* moveHighScore = CCMoveTo::create(
		kMenuCloseDuration, highScorePoint);
	highScore->runAction(moveHighScore);

	CCFiniteTimeAction* moveHowtoPlay = CCMoveTo::create(
		kMenuCloseDuration, howtoPlayPoint);
	CCFiniteTimeAction* moveHowtoPlayDone = CCCallFuncN::create(
		this,callfuncN_selector(MainMenuLayer::openHighScore));
	howtoPlay->runAction(CCSequence::create(moveHowtoPlay,moveHowtoPlayDone,NULL));
}

void MainMenuLayer::openHighScore(CCNode* sender)
{
	CCScene* newScene = HighScoreLayer::scene();
	CCDirector::sharedDirector()->replaceScene(newScene);
}

void MainMenuLayer::actionInvertForHowtoPlay()
{
	CCFiniteTimeAction* moveNewGame = CCMoveTo::create(
		kMenuCloseDuration, newGamePoint);
	newGame->runAction(moveNewGame);

	CCFiniteTimeAction* moveHighScore = CCMoveTo::create(
		kMenuCloseDuration, highScorePoint);
	highScore->runAction(moveHighScore);

	CCFiniteTimeAction* moveHowtoPlay = CCMoveTo::create(
		kMenuCloseDuration, howtoPlayPoint);
	CCFiniteTimeAction* moveHowtoPlayDone = CCCallFuncN::create(
		this,callfuncN_selector(MainMenuLayer::openHowtoPlay));
	howtoPlay->runAction(CCSequence::create(moveHowtoPlay,moveHowtoPlayDone,NULL));
}

void MainMenuLayer::openHowtoPlay(CCNode* sender)
{
	CCScene* newScene = HowToPlayScene::scene();
	CCDirector::sharedDirector()->replaceScene(newScene);
}