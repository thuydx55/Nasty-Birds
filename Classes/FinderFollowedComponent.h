#ifndef _FINDERFOLLOWEDCOMPONENT_H_
#define _FINDERFOLLOWEDCOMPONENT_H_

#include "cocos2d.h"
#include "artemis/Entity.h"

#include "GraphicComponent.h"

using namespace cocos2d;
using namespace artemis;

class FinderFollowedComponent : public GraphicComponent {

public:
  FinderFollowedComponent(CCNode* pLeftSprite);
};

#endif