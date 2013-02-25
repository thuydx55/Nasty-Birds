#ifndef __LIONROAR_SKILL_SYSTEM_H__
#define __LIONROAR_SKILL_SYSTEM_H__

#include "cocos2d.h"
#include "artemis/EntityProcessingSystem.h"
#include "artemis/World.h"
#include "artemis/Entity.h"
#include "artemis/ComponentMapper.h"
#include "LionRoarSkillComponent.h"
#include "EntityFactory.h"

class GamePlayLayer;

using namespace cocos2d;
using namespace artemis;

class LionRoarSkillSystem : public EntityProcessingSystem
{
  ComponentMapper<LionRoarSkillComponent> mLionRoarMapper;
  EntityFactory* mEntityFactory;
public:
  LionRoarSkillSystem(GamePlayLayer* pLayer, CCSize pWinSize, EntityFactory* pEntityFactory);
  virtual void initialize();
  virtual void added(Entity &e);
  virtual void processEntity(Entity &pE);

  void createLionChibi();
  void createEntities(CCNode* sender);
  void actionForEntities();
  void showDone(CCNode* sender);
  void deleteBirdAndShit(CCNode* sender);


private:
  CCSprite* backgroundSkill;
  CCSprite* lionImage;
  CCSprite* lionRoarText;
  CCSprite* lionChibi;

  CCSize winSize;
  GamePlayLayer* mLayer;
  
  // Animation
  CCAnimationCache* mAnimCache;
};

#endif