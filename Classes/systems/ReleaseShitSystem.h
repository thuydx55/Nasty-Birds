#ifndef __RELEASE_SHIT_SYSTEM__
#define __RELEASE_SHIT_SYSTEM__

#include "cocos2d.h"
#include "artemis/EntityProcessingSystem.h"
#include "artemis/ComponentMapper.h"
#include "artemis/Entity.h"
#include "artemis/World.h"

#include "components/GraphicComponent.h"
#include "components/ReleaseShitComponent.h"

#include "EntityFactory.h"

using namespace cocos2d;
using namespace artemis;

class GamePlayLayer;
class ReleaseShitSystem : public artemis::EntityProcessingSystem {
  ComponentMapper<GraphicComponent> mGraphicMapper;
  CC_SYNTHESIZE(EntityFactory*, mEntityFactory, EntityFactory);

  CCSize mWinSize;
  World *mWorld;
  CCNode* mLayer;
public:
  ReleaseShitSystem(CCNode* pLayer, World* pWorld, CCSize pSize, EntityFactory* pEntityFactory);
  virtual void initialize();
  virtual void processEntity(Entity& pE);

};

#endif