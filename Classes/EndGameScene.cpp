#include "EndGameScene.h"
#include "GamePlayScene.h"
#include "MainMenuLayer.h"
#include "Constants.h"

bool EndGameScene::init( )
{
  winSize = CCDirector::sharedDirector()->getWinSize();
  database = new Database();
  database->loadHighScore();
  if (database->gamePlayer.size()==0)
  {
    highScore=0;
  }else{
    highScore = database->gamePlayer[0]->score;
  }
  CreateEntities();
  this->setTouchEnabled(true);
  return true;
}

void EndGameScene::setScore(int pValue)
{
  mScore = pValue;
}

void EndGameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
  CCTouch *touch = (CCTouch*)(pTouches->anyObject());
  CCPoint pointTouched = touch->getLocationInView();
  pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);

  //handle reset button
  if(resetGame->boundingBox().containsPoint(pointTouched)){
    SaveGame();
    CCScene* reset = GamePlayLayer::scene();
    CCDirector::sharedDirector()->replaceScene(reset);
  }
  
  //handle quit button
  if (quitGame->boundingBox().containsPoint(pointTouched))
  {
    SaveGame();
    CCScene* main_menu = MainMenuLayer::scene();
    CCDirector::sharedDirector()->replaceScene(main_menu);
  }

  //handle when user touch at nameField
  if (nameField->boundingBox().containsPoint(pointTouched))
  {
    nameField->attachWithIME();
  }else{
    nameField->detachWithIME();
  }
}

void EndGameScene::createBushAndBoard()
{
  spriteLeft = CCSprite::create("bushLeft.png");
  leftPoint = ccp( -spriteLeft->getContentSize().width/2, winSize.height/2);
  spriteLeft->setPosition(leftPoint);
  spriteLeft->setScaleY(0.7);
  spriteLeft->setScaleX(0.6);
  this->addChild(spriteLeft,13);

  spriteRight = CCSprite::create("bushRight.png");
  rightPoint = ccp(winSize.width + spriteRight->getContentSize().width/2,winSize.height/2);
  spriteRight->setPosition(rightPoint);
  spriteRight->setScaleY(0.7);
  spriteRight->setScaleX(0.6);
  this->addChild(spriteRight,13);

  boardSprite = CCSprite::create("board.png");
  boardSprite->setPosition(ccp(winSize.width/2, 
		winSize.height + boardSprite->getContentSize().height/2 + 400));
  boardSprite->setScaleY(0.7);
  boardSprite->setScaleX(0.6);
  this->addChild(boardSprite,13);
}

void EndGameScene::createResetAndQuitButton()
{
  resetGame = CCSprite::create("menu_reset.png");
  resetGamePoint = ccp(winSize.width/2 - 80,
		winSize.height/2 + resetGame->getContentSize().height/2 + 640);
  resetGame->setScale(0.5);
  resetGame->setPosition(resetGamePoint);
  //resetGame->setTag(18);
  this->addChild(resetGame,17);

  quitGame = CCSprite::create("menu_quit.png");
  quitGamePoint  = ccp(winSize.width/2 + 80,
		winSize.height/2 + resetGame->getContentSize().height/2+640);
  quitGame->setScale(0.5);
  quitGame->setPosition(quitGamePoint);
  //quitGame->setTag(19);
  this->addChild(quitGame,17);
}

void EndGameScene::moveResetAndQuitGame()
{
  CCFiniteTimeAction* moveReset;
  CCFiniteTimeAction* moveQuit;
  int length = database->gamePlayer.size();
  if (length==0 || length <5)
  {
    moveReset = CCMoveTo::create(
			kEndSceneMoveDuration,ccp(resetGame->getPositionX(), winSize.height/2));
    moveQuit = CCMoveTo::create(
			kEndSceneMoveDuration,ccp(quitGame->getPositionX(),winSize.height/2));
    CCLOG("<5");
  }else
  {

    if (mScore > database->gamePlayer[length-1]->score)
    {
      moveReset = CCMoveTo::create(
				kEndSceneMoveDuration,ccp(resetGame->getPositionX(), winSize.height/2));
      moveQuit = CCMoveTo::create(
				kEndSceneMoveDuration,ccp(quitGame->getPositionX(),winSize.height/2));
      CCLOG("co the luu diem");
    }
    if(mScore <= database->gamePlayer[length-1]->score)
    {
      moveReset = CCMoveTo::create(
				kEndSceneMoveDuration,ccp(resetGame->getPositionX(), winSize.height/2-50));
      moveQuit = CCMoveTo::create(
				kEndSceneMoveDuration,ccp(quitGame->getPositionX(),winSize.height/2-50));
      CCLOG("ko save");
    }
  }
  resetGame->runAction(moveReset);
  quitGame->runAction(moveQuit);
}

void EndGameScene::createHighScoreAndGameOverTitle()
{
  highScoreTitle = CCLabelTTF::create(CCString::createWithFormat("The current high score is: %d",highScore)->getCString(),"font/font1.ttf",19);
  highScoreTitlePoint = ccp(winSize.width/2, winSize.height/2 + highScoreTitle->getContentSize().height/2 + 700);
  highScoreTitle->setPosition(highScoreTitlePoint);
  this->addChild(highScoreTitle,17);

  gameOver = CCLabelTTF::create("GAME OVER ^.^", "font/font1.ttf",35);
  gameOverPoint = ccp(winSize.width/2,winSize.height/2 + gameOver->getContentSize().height/2+700);
  gameOver->setPosition(gameOverPoint);
  this->addChild(gameOver,17);
}

