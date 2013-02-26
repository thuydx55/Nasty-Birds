#include "EntityFactory.h"
#include "Constants.h"

#include "components/GraphicComponent.h"
#include "components/VelocityComponent.h"
#include "components/HeathComponent.h"
#include "components/DamageComponent.h"
#include "components/OnScreenBoundaryComponent.h"
#include "components/PhysicalComponent.h"
#include "components/ReleaseShitComponent.h"
#include "components/DefaultPositionComponent.h"
#include "components/ScoreComponent.h"
#include "components/SnakeFollowedComponent.h"
#include "components/FinderFollowedComponent.h"

#include "GamePlayScene.h"
#include "Constants.h"
#include "math.h"


EntityFactory::EntityFactory( World* pWorld, CCNode* pParentNode, const CCSize& pWinSize ) :
  mWorld(pWorld), mParentNode(pParentNode), mWinSize(pWinSize){
    initAnimations();
}

EntityFactory::~EntityFactory()
{
  
}

void EntityFactory::initAnimations()
{
  mAnimCache = CCAnimationCache::sharedAnimationCache();
  
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bird.plist");
  // Bird
  CCAnimation* birdAnim = CCAnimation::create();
  char fileName[128];
  for(int i = 1; i <= 48; ++i) {
    sprintf (fileName, "bird-%d.png", i);
    birdAnim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName));
  }
  birdAnim->setDelayPerUnit(0.06f);
  mAnimCache->addAnimation(birdAnim, ANIM_BIRD);
  
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("lionRoarBackground.plist");
  // Lion Roar
  CCAnimation* lionRoarAnim = CCAnimation::create();
  for(int i = 1; i <= 3; ++i) {
    sprintf (fileName, "lionRoarBackground-%d.png", i);
    lionRoarAnim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName));
  }
  lionRoarAnim->setDelayPerUnit(0.06f);
  mAnimCache->addAnimation(birdAnim, ANIM_LIONROAR);
}

/**
 * Create and return a bird entity
 *
 * @param   pX            position x
 * @param   pX            position y
 * @return                a reference to the created entity
 */
Entity* EntityFactory::createBird( float pX, float pY, float pSpeed, bool pFlipX ) {
  Entity* e = &mWorld->createEntity();

  CCSprite *sprite = CCSprite::create();
  sprite->cocos2d::CCNode::setPosition(pX, pY);

  CCAnimation* animation = mAnimCache->animationByName(ANIM_BIRD);
  sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
  sprite->setFlipX(pFlipX);

  mParentNode->addChild(sprite);
  e->addComponent(new GraphicComponent(sprite));
  e->addComponent(new VelocityComponent(pSpeed, 0));
  e->addComponent(new ReleaseShitComponent);
  e->addComponent(new OnScreenBoundaryComponent);
	e->addComponent(new HeathComponent(kBirdHeath));
  e->addComponent(new ScoreComponent(kBirdScore));

  e->setGroup("BIRD");
  e->refresh();
  return e;
}

/**
 * Create and return a shit entity
 *
 * @param   pX            position x
 * @param   pX            position y
 * @return                a reference to the created entity
 */
Entity* EntityFactory::createShit( float pX, float pY ) {
  Entity* e = &mWorld->createEntity();

  CCSprite* sprite = CCSprite::create("shit.png");
  sprite->cocos2d::CCNode::setPosition(pX, pY);

  mParentNode->addChild(sprite);

	e->addComponent(new GraphicComponent(sprite));
  e->addComponent(new PhysicalComponent(((GamePlayLayer*)mParentNode)->mB2World,0,0));
  e->addComponent(new OnScreenBoundaryComponent);
	e->addComponent(new DamageComponent(kShitDamage));
  e->addComponent(new ScoreComponent(kShitScore));
	e->setGroup("SHIT");
  e->refresh();
  return e;
}

