#include "CollisionSystem.h"

#include "components/ReleaseShitComponent.h"
#include "components/HeathComponent.h"
#include "components/DamageComponent.h"
#include "components/ScoreComponent.h"

#include "artemis/World.h"
#include "artemis/Entity.h"

#include "GamePlayScene.h"

/**
 * System constructor define the list of components it interests in
 */
CollisionSystem::CollisionSystem() {
  addComponentType<GraphicComponent>();
  addComponentType<VelocityComponent>();
}

void CollisionSystem::initialize() {
  mGraphicMapper.init(*world);

  mCollisionGroups = new Bag<CollisionGroup*>();
  mCollisionGroups->add(new CollisionGroup(this, "STONE", "BIRD", collideStoneBird));
  mCollisionGroups->add(new CollisionGroup(this, "SHIT", "LION", collideShitLion));
	mCollisionGroups->add(new CollisionGroup(this, "STONE", "SHIT", collideStoneShit));
}

/**
 * Process all entities once per frame
 *
 * @param pBag   the bag of entities being processed
 */
void CollisionSystem::processEntities(ImmutableBag<Entity*> & pBag) {
  for(int i=0; i < mCollisionGroups->getCount(); i++)
    mCollisionGroups->get(i)->checkForCollisions();
}

void CollisionSystem::collideStoneBird( CollisionSystem* pSys, Entity* pStone, Entity* pBird )
{
  DamageComponent* pDCStone = (DamageComponent*)pStone->getComponent<DamageComponent>();
  HeathComponent* pHCBird = (HeathComponent*)pBird->getComponent<HeathComponent>();
  pHCBird->setCurrentValue(pHCBird->getCurrentValue() - pDCStone->getCurrentValue());
  pStone->remove();
  if (pHCBird->Die())
  {
    Entity* mLionEntity = &pSys->world->getTagManager()->getEntity("GUNNER");
    pSys->LionAbsort<ScoreComponent>(mLionEntity,pBird);

    pBird->setGroup("BIRD DEAD");
    pBird->removeComponent<ReleaseShitComponent>();

    GraphicComponent* pGCBird = (GraphicComponent*)pBird->getComponent<GraphicComponent>();
    VelocityComponent* pVCBird = (VelocityComponent*)pBird->getComponent<VelocityComponent>();

    CCActionInterval* fadeOut = CCFadeOut::create(1);
    pGCBird->getGraphicNode()->stopAllActions();

    if (pVCBird->getX() > 0)
    {
      pGCBird->getGraphicNode()->setRotation(90);
    }
    else {
      pGCBird->getGraphicNode()->setRotation(-90);
    }

    pGCBird->getGraphicNode()->runAction(fadeOut);

    pVCBird->setX(0);
    pVCBird->setY(-1);
  }
  pBird->refresh();
}

void CollisionSystem::collideShitLion( CollisionSystem* pSys, Entity* pShit, Entity* pLion )
{
	DamageComponent* pDCShit = (DamageComponent*)pShit->getComponent<DamageComponent>();

  GraphicComponent* pGCShit = (GraphicComponent*)pShit->getComponent<GraphicComponent>();
  pGCShit->getGraphicNode()->setVisible(false);
	pShit->remove();

	HeathComponent* pHCLion = (HeathComponent*)pLion->getComponent<HeathComponent>();
  pHCLion->lossBloob(pDCShit->getCurrentValue());
	
}

void CollisionSystem::collideStoneShit( CollisionSystem* pSys, Entity* pStone, Entity* pShit )
{
  Entity* mLionEntity = &pSys->world->getTagManager()->getEntity("GUNNER");
  pSys->LionAbsort<ScoreComponent>(mLionEntity,pShit);

  pStone->remove();
	pShit->remove();
}

template<class T>
void CollisionSystem::LionAbsort(Entity* pLion, Entity* pItem)
{
  T* itemComponent = (T*)pItem->getComponent<T>();
  if (itemComponent!=NULL)
  {
    T* lionComponent = (T*)pLion->getComponent<T>();
    lionComponent->add(itemComponent->getCurrentValue());
  }
}


/* =================== CollisionGroup ===================== */

CollisionSystem::CollisionGroup::CollisionGroup(CollisionSystem* pParent,
                                                std::string pGroupName1,
                                                std::string pGroupName2,
                                                collisionHandler pHandler) :
mCollisionHandler(pHandler), mParent(pParent) {

  mGroup1 = mParent->world->getGroupManager()->getEntities(pGroupName1);
  mGroup2 = mParent->world->getGroupManager()->getEntities(pGroupName2);
}

/**
 * Check collision between 2 entities
 *
 * @param pE1   entity 1
 * @param pE2   entity 2
 * @return true if 2 entities collided, false otherwise
 */
bool CollisionSystem::CollisionGroup::isCollided(Entity* pE1, Entity* pE2) {
  GraphicComponent* graphic1 = mParent->mGraphicMapper.get(*pE1);
  GraphicComponent* graphic2 = mParent->mGraphicMapper.get(*pE2);
  
  return graphic1->getBoundingBox().intersectsRect(graphic2->getBoundingBox());
}

/**
 * Check for collisions between entities of the two groups
 * and call handler on collision
 */
void CollisionSystem::CollisionGroup::checkForCollisions() {
  for(int i = 0; mGroup1->getCount() > i; i++) {
    for(int j = 0; mGroup2->getCount() > j; j++) {
      Entity* entityA = mGroup1->get(i);
      Entity* entityB = mGroup2->get(j);
      if(isCollided(entityA, entityB)) {
        mCollisionHandler(mParent, entityA, entityB);
        
      }
    }
  }
}

CollisionSystem::CollisionGroup::~CollisionGroup() {

  ((Bag<Entity*>*)mGroup1)->deleteData();
  ((Bag<Entity*>*)mGroup1)->clear();
  ((Bag<Entity*>*)mGroup2)->deleteData();
  ((Bag<Entity*>*)mGroup2)->clear();
  mCollisionHandler = NULL;

}