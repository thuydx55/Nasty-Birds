#ifndef __MOVEMENT_SYSTEM_H__
#define __MOVEMENT_SYSTEM_H__

#include "cocos2d.h"
#include "artemis/EntityProcessingSystem.h"
#include "artemis/ComponentMapper.h"
#include "artemis/Entity.h"

#include "components/GraphicComponent.h"
#include "components/VelocityComponent.h"

using namespace cocos2d;
using namespace artemis;

class MovementSystem : public artemis::EntityProcessingSystem {
  ComponentMapper<GraphicComponent> mGraphicMapper;
  ComponentMapper<VelocityComponent> mVelocityMapper;

public:
  MovementSystem();
  virtual void initialize();
  virtual void processEntity(Entity& pE);

};

#endif