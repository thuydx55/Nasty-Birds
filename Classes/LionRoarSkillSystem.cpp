#include "LionRoarSkillSystem.h"
#include "GraphicComponent.h"
#include "ScoreComponent.h"
#include "GamePlayScene.h"

LionRoarSkillSystem::LionRoarSkillSystem(GamePlayLayer* pLayer, CCSize pWInSize, EntityFactory* pEntityFactory)
{
  addComponentType<LionRoarSkillComponent>();
  mEntityFactory = pEntityFactory;
  mLayer = pLayer;
  winSize = pWInSize;
}

void LionRoarSkillSystem::initialize()
{
  mLionRoarMapper.init(*world);
}

void LionRoarSkillSystem::processEntity( Entity &pE ){}

void LionRoarSkillSystem::added( Entity &e )
{
  mLayer->pauseSchedulerAndActions();
  lionChibi = CCSprite::create("lionRoarChibi.png");
  lionChibi->setPosition(ccp(winSize.width/2, lionChibi->getContentSize().height/2));
  mLayer->addChild(lionChibi,20);
  CCFiniteTimeAction *delay = CCDelayTime::create(1);
  CCFiniteTimeAction *callFuncN = CCCallFuncN::create(mLayer,callfuncN_selector(GamePlayLayer::createEntities));
  lionChibi->runAction(CCSequence::create(delay,callFuncN,NULL));
}

void LionRoarSkillSystem::createEntities( CCNode* sender )
{
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("lionRoar.mp3",false);
  //create background for Skill LionRoar
  backgroundSkill = CCSprite::create("lionRoarBackground-1.png");
  backgroundSkill->setPosition(ccp(winSize.width/2, winSize.height/2));
  mLayer->addChild(backgroundSkill,20);

  //create LionImage for Skill LionRoar
  lionImage = CCSprite::create("lionRoarImage.png");
  lionImage->setPosition(ccp(lionImage->getContentSize().width/2, winSize.height/2));
  mLayer->addChild(lionImage,20);

  //create the text "LionRoar" for skill
  lionRoarText = CCSprite::create("lionRoarText.png");
  lionRoarText->setPosition(ccp(winSize.width/2+winSize.width/9.6, winSize.height/2));
  mLayer->addChild(lionRoarText,20);

  actionForEntities();
}

void LionRoarSkillSystem::actionForEntities()
{
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("lionRoar.mp3",false);

  //action for background
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("lionRoarBackground.plist");
  CCArray* frames = new CCArray();
  for (int i=1; i<=3; i++)
  {
    frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("lionRoarBackground-%d.png",i)->getCString()));
  }
  CCAnimation *animation = CCAnimation::create(frames,0.25, 1);
  CCAnimate* animate = CCAnimate::create(animation);
  CCFiniteTimeAction *repeat = CCRepeatForever::create(animate);
  backgroundSkill->runAction(repeat);
  
  //lionImage and  lionRoarText auto hide after 2.8s
  CCFiniteTimeAction *delay = CCDelayTime::create(2.8);
  CCFiniteTimeAction* callFuncN_2 = CCCallFuncN::create(mLayer,callfuncN_selector(GamePlayLayer::showDone));
  lionImage->runAction(CCSequence::create(delay,callFuncN_2,NULL));
  lionRoarText->runAction(CCSequence::create(delay,callFuncN_2,NULL));
  
  // background auto hide after 2.8s  
  CCFiniteTimeAction* callFuncN_1 = CCCallFuncN::create(mLayer,callfuncN_selector(GamePlayLayer::deleteBirdAndShit));
  backgroundSkill->runAction(CCSequence::create(delay,callFuncN_1,NULL));
  
}

void LionRoarSkillSystem::deleteBirdAndShit( CCNode* sender )
{
  //call entity sequence Gunner to calculate score

  Entity* mLion  = &world->getTagManager()->getEntity("GUNNER");

  //delete bird
  ImmutableBag<Entity*>* mBirdEntities = world->getGroupManager()->getEntities("BIRD");
  for(int i=0; i<mBirdEntities->getCount(); i++)
  {
    Entity* current = mBirdEntities->get(i);
    GraphicComponent* GCBird = (GraphicComponent*)current->getComponent<GraphicComponent>();
    mEntityFactory->createBirdDead(GCBird->getGraphicNode()->getPositionX(), GCBird->getGraphicNode()->getPositionY());
    GCBird->getGraphicNode()->setVisible(false);

    ScoreComponent* mLionScore = (ScoreComponent*)mLion->getComponent<ScoreComponent>();
    ScoreComponent* mBirdScore = (ScoreComponent*)current->getComponent<ScoreComponent>();
    mLionScore->add(mBirdScore->getCurrentValue());
    current->remove();
  }

  //delete shit
  ImmutableBag<Entity*>* mShitEntities = world->getGroupManager()->getEntities("SHIT");
  for(int i=0; i<mShitEntities->getCount(); i++)
  {
    Entity* current = mShitEntities->get(i);
    GraphicComponent* GCShit = (GraphicComponent*)current->getComponent<GraphicComponent>();
    GCShit->getGraphicNode()->setVisible(false);

    ScoreComponent* mLionScore = (ScoreComponent*)mLion->getComponent<ScoreComponent>();
    ScoreComponent* mShitScore = (ScoreComponent*)current->getComponent<ScoreComponent>();
    mLionScore->add(mShitScore->getCurrentValue());

    current->remove();
  }
  
  mLayer->resumeSchedulerAndActions();
  mLayer->resumeBird();
}