/**
 * Create and return a player entity
 *
 * @param   pX            position x
 * @param   pX            position y
 * @return                a reference to the created entity
 */
Entity* EntityFactory::createGunner(float pX, float pY) {
  Entity* e = &mWorld->createEntity();

  CCSprite* sprite = CCSprite::create("gun2.png");
  sprite->cocos2d::CCNode::setPosition(pX, pY);

  CCSprite* snakeSprite = CCSprite::create("snake.png");
  snakeSprite->setAnchorPoint(ccp(1, 1));
  snakeSprite->cocos2d::CCNode::setPosition(pX-20, pY-20);
  snakeSprite->setScaleX(0.8); snakeSprite->setScaleY(0.8);

  mParentNode->addChild(sprite);
  mParentNode->addChild(snakeSprite, 10);

	e->addComponent(new GraphicComponent(sprite));
	e->addComponent(new VelocityComponent(0,0));
	e->addComponent(new HeathComponent(kPlayerHeath));
  e->addComponent(new ScoreComponent(kPlayerScore));
  e->setTag("GUNNER");
	mWorld->getGroupManager()->set("LION", *e);

  e->refresh();

  return e;
}

/**
 * Create and return a stone entity
 *
 * @param   pX            position x
 * @param   pX            position y
 * @return                a reference to the created entity
 */
Entity* EntityFactory::createStone(float pX, float pY, b2World* pB2World, float vecX, float vecY) {
  Entity* e = &mWorld->createEntity();

  CCSprite* sprite = CCSprite::create("bomb.png");
  sprite->cocos2d::CCNode::setPosition(pX, pY);

  mParentNode->addChild(sprite);

  e->addComponent(new GraphicComponent(sprite));
  e->addComponent(new PhysicalComponent(pB2World, vecX, vecY));
  e->addComponent(new OnScreenBoundaryComponent);
	e->addComponent(new DamageComponent(kStoneDamage));
  e->setGroup("STONE");
  e->refresh();
  return e;
}

/**
 * Create and return a lion entity
 *
 * @param   pX            position x
 * @param   pX            position y
 * @return                a reference to the created entity
 */
Entity* EntityFactory::createLion(Entity* pGunner, float pX, float pY) {
  GraphicComponent* gunnerGrapC = (GraphicComponent*)pGunner->getComponent<GraphicComponent>();
  
  CCPoint mGunnerPos = gunnerGrapC->getGraphicNode()->getPosition();
  CCSize mGunnerRealSize = gunnerGrapC->getGraphicSize();
  // Get Fixed Point of Left and Right BodySnake
  CCPoint mLeftSnakeFixedPoint = ccp(
    mGunnerPos.x - mGunnerRealSize.width*0.427,
    mGunnerPos.y + mGunnerRealSize.height*0.2);
  CCPoint mRightSnakeFixedPoint = ccp(
    mGunnerPos.x + mGunnerRealSize.width*0.32,
    mGunnerPos.y + mGunnerRealSize.height*0.225);

  // Create Stone Sprite
  CCSprite* mStoneSprite = CCSprite::create("bomb.png");
  mStoneSprite->cocos2d::CCNode::setPosition(pX, pY);
  
  // Create Lion Sprite
  CCSprite* mLionSprite = CCSprite::create("lion.png");
  mLionSprite->setAnchorPoint(ccp(0.71, 1));
  mLionSprite->cocos2d::CCNode::setPosition(pX, pY);

  // Create Finder Sprite
  CCSprite* mFinderSprite = CCSprite::create("finder.png");
  mFinderSprite->setPosition(calcFinderPos(ccp(pX, pY), ccp(pX, pY)));

  // Create Snake Body
  CCSprite* mLeftSnakeSprite = CCSprite::create("snakeBody.png");
  mLeftSnakeSprite->setTag(kLeftSnake);
  setSnakeBodyPosition(mLeftSnakeSprite, mLeftSnakeFixedPoint.x, mLeftSnakeFixedPoint.y, pX, pY);

  CCSprite* mRightSnakeSprite = CCSprite::create("snakeBody.png");
  mRightSnakeSprite->setTag(kRightSnake);
  setSnakeBodyPosition(mRightSnakeSprite, mRightSnakeFixedPoint.x, mRightSnakeFixedPoint.y, pX, pY);

  CCLayer* mSnake = new CCLayer();
  mSnake->addChild(mLeftSnakeSprite);
  mSnake->addChild(mRightSnakeSprite);
  

  // Add all sprite to parent
  mParentNode->addChild(mSnake, 11);
  mParentNode->addChild(mLionSprite, 11);
  mParentNode->addChild(mStoneSprite, 11);
  mParentNode->addChild(mFinderSprite, 11);

  // Add Component to Entity
  Entity* e = &mWorld->createEntity();
  e->addComponent(new GraphicComponent(mStoneSprite));
  e->addComponent(new DefaultPositionComponent(pX, pY));
  e->addComponent(new LionFollowedComponent(mLionSprite));
  e->addComponent(new SnakeFollowedComponent(mSnake));
  e->addComponent(new FinderFollowedComponent(mFinderSprite));

  // Set offset BoundingBox of the Stone
  GraphicComponent* grapC = (GraphicComponent*)e->getComponent<GraphicComponent>();
  grapC->setOffsetLeftBottom(ccp(
    -50, -50));
  grapC->setOffsetRightTop(ccp(
    100, 100));

  e->refresh();
  return e;
}

