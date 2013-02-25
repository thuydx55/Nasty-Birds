#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "artemis/Entity.h"
#include "artemis/World.h"

#include "MovementSystem.h"
#include "OnScreenBoundarySystem.h"
#include "ReleaseShitSystem.h"
#include "EntityFactory.h"
#include "PhysicalSystem.h"
#include "CollisionSystem.h"
#include "PlayerControllerSystem.h"
#include "LionRoarSkillSystem.h"

#include "EndGameScene.h"
#include "InsideMenu.h"

using namespace cocos2d;

class GamePlayLayer : public CCLayer
{
  EntityFactory* mEntityFactory;
public:
  static CCScene* scene();
  bool init();
  void initUI();
  void update(float pDt);
  void updateHeath();
  void updateScore();
  void releaseShit(float pDt);

  void addBird(float pDt);
  void addStone(float pDt);

  void showDone(CCNode* sender);

  void pauseBird();
  void resumeBird();
  void gamOver();
  void createEntities(CCNode* sender);
  void deleteBirdAndShit(CCNode* sender);
  CREATE_FUNC(GamePlayLayer);
  World* mWorld;
  b2World* mB2World;
private:
  CCSize WinSize;

  int mHeath, mScore;
  CCSprite* soap[10];

  CCSprite* mSkillButton;
  CCSprite* mSkillShade;
  bool useSkill;
  bool turnOn;
  
  bool lose;

	Entity* mGunner;
  Entity* mPlayer;

	InsideMenu* mMenu;

	CCLabelTTF* mScoreLabel;
	CCLabelTTF* mMenuLabel;

  //************************************
  // Method:    ccTouchesBegan
  // FullName:  GamePlayLayer::ccTouchesBegan
  // Access:    private 
  // Returns:   void
  // Qualifier: Handle when user begen touch to sceen
  // Parameter: CCSet * pTouches
  // Parameter: CCEvent * pEvent
  //************************************
  void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	//************************************
	// Method:    ccTouchesEnded
	// FullName:  GamePlayLayer::ccTouchesEnded
	// Access:    private 
	// Returns:   void
	// Qualifier: Handle when user touched out screen
	// Parameter: CCSet * pTouches
	// Parameter: CCEvent * pEvent
	//************************************
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
  

protected:
  MovementSystem* mMovementSystem;
  OnScreenBoundarySystem* mOnScreenSystem;
  ReleaseShitSystem* mReleaseShitSystem;
  CollisionSystem* mCollisionSystem;
  PhysicalSystem* mPhysicalSystem;
  PlayerControllerSystem* mPlayerControllerSystem;
  LionRoarSkillSystem* mLionRoarSystem;
};

#endif
