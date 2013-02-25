#ifndef __COLLISION_SYSTEM_H__
#define __COLLISION_SYSTEM_H__

#include "cocos2d.h"
#include "artemis/EntityProcessingSystem.h"
#include "artemis/ComponentMapper.h"
#include "artemis/Entity.h"

#include "GraphicComponent.h"
#include "VelocityComponent.h"

using namespace cocos2d;
using namespace artemis;

/**
   * @brief System use to check and perform collision handling on two groups of entities
   */
class CollisionSystem : public artemis::EntityProcessingSystem {
  /** Define a block for collision handler callback */
  typedef void (*collisionHandler)(CollisionSystem* pSys, Entity* pE1, Entity* pE2);

  /**
   * @brief Check and perform collision handling on two groups of entities
   */
  class CollisionGroup {
    ImmutableBag<Entity*>* mGroup1;
    ImmutableBag<Entity*>* mGroup2;
    collisionHandler mCollisionHandler;
    CollisionSystem* mParent;
    
  public:
    CollisionGroup(CollisionSystem* pParent, std::string pGroupName1,
                   std::string pGroupName2, collisionHandler pHandler);
    virtual ~CollisionGroup();
    
    // Check collision between 2 entities
    bool isCollided(Entity* pE1, Entity* pE2);
    
    // Check for collisions between entities of the two groups
    // call handler on collision
    void checkForCollisions();
  };

  ComponentMapper<GraphicComponent> mGraphicMapper;

  Bag<CollisionGroup*>* mCollisionGroups;

  static void collideStoneBird(CollisionSystem* pSys, Entity* pStone, Entity* pBird);
  static void collideShitLion(CollisionSystem* pSys, Entity* pShit, Entity* pLion);
	static void collideStoneShit(CollisionSystem* pSys, Entity* pStone, Entity* pShit);

  template<class T> void LionAbsort(Entity* pLion, Entity* pItem);

public:
  CollisionSystem();
  virtual void initialize();
  virtual void processEntities(ImmutableBag<Entity*> & pBag);
  virtual void processEntity(Entity &pE) {};
};

#endif