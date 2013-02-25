#ifndef _ENTITYFACTORY_H_
#define _ENTITYFACTORY_H_

#include "artemis/SystemManager.h"
#include "artemis/World.h"
#include "artemis/Entity.h"

#include "Box2D/Box2D.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace artemis;

class EntityFactory {
  World* mWorld;
  CCNode* mParentNode;
  const CCSize& mWinSize;

  // Animation
  CCAnimationCache* mAnimCache;

public:
  EntityFactory(World* pWorld, CCNode* pParentNode, const CCSize& pWinSize);
  virtual ~EntityFactory();
  
  void initAnimations();

  Entity* createShit(float pX, float pY);
  Entity* createGunner(float pX, float pY);
  Entity* createBird(float pX, float pY, float pSpeed, bool FlipX);
  Entity* createBirdDead(float pX, float pY);
  Entity* createStone(float pX, float pY, b2World* pB2World, float vecX, float vecY);
  Entity* createLionRoar();

  Entity* createLion(Entity* pGunner, float pX, float pY);
  static void setSnakeBodyPosition(CCSprite *sprite, float pX1, float pY1, float pX2, float pY2);
  static CCPoint calcFinderPos( CCPoint pCurrentPoint, CCPoint pDefaultPoint );
};

#endif