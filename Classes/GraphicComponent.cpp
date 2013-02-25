#include "GraphicComponent.h"


GraphicComponent::GraphicComponent(CCNode* pGraphicNode) : 
  mGraphicNode(pGraphicNode) {
    mOffsetLeftBottom = mOffsetRightTop = CCPointZero;
}

GraphicComponent::GraphicComponent()
{
  mGraphicNode = new CCNode();
  mOffsetLeftBottom = mOffsetRightTop = CCPointZero;
}

GraphicComponent::~GraphicComponent(){
  //CCLog("~GraphicComponent");
  mGraphicNode->removeFromParentAndCleanup(true);
}

/**
 * Get graphic size after scaling
 *
 * @return the size
 */
CCSize GraphicComponent::getGraphicSize() const {
  CCSize size = mGraphicNode->getContentSize();
  size.width *= mGraphicNode->getScaleX();
  size.height *= mGraphicNode->getScaleY();
  
  return size;
}

/**
 * Get bounding box after subtraction offset
 *
 * @return the size
 */
CCRect GraphicComponent::getBoundingBox() {
  CCRect original = mGraphicNode->boundingBox();
  
  return CCRect(original.origin.x + mOffsetLeftBottom.x,
                original.origin.y + mOffsetLeftBottom.y,
                original.size.width - mOffsetLeftBottom.x + mOffsetRightTop.x,
                original.size.height - mOffsetLeftBottom.y + mOffsetRightTop.y);
}