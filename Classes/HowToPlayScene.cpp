#include "HowToPlayScene.h"
#include "MainMenuLayer.h"
CCScene* HowToPlayScene::scene()
{
	CCScene* scene = CCScene::create();
	HowToPlayScene* layer = HowToPlayScene::create();
	scene->addChild(layer);
	return scene;
}
bool HowToPlayScene::init()
{
	if (!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
	{
		return false;
	}
	
	winSize = CCDirector::sharedDirector()->getWinSize();
	
	howtoplay = CCSprite::create("howtoplayBackground.png");
	howtoplay->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(howtoplay);

  this->setTouchEnabled(true);

	return true;
}

void HowToPlayScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
  CCTouch *touch = (CCTouch *)pTouches->anyObject();
  CCPoint pointTouched = touch->locationInView();
  pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);

  CCScene* scene = MainMenuLayer::scene();
  CCDirector::sharedDirector()->replaceScene(scene);
}