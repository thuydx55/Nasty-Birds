#ifndef __VELOCITY_COMPONENT_H__
#define __VELOCITY_COMPONENT_H__

#include "cocos2d.h"
#include "artemis/Component.h"

using namespace cocos2d;

/**
 * @brief Component to be used for entities who are moveable.
 */
class VelocityComponent : public artemis::Component {
  CC_SYNTHESIZE(float, mX, X);
  CC_SYNTHESIZE(float, mY, Y);
public:
  VelocityComponent(float pX, float pY);
};

#endif