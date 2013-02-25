#include "PhysicalComponent.h"
PhysicalComponent::PhysicalComponent(b2World* pB2World, float pVecX, float pVecY){
  this->mB2World = pB2World;
  this->mVecX = pVecX;
  this->mVecY = pVecY;
}

PhysicalComponent::~PhysicalComponent() {
  //CCLOG("~physicalcomponent");
  mB2World->DestroyBody(mBody);
}