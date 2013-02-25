#ifndef _SNAKEFOLLOWEDCOMPONENT_H_
#define _SNAKEFOLLOWEDCOMPONENT_H_

#include "cocos2d.h"
#include "artemis/Entity.h"

#include "GraphicComponent.h"

using namespace cocos2d;
using namespace artemis;

class SnakeFollowedComponent : public GraphicComponent {

public:
  SnakeFollowedComponent(CCNode* pLeftSprite);
};

#endif