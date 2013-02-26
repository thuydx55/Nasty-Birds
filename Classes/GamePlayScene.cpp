#include "Box2D/Box2D.h"

#include "artemis/SystemManager.h"

#include "Constants.h"

#include "components/OnScreenBoundaryComponent.h"
#include "components/ReleaseShitComponent.h"
#include "components/PhysicalComponent.h"
#include "components/HeathComponent.h"
#include "components/ScoreComponent.h"

#include "GamePlayScene.h"
#include "MainMenuLayer.h"

CCScene* GamePlayLayer::scene()
{
  CCScene* scene = CCScene::create();
  GamePlayLayer* layer = GamePlayLayer::create();
  scene->addChild(layer);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameSceneBackgroundMusic.mp3",true);
  return scene;
}

bool GamePlayLayer::init()
{
  if (!CCLayer::init())
  {
    return false;
  }
  srand(time(NULL));

  mB2World = new b2World(b2Vec2(0,kGravity));
  mWorld = new World();

  lose = false;

  WinSize = CCDirector::sharedDirector()->getWinSize();
  mEntityFactory =  new EntityFactory(mWorld, this, WinSize);

  //create background image
  CCSprite* mBg = CCSprite::create("backgroundGameScene.png");
  mBg->setPosition(ccp(WinSize.width/2, WinSize.height/2));
  this->addChild(mBg,0);

  // Inside Menu
  mMenu = new InsideMenu(WinSize, this);

  // Add Gunner
  mGunner = mEntityFactory->createGunner(WinSize.width/2, WinSize.height*0.3);
  
  // Foreground
  CCSprite* fg = CCSprite::create("foreground.png");
  fg->setAnchorPoint(ccp(0,0));
  addChild(fg);
  fg->setPosition(ccp(0,0));
  

  // Add Lion
  mPlayer = mEntityFactory->createLion(mGunner, WinSize.width/2, WinSize.height*0.31);

  SystemManager *mSystemManager = mWorld->getSystemManager();
  mMovementSystem = (MovementSystem*)mSystemManager->setSystem(new MovementSystem());
  mOnScreenSystem = (OnScreenBoundarySystem*)mSystemManager->setSystem(new OnScreenBoundarySystem(WinSize));
  mReleaseShitSystem = (ReleaseShitSystem*)mSystemManager->setSystem(new ReleaseShitSystem(this,mWorld,WinSize, mEntityFactory));
  mPhysicalSystem = (PhysicalSystem*)mSystemManager->setSystem(new PhysicalSystem(mB2World));
  mCollisionSystem = (CollisionSystem*)mSystemManager->setSystem(new CollisionSystem);
  mPlayerControllerSystem = (PlayerControllerSystem*)mSystemManager->setSystem(new PlayerControllerSystem(mEntityFactory, mB2World, mPlayer));
  mLionRoarSystem = (LionRoarSkillSystem*)mSystemManager->setSystem(new LionRoarSkillSystem(this, WinSize, mEntityFactory));

  mSystemManager->initializeAll();

  this->addChild(mPlayerControllerSystem);

	initUI();

  //update
  scheduleUpdate();

  this->schedule(schedule_selector(GamePlayLayer::addBird),kAddBirdDelay);
  this->schedule(schedule_selector(GamePlayLayer::releaseShit),kReleaseShitDelay);
  
  this->setTouchEnabled(true);
  return true;
}

void GamePlayLayer::initUI()
{
  for (int i=0; i<10;i+=2)
  {
    soap[i] = CCSprite::create("soap.png");
    soap[i+1] = CCSprite::create("soap-die.png");
    soap[i]->setPosition(ccp(WinSize.width - 11*i - soap[i]->getContentSize().width/2 - 3, 
			WinSize.height - soap[i]->getContentSize().height/2 - 5));
    soap[i+1]->setPosition(ccp(WinSize.width - 11*i - soap[i]->getContentSize().width/2-3, 
			WinSize.height - soap[i]->getContentSize().height/2 - 5));
    soap[i]->setVisible(true);
    soap[i+1]->setVisible(false);
    this->addChild(soap[i]);
    this->addChild(soap[i+1]);
  }

  //Score Label
  mScoreLabel = CCLabelTTF::create("Score: 0","Arial",kFontSize);
  mScoreLabel->setPosition(ccp(WinSize.width/2, WinSize.height - mScoreLabel->getContentSize().height/2));
  this->addChild(mScoreLabel);

	// Menu Label
	mMenuLabel = CCLabelTTF::create("MENU", "Arial", kFontSize);
	mMenuLabel->setPosition(ccp(mMenuLabel->getContentSize().width/2+20,
		WinSize.height - mMenuLabel->getContentSize().height/2));
	this->addChild(mMenuLabel);

  //Button Skill
  mSkillButton = CCSprite::create("lionRoarButton.png");
  mSkillShade = CCSprite::create("SkillShade-1.png");
  CCPoint position = ccp(mSkillShade->getContentSize().width, WinSize.height/8);
  mSkillButton->setPosition(position);
  mSkillShade->setPosition(position);
  this->addChild(mSkillButton); this->addChild(mSkillShade);
  useSkill = false;
  turnOn = true;
}

void GamePlayLayer::update(float pDt)
{
  mWorld->setDelta(pDt);
  mWorld->loopStart();

  mMovementSystem->process();
  mCollisionSystem->process();
  mPhysicalSystem->process();
  mLionRoarSystem->process();
  mPlayerControllerSystem->process();
  mOnScreenSystem->process();
  updateScore();
  updateHeath();
  
}

