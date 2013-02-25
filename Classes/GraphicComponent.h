#ifndef __GRAPHIC_COMPONENT_H__
#define __GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "artemis/Component.h"

using namespace cocos2d;

/**
 * @brief Component to be used for entities who are renderable on the screen.
 *
 * It contains a CCNode object which should be manually added to a CCLayer or
 * CCSpriteBatchNode in order to be rendered. CCNode can be a sprite or a
 * particle, or any sub-class of CCNode.
 *
 * CCNode contains data such as position, scale and rotation. Hence,
 * GraphicComponent plays the role of rendering, positioning, transforming.
 */
class GraphicComponent : public artemis::Component {
  CC_SYNTHESIZE(CCNode*, mGraphicNode, GraphicNode);
  // Offset of bounding box
  CC_SYNTHESIZE(CCPoint, mOffsetLeftBottom, OffsetLeftBottom);
  CC_SYNTHESIZE(CCPoint, mOffsetRightTop, OffsetRightTop);
public:
  GraphicComponent();
  GraphicComponent(CCNode* pGraphicNode);
  ~GraphicComponent();
  CCSize getGraphicSize() const;
  // Get bounding box after subtraction offset
  CCRect getBoundingBox();
};

#endif