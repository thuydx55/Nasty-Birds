#ifndef __PHYSICAL_SYSTEM__
#define __PHYSICAL_SYSTEM__

#include "cocos2d.h"
#include "artemis/EntityProcessingSystem.h"
#include "artemis/ComponentMapper.h"
#include "artemis/Entity.h"
#include "artemis/World.h"
#include "Box2D/Box2D.h"
#include "GraphicComponent.h"
#include "PhysicalComponent.h"

//#define PTM_RATIO 32.0f

using namespace cocos2d;
using namespace artemis;

class PhysicalSystem : public artemis::EntityProcessingSystem {
  ComponentMapper<GraphicComponent> mGraphicMapper;
  ComponentMapper<PhysicalComponent> mPhysicalMapper;
  b2World* mB2World;
public:
  PhysicalSystem(b2World* pB2World);
  virtual void initialize();
  virtual void added(Entity &e);
  virtual void processEntity(Entity& pE);
  virtual void processEntities(ImmutableBag<Entity*> & bag);
};

#endif