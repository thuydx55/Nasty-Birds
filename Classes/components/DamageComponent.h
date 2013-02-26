#ifndef __DAMAGE_COMPONENT_H__
#define __DAMAGE_COMPONENT_H__

#include "cocos2d.h"
#include "artemis/Component.h"

using namespace cocos2d;

/**
 * @brief Component to be used for entities who can damage others.
 */
class DamageComponent : public artemis::Component {
	CC_SYNTHESIZE(int, mDamage, CurrentValue);
public:
	DamageComponent(int pDamage);
};

#endif