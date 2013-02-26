#ifndef __ONSCREEN_BOUNDARY_SYSTEM_H__
#define __ONSCREEN_BOUNDARY_SYSTEM_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "artemis/EntityProcessingSystem.h"
#include "artemis/ComponentMapper.h"
#include "artemis/Entity.h"
#include "artemis/World.h"

#include "components/GraphicComponent.h"
#include "components/VelocityComponent.h"

using namespace cocos2d;
using namespace artemis;
class GamePlayLayer;
class OnScreenBoundarySystem : public artemis::EntityProcessingSystem {
  ComponentMapper<GraphicComponent> mGraphicMapper;
  CCSize mWinSize;

public:
  OnScreenBoundarySystem( CCSize size);
  virtual void initialize();
  virtual void processEntity(Entity& pE);

};

#endif