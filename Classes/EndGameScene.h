#ifndef __END_GAME_SCENE_H__
#define __END_GAME_SCENE_H__
#include "cocos2d.h"
#include "Database.h"
using namespace cocos2d;

class EndGameScene : public CCLayer
{
public:

  bool init();

  void CreateEntities();
  void moveEntities();

  void createBushAndBoard();

  void createNameField();
  void moveNameField();

  void createHighScoreAndGameOverTitle();
  void moveHighScoreAndGameOver();

  void createResetAndQuitButton();
  void moveResetAndQuitGame();
  
  void SaveGame();

  void setScore(int pValue);
  void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
  CREATE_FUNC(EndGameScene);
private:
  CCSize winSize;

  CCSprite* spriteLeft;
  CCPoint leftPoint;
  CCSprite* spriteRight;	
  CCPoint rightPoint;

  CCSprite* boardSprite;
  CCPoint boardPoint;

  CCTextFieldTTF* nameField;
  CCPoint nameFieldPoint;
  CCLabelTTF* nameTitle;
  CCPoint nameTitlePoint;
  CCLabelTTF* highScoreTitle;
  CCPoint highScoreTitlePoint;
  CCLabelTTF* gameOver;
  CCPoint gameOverPoint;

  CCSprite* resetGame;
  CCPoint resetGamePoint;
  CCSprite* quitGame;
  CCPoint quitGamePoint;


  int mScore;
  int highScore;
  Database* database;
};

#endif