void EndGameScene::moveHighScoreAndGameOver()
{
  CCFiniteTimeAction* moveHighScoreTitle;
  CCFiniteTimeAction* moveGameOverTitle;
  int length = database->gamePlayer.size();
  if (length==0 || length <5)
  {
    moveHighScoreTitle = CCMoveTo::create(
			kEndSceneMoveDuration, ccp(highScoreTitle->getPositionX(),winSize.height/2+82));
    highScoreTitle->runAction(moveHighScoreTitle);

    moveGameOverTitle = CCMoveTo::create(
			kEndSceneMoveDuration, ccp(gameOver->getPositionX(),2*winSize.height/3+57));
    gameOver->runAction(moveGameOverTitle);
  }else
  {

    if (mScore> database->gamePlayer[length-1]->score)
    {
      moveHighScoreTitle = CCMoveTo::create(
				kEndSceneMoveDuration, ccp(highScoreTitle->getPositionX(),winSize.height/2+82));
      highScoreTitle->runAction(moveHighScoreTitle);

      moveGameOverTitle = CCMoveTo::create(
				kEndSceneMoveDuration, ccp(gameOver->getPositionX(),2*winSize.height/3+57));
      gameOver->runAction(moveGameOverTitle);
    }
    if (mScore<=database->gamePlayer[length-1]->score)
    {
      moveHighScoreTitle = CCMoveTo::create(
				kEndSceneMoveDuration, ccp(highScoreTitle->getPositionX(),winSize.height/2));
      highScoreTitle->runAction(moveHighScoreTitle);

      moveGameOverTitle = CCMoveTo::create(
				kEndSceneMoveDuration, ccp(gameOver->getPositionX(),winSize.height/2+50));
      gameOver->runAction(moveGameOverTitle);
    }
  }
}

void EndGameScene::createNameField()
{
  nameField= CCTextFieldTTF::textFieldWithPlaceHolder("Enter your name","font/font1.ttf",19);
  nameFieldPoint = ccp(winSize.width/2 - 11, winSize.height/2 + nameField->getContentSize().height/2 + 700);
  nameField->setString("Anonymous");
  nameField->setAnchorPoint(ccp(0,1));
  nameField->setColor(ccc3(246,255,0));
  nameField->setColorSpaceHolder(ccc3(212,238,236));
  nameField->setPosition(nameFieldPoint);
  nameField->setTag(14);
  this->addChild(nameField,17);

  nameTitle  = CCLabelTTF::create("Your name:", "font/font1.ttf",18);
  nameTitlePoint = ccp(winSize.width/2 - 105, winSize.height/2 + nameTitle->getContentSize().height/2 + 700);
  nameTitle->setAnchorPoint(ccp(0,1));
  nameTitle->setPosition(nameTitlePoint);
  this->addChild(nameTitle,17);
}

void EndGameScene::moveNameField()
{
  CCFiniteTimeAction *moveNameField = CCMoveTo::create(
		kEndSceneMoveDuration,ccp(nameField->getPositionX(), winSize.height/2+60));
  nameField->runAction(moveNameField);

  CCFiniteTimeAction *moveNameTitle = CCMoveTo::create(
		kEndSceneMoveDuration, ccp(nameTitle->getPositionX(),winSize.height/2+60));
  nameTitle->runAction(moveNameTitle);
}

void EndGameScene::CreateEntities()
{
  createBushAndBoard();
  createResetAndQuitButton();
  createNameField();
  createHighScoreAndGameOverTitle();
}

void EndGameScene::moveEntities()
{
  CCFiniteTimeAction *moveLeft = CCMoveTo::create(
		kCloseSceneDuration,ccp(spriteLeft->getContentSize().width/2 - 110,spriteLeft->getPositionY()));
  CCFiniteTimeAction *moveRight = CCMoveTo::create(
		kCloseSceneDuration,ccp(winSize.width-spriteRight->getContentSize().width/2 + 110,spriteRight->getPositionY()));
  spriteLeft->runAction(moveLeft);
  spriteRight->runAction(moveRight);

  moveResetAndQuitGame();

  int length = database->gamePlayer.size();
  if (length==0 || length <5)
  {
    moveNameField();
  }else
  {
    if (mScore> database->gamePlayer[length-1]->score)
    {
      moveNameField();
    }
  }

  moveHighScoreAndGameOver();

  CCFiniteTimeAction *moveBoard  = CCMoveTo::create(
		kEndSceneMoveDuration,ccp(winSize.width/2, winSize.height/2));
  boardSprite->runAction(moveBoard);
}

void EndGameScene::SaveGame()
{
  CCString* test = CCString::createWithFormat("%s",nameField->getString());
  if (test->length()==0)
  {
    return;
  }
  Gamer* player = new Gamer(nameField->getString(),mScore);
  database->saveHighScore(player);
}
