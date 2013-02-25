#ifndef __HEATH_COMPONENT_H__
#define __HEATH_COMPONENT_H__

#include "cocos2d.h"
#include "artemis/Component.h"
using namespace cocos2d;

/**
 * @brief Component to be used in entities who have heath.
 */
class HeathComponent : public artemis::Component {
	CC_SYNTHESIZE(int, mHeart, CurrentValue);
public:
	HeathComponent(int pHeart);

  void lossBloob(int pValue){
    mHeart-=pValue;
  }
  bool Die();
};

#endif