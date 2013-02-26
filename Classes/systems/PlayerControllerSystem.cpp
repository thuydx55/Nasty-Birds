#include "PlayerControllerSystem.h"

#include "Constants.h"

PlayerControllerSystem::PlayerControllerSystem(EntityFactory *pEntityFacory, b2World* pB2World, Entity* pE) : 
  mEntityFactory(pEntityFacory), mB2World(pB2World), mEntity(pE)
{
  addComponentType<GraphicComponent>();
  addComponentType<DefaultPositionComponent>();
  addComponentType<LionFollowedComponent>();
  addComponentType<SnakeFollowedComponent>();
  addComponentType<FinderFollowedComponent>();

  setTouchEnabled(true);
  mStoneIsTouched = mStoneIsMoved = false;

  mGrapC = (GraphicComponent*)mEntity->getComponent<GraphicComponent>();
  mLionC = (LionFollowedComponent*)mEntity->getComponent<LionFollowedComponent>();
  mSnakeC = (SnakeFollowedComponent*)mEntity->getComponent<SnakeFollowedComponent>();
  mFinderC = (FinderFollowedComponent*)mEntity->getComponent<FinderFollowedComponent>();
  mDefaultPosC = (DefaultPositionComponent*)mEntity->getComponent<DefaultPositionComponent>();
}


void PlayerControllerSystem::initialize() {}

void PlayerControllerSystem::processEntity( Entity &pE ) {}

void PlayerControllerSystem::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
  CCTouch *touch = (CCTouch*)(pTouches->anyObject());
  CCPoint pointTouched = touch->getLocationInView();
  pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);
  
  if (mGrapC->getBoundingBox().containsPoint(pointTouched))
  {
    mStoneIsTouched = true;
    //mGrapC->getGraphicNode()->setPosition(pointTouched);
  }

  //CCLOG("Touch Began");
}

void PlayerControllerSystem::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent )
{
  CCTouch *touch = (CCTouch*)(pTouches->anyObject());
  CCPoint pointTouched = touch->getLocationInView();
  pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);

  if (mStoneIsTouched && pointTouched.y < mDefaultPosC->getDefaultPosition().y)
  {
    mGrapC->getGraphicNode()->setPosition(pointTouched);
    setSpriteFollowedPosition(pointTouched);
    mStoneIsMoved = true;
  }

  //CCLOG("Touch Move");
}

void PlayerControllerSystem::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
  CCTouch *touch = (CCTouch*)(pTouches->anyObject());
  CCPoint pointTouched = touch->getLocationInView();
  pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);

  CCPoint defaultPos = mDefaultPosC->getDefaultPosition();

  if (mStoneIsMoved){
    fire(pointTouched, defaultPos);
    setSpriteFollowedPosition(defaultPos);
  }
  
  mGrapC->getGraphicNode()->setPosition(defaultPos);

  mStoneIsTouched = mStoneIsMoved = false;

  //CCLOG("Touch End");
}

void PlayerControllerSystem::fire(CCPoint pPointTouch, CCPoint pDefaultPoint) {
  float offX = pPointTouch.x - pDefaultPoint.x;
  float offY = pPointTouch.y - pDefaultPoint.y;

  //float force = 4*sqrt(offX*offX + offY*offY)/PTM_RATIO;

  mEntityFactory->createStone(pPointTouch.x, pPointTouch.y, mB2World, -offX*9, -offY*9);
}

void PlayerControllerSystem::setSpriteFollowedPosition(CCPoint pPos)
{
  mLionC->getGraphicNode()->setPosition(pPos);

  CCSprite* mLeftSnake = (CCSprite*)mSnakeC->getGraphicNode()->getChildByTag(kLeftSnake);
  CCSprite* mRightSnake = (CCSprite*)mSnakeC->getGraphicNode()->getChildByTag(kRightSnake);

  CCPoint mLeftSnakePos = mLeftSnake->getPosition();
  CCPoint mRightSnakePos = mRightSnake->getPosition();

  EntityFactory::setSnakeBodyPosition(mLeftSnake,
    mLeftSnakePos.x, mLeftSnakePos.y, pPos.x, pPos.y );
  EntityFactory::setSnakeBodyPosition(mRightSnake,
    mRightSnakePos.x, mRightSnakePos.y, pPos.x, pPos.y );

  mFinderC->getGraphicNode()->setPosition(EntityFactory::calcFinderPos(pPos, mDefaultPosC->getDefaultPosition()));
}
