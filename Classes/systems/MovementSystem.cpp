#include "MovementSystem.h"

/**
 * System constructor define the list of components it interests in
 */
MovementSystem::MovementSystem() {
  addComponentType<GraphicComponent>();
  addComponentType<VelocityComponent>();
}

void MovementSystem::initialize() {
  mGraphicMapper.init(*world);
  mVelocityMapper.init(*world);
}

void MovementSystem::processEntity(Entity& pE) {
  GraphicComponent* grapC = mGraphicMapper.get(pE);
  VelocityComponent* velC = mVelocityMapper.get(pE);

  CCPoint pos = grapC->getGraphicNode()->getPosition();
  pos.x += velC->getX();
  pos.y += velC->getY();
  grapC->getGraphicNode()->setPosition(pos);
}