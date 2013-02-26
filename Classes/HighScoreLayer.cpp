#include "HighScoreLayer.h"
#include "MainMenuLayer.h"

CCScene* HighScoreLayer::scene()
{
	CCScene* scene = new CCScene();
	HighScoreLayer* highScore = HighScoreLayer::create();
	scene->addChild(highScore);
	return scene;
}

bool HighScoreLayer::init()
{
	if (! CCLayerColor::initWithColor(ccc4(0,0,0,100)))
	{
		return false;
	}

	winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* backgound = CCSprite::create("background.png");
	backgound->setPosition(ccp(winSize.width/2, winSize.height/2));
	//backgound->setScaleY(0.669);
	//backgound->setScaleX(0.6);
	this->addChild(backgound);

	database = new Database();
	player = database->loadHighScore();
	showTopScore();

	CCSprite* board = CCSprite::create("board.png");
	board->setScaleY(0.669);
  board->setScaleX(0.47);
	board->setPosition(ccp(winSize.width/2+130, winSize.height/2));
	this->addChild(board);

  this->setTouchEnabled(true);
	return true;
}

void HighScoreLayer::showTopScore()
{
	if (player.size()==0)
	{
		CCLabelTTF *empty = CCLabelTTF::create("Have no top score!","mvboli.ttf",20);
		empty->setColor(ccc3(237,250,25));
		empty->setPosition(ccp(winSize.width/2+130, winSize.height/2));
		this->addChild(empty,1);
	}else{
		for (int i=0; i<player.size();i++)
		{
			name[i] = CCLabelTTF::create(player[i]->name.c_str(),"font/font1.ttf",20);
			name[i]->setAnchorPoint(ccp(0,1));
			name[i]->setPosition(ccp(winSize.width/2+40, winSize.height/2 +75 - 35*i));
			name[i]->setColor(ccc3(237,250,25));
			this->addChild(name[i],1);

			score[i] = CCLabelTTF::create(CCString::createWithFormat("%d",player[i]->score)->getCString(),"font/font1.ttf",20);
			score[i]->setAnchorPoint(ccp(1,0));
			score[i]->setPosition(ccp(winSize.width - 20,winSize.height/2 + 50 - 35*i));
			score[i]->setColor(ccc3(237,250,25));
			this->addChild(score[i],1);
		}
	}
		
}

void HighScoreLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
  CCTouch *touch = (CCTouch *)pTouches->anyObject();
  CCPoint pointTouched = touch->locationInView();
  pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);

  CCScene* scene = MainMenuLayer::scene();
  CCDirector::sharedDirector()->replaceScene(scene);
}