void GamePlayLayer::releaseShit(float pDt)
{
  mReleaseShitSystem->process();
}

void GamePlayLayer::addBird(float pDt)
{
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("birdSound.wav",false);

  CCSprite* bird = CCSprite::create("bird-1.png");


  float maxY = WinSize.height - bird->getContentSize().height/2;
  float minY = 2.5*WinSize.height/3;
  int range = (int)(maxY - minY);
  int positionY = (int) (rand()%range + minY);

  float speed = (rand()%4)/3 + 1.05;


  if (rand()%2==0)
  {
    mEntityFactory->createBird(WinSize.width+bird->getContentSize().width/2, positionY, -speed, false);
  }else
  {
    mEntityFactory->createBird(-bird->getContentSize().width/2 , positionY, speed, true);
  }
}

void GamePlayLayer::updateHeath()
{
  HeathComponent* mHealthComp = (HeathComponent*)mGunner->getComponent<HeathComponent>();
  mHeath = mHealthComp->getCurrentValue();
  if (mHeath!=5){
    for (int i=0; i<10; i+=2){
      if (i>=mHeath*2)
      {
        soap[i]->setVisible(false);
        soap[i+1]->setVisible(true);
      }
    }
  }

  if (mHeath<2 && turnOn)
  {
    mSkillShade->setVisible(false);
    useSkill = true;
  }
  
  if (mHeath<=0)
  {
    lose = true;
    gamOver();
    return;
  }

}

void GamePlayLayer::updateScore()
{
  ScoreComponent* mScoreComp = (ScoreComponent*)mGunner->getComponent<ScoreComponent>();
  mScore = mScoreComp->getCurrentValue();
  mScoreLabel->setString(CCString::createWithFormat("Score: %d",mScore)->getCString());
}

void GamePlayLayer::gamOver()
{
  pauseBird();
  CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
  this->pauseSchedulerAndActions();
  EndGameScene* layer = EndGameScene::create();
  layer->setScore(mScore);
  layer->moveEntities();
  this->addChild(layer, 999);
  mPlayerControllerSystem->setTouchEnabled(false);
}


void GamePlayLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
  CCTouch *touch = (CCTouch *)pTouches->anyObject();
  CCPoint pointTouched = touch->getLocationInView();
  pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);

  if (mSkillButton->boundingBox().containsPoint(pointTouched) && useSkill && turnOn && !lose)
  {
    useSkill = false;
    turnOn  = false;
    mSkillShade->setVisible(true);
    mEntityFactory->createLionRoar();
    pauseBird();
    mPlayerControllerSystem->setTouchEnabled(false);
  }
}

void GamePlayLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = convertTouchToNodeSpace(touch);

	CCRect menuRect = mMenuLabel->boundingBox();

	if (menuRect.containsPoint(location))
	{
		mMenu->actionForMenu();
    pauseBird();
		this->pauseSchedulerAndActions();
    mPlayerControllerSystem->setTouchEnabled(false);
	}

	if (mMenu->getResume()->boundingBox().containsPoint(location))
	{
		mMenu->actionInvertToResume();
    resumeBird();
		this->resumeSchedulerAndActions();
    mPlayerControllerSystem->setTouchEnabled(true);
	}

	if (mMenu->getReset()->boundingBox().containsPoint(location))
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		CCScene* newScene = GamePlayLayer::scene();
		CCDirector::sharedDirector()->replaceScene(newScene);
	}

	if (mMenu->getQuit()->boundingBox().containsPoint(location))
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		CCScene* menuScene = MainMenuLayer::scene();
		CCDirector::sharedDirector()->replaceScene(menuScene);
	}
}

void GamePlayLayer::pauseBird()
{
  ImmutableBag<Entity*>* mBirdBag = mWorld->getGroupManager()->getEntities("BIRD");
  for(int i=0; i<mBirdBag->getCount(); i++)
  {
    Entity* current = mBirdBag->get(i);
    GraphicComponent* GCBird = (GraphicComponent*)current->getComponent<GraphicComponent>();
    GCBird->getGraphicNode()->pauseSchedulerAndActions();
  }
}

void GamePlayLayer::resumeBird()
{
  ImmutableBag<Entity*>* mBirdBag = mWorld->getGroupManager()->getEntities("BIRD");
  for(int i=0; i<mBirdBag->getCount(); i++)
  {
    Entity* current = mBirdBag->get(i);
    GraphicComponent* GCBird = (GraphicComponent*)current->getComponent<GraphicComponent>();
    GCBird->getGraphicNode()->resumeSchedulerAndActions();
  }
}

void GamePlayLayer::showDone( CCNode* sender )
{
  CCSprite* sprite = (CCSprite*)sender;
  sprite->removeFromParentAndCleanup(true);
}

void GamePlayLayer::createEntities(CCNode* sender)
{
  CCSprite* sprite  = (CCSprite*) sender;
  sprite->removeFromParentAndCleanup(true);
  mLionRoarSystem->createEntities(sender);
}

void GamePlayLayer::deleteBirdAndShit( CCNode* sender )
{
  CCSprite* sprite = (CCSprite*)sender;
  sprite->removeFromParentAndCleanup(true);
  mLionRoarSystem->deleteBirdAndShit(sender);
  mPlayerControllerSystem->setTouchEnabled(true);
}