Entity* EntityFactory::createLionRoar()
{
  Entity *e = &mWorld->createEntity();
  e->addComponent(new LionRoarSkillComponent);
  e->refresh();
  return e;
}

Entity* EntityFactory::createBirdDead( float pX, float pY )
{
  Entity* e = &mWorld->createEntity();

  CCSprite* birdDead = CCSprite::create("fallingBird.png");
  birdDead->setPosition(ccp(pX, pY));
  birdDead->setFlipX(rand()%2);

  CCActionInterval* fadeOut = CCFadeOut::create(1);
  birdDead->runAction(fadeOut);

  mParentNode->addChild(birdDead);

  e->addComponent(new GraphicComponent(birdDead));
  e->addComponent(new VelocityComponent(0,-2));
  e->addComponent(new OnScreenBoundaryComponent);
  e->refresh();

  return e;
}

void EntityFactory::setSnakeBodyPosition(CCSprite *sprite, float pX1, float pY1, float pX2, float pY2) {
  sprite->setAnchorPoint(ccp(0, 0.5));
  sprite->cocos2d::CCNode::setPosition(pX1, pY1);

  float distant = sqrt(pow(pX2-pX1, 2) + pow(pY2-pY1, 2));
  sprite->setScaleX(distant/sprite->getContentSize().width);

  float deltaX = pX1 - pX2;
  float deltaY = pY1 - pY2;

  if (deltaX == 0) {
    if (deltaY > 0) {
      sprite->setRotation(-90);
      return;
    }
    else {
      sprite->setRotation(90);
      return;
    }
  }

  if (deltaY == 0) {
    if (deltaX > 0) {
      sprite->setRotation(-180);
      return;
    }
    else return;
  }

  float degree = atan(deltaY/deltaX) * 180 / M_PI;
  if (deltaX < 0)
    sprite->setRotation(-degree);
  else
    sprite->setRotation(180-degree);
}

CCPoint EntityFactory::calcFinderPos( CCPoint pCurrentPoint, CCPoint pDefaultPoint )
{
#define RATIO 5

  float deltaX = pCurrentPoint.x - pDefaultPoint.x;
  float deltaY = pCurrentPoint.y - pDefaultPoint.y;

  return ccp(pDefaultPoint.x - RATIO*deltaX,
    pDefaultPoint.y - RATIO*deltaY+20);
}
