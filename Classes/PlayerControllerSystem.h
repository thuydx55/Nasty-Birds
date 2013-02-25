#ifndef _TOUCHINPUTSYSTEM_H_
#define _TOUCHINPUTSYSTEM_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "artemis/EntityProcessingSystem.h"
#include "artemis/ComponentMapper.h"
#include "artemis/Entity.h"
#include "artemis/World.h"

#include "EntityFactory.h"

#include "GraphicComponent.h"
#include "DefaultPositionComponent.h"
#include "LionFollowedComponent.h"
#include "SnakeFollowedComponent.h"
#include "FinderFollowedComponent.h"

using namespace cocos2d;
using namespace artemis;

class PlayerControllerSystem : public CCLayer, public EntityProcessingSystem {

  EntityFactory* mEntityFactory;
  b2World* mB2World;
  Entity* mEntity;
  bool mStoneIsTouched, mStoneIsMoved;

  GraphicComponent* mGrapC;
  LionFollowedComponent* mLionC;
  SnakeFollowedComponent* mSnakeC;
  FinderFollowedComponent* mFinderC;
  DefaultPositionComponent* mDefaultPosC;

  void fire(CCPoint pPointTouch, CCPoint pDefaultPoint);

public:
  PlayerControllerSystem(EntityFactory *pEntityFacory, b2World* pB2World, Entity* pE);

  virtual void initialize();
  virtual void processEntity(Entity &e);

  virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
  virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
  virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

  void setSpriteFollowedPosition(CCPoint pPos);
};

#endif