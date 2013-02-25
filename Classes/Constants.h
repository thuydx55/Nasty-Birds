//
//  Constants.h
//  fucking-bird
//
//  Created by Mark Chu on 9/19/12.
//
//

#ifndef _CONSTANTS_H_ 
#define _CONSTANTS_H_

#define PTM_RATIO 32.0

/*
 *  Animation
 */

#define ANIM_BIRD "birds"

/*
 *  Entity Constants
 */

// Bird constants
#define kBirdHeath 1
#define kBirdScore 10

// Shit constants
#define kShitDamage 1
#define kShitScore 5

// Player constants
#define kPlayerHeath 5
#define kPlayerScore 0

// Stone constants
#define kStoneDamage 1

/*
 *  Gameplay Constants
 */
#define kGravity -4.5
#define kFontSize 18

#define kAddBirdDelay 1.0
#define kReleaseShitDelay 0.8

/*
 *  Menu Constants
 */
#define kScaleRatio 0.6
#define kMenuOpenDuration 0.5
#define kMenuCloseDuration 0.4

#define kStartPointX 100
#define kStartPointY 40

#define kNewGameOpenPoint 80
#define kHighScoreOpenPoint 20
#define kHowToPlayOpenPoint -40

#define kResumeOpenPoint 60
#define kResetOpenPoint 00
#define kQuitOpenPoint -60

/*
 *  End Scene Constants
 */
#define kCloseSceneDuration 2
#define kEndSceneMoveDuration 4

typedef enum {
  kLeftSnake,
  kRightSnake
} SnakePart;

#endif