#include "OnScreenBoundarySystem.h"

#include "components/OnScreenBoundaryComponent.h"

#include "GamePlayScene.h"
/**
 * System constructor define the list of components it interests in
 */
OnScreenBoundarySystem::OnScreenBoundarySystem(CCSize size) {
  addComponentType<GraphicComponent>();
  addComponentType<OnScreenBoundaryComponent>();
  mWinSize = size;
}

void OnScreenBoundarySystem::initialize() {
  mGraphicMapper.init(*world);
}

void OnScreenBoundarySystem::processEntity(Entity& pE) {
  GraphicComponent* grapC = mGraphicMapper.get(pE);

  CCPoint pos = grapC->getGraphicNode()->getPosition();
  if (pos.x > mWinSize.width+30 || pos.x < -30){
    //world->deleteEntity(pE);
    pE.remove();
    //CCLOG("DA XOA NGANG");
  }
  if (pos.y < 0){
    pE.remove();
   // world->deleteEntity(pE);
    //CCLOG("DA XOA DOC");
  }
}
