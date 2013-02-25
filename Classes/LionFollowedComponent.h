#ifndef _LIONFOLLOWEDCOMPONENT_H_
#define _LIONFOLLOWEDCOMPONENT_H_

#include "cocos2d.h"
#include "artemis/Entity.h"

#include "GraphicComponent.h"

using namespace cocos2d;
using namespace artemis;

/**
 * @brief Lion component.
 */
class LionFollowedComponent : public GraphicComponent {

public:
  LionFollowedComponent(CCNode* pSprite);
};

#endif