#ifndef _DEFAULTPOSITIONCOMPONENT_H_
#define _DEFAULTPOSITIONCOMPONENT_H_

#include "cocos2d.h"
#include "artemis/Component.h"

using namespace cocos2d;

/**
 * @brief Component to be used to save the default position of player.
 */
class DefaultPositionComponent : public artemis::Component {
  float mX, mY;
public:
  DefaultPositionComponent(float pX, float pY) : mX(pX), mY(pY) {};
  CCPoint getDefaultPosition() {return CCPoint(mX, mY);}
};
#endif