#ifndef __PHYSICAL_COMPONENT_H__
#define __PHYSICAL_COMPONENT_H__

#include "cocos2d.h"
#include "artemis/Component.h"
#include "Box2D/Box2D.h"
using namespace cocos2d;

/**
 * @brief Component to be used in entities who are affected by gravity.
 */
class PhysicalComponent : public artemis::Component {

public:
  PhysicalComponent(b2World* pB2World, float vecX, float vecY);
  virtual ~PhysicalComponent();
  b2Body* mBody;
  b2BodyDef mBodyDef;
  b2World* mB2World;
  float mVecX, mVecY;
};

#endif