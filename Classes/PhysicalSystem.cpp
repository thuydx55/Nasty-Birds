#include "PhysicalSystem.h"
#include "GamePlayScene.h"
#include "OnScreenBoundaryComponent.h"
#include "Constants.h"
/**
 * System constructor define the list of components it interests in
 */
PhysicalSystem::PhysicalSystem(b2World* pB2World) : mB2World(pB2World) {
  addComponentType<GraphicComponent>();
  addComponentType<PhysicalComponent>();
}
void PhysicalSystem::added(Entity &e) {
  //CCLOG("add");
  PhysicalComponent* physic  = (PhysicalComponent*)e.getComponent<PhysicalComponent>();
  GraphicComponent* graphic = (GraphicComponent*)e.getComponent<GraphicComponent>();

  CCSprite* sprite = (CCSprite*)graphic->getGraphicNode();

  physic->mBodyDef.type = b2_dynamicBody;
  physic->mBodyDef.userData = sprite;
  physic->mBodyDef.position.Set(sprite->getPositionX()/PTM_RATIO,sprite->getPositionY()/PTM_RATIO);
  physic->mBody = physic->mB2World->CreateBody(&(physic->mBodyDef));
  
  b2PolygonShape mShape;
  mShape.SetAsBox((graphic->getGraphicSize().width-1)/2/PTM_RATIO, (graphic->getGraphicSize().height-1)/2/PTM_RATIO);
  b2FixtureDef mFixture;
  mFixture.shape = &mShape;
  mFixture.density = 0.1f;
  physic->mBody->CreateFixture(&mFixture);
  physic->mBody->SetLinearVelocity(b2Vec2(physic->mVecX/PTM_RATIO,physic->mVecY/PTM_RATIO));

};
void PhysicalSystem::initialize() {
  mGraphicMapper.init(*world);
  mPhysicalMapper.init(*world);
}

void PhysicalSystem::processEntities(ImmutableBag<Entity*> & bag) {

  mB2World->Step(world->getDelta(),20,20);
  for(b2Body *b = mB2World->GetBodyList();b;b=b->GetNext()){
    if(b->GetUserData() != NULL){
      CCSprite *sprite = (CCSprite *)b->GetUserData();
      sprite->setPosition(ccp(b->GetPosition().x*PTM_RATIO,b->GetPosition().y*PTM_RATIO));
    }
  }
}

void PhysicalSystem::processEntity(Entity& pE) {};