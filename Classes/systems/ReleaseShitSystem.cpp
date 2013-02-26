#include "ReleaseShitSystem.h"

#include "components/OnScreenBoundaryComponent.h"

#include "GamePlayScene.h"
/**
 * System constructor define the list of components it interests in
 */
ReleaseShitSystem::ReleaseShitSystem(CCNode* pLayer, World* pWorld, CCSize pSize, EntityFactory* pEntityFactory) {
  addComponentType<GraphicComponent>();
  addComponentType<ReleaseShitComponent>();
  mWinSize = pSize;
  mLayer = pLayer;
  mWorld = pWorld;
  mEntityFactory = pEntityFactory;
}

void ReleaseShitSystem::initialize() {
  mGraphicMapper.init(*mWorld);
}

void ReleaseShitSystem::processEntity(Entity& pE) {

  GraphicComponent* grapC = mGraphicMapper.get(pE);

  CCPoint pos = grapC->getGraphicNode()->getPosition();

  //if Bird's position appropriate the condition then release shit at this postion
  if (pos.x > mWinSize.width/3 && pos.x < 2*mWinSize.width/3 && rand()%5==1){
    mEntityFactory->createShit(pos.x, pos.y);
  }
}