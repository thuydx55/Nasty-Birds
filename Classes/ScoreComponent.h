#ifndef __SCORE_COMPONENT_H__
#define __SCORE_COMPONENT_H__

#include "cocos2d.h"
#include "artemis/Component.h"

using namespace cocos2d;
using namespace artemis;

/**
 * @brief Component to be used in entities who have score
 *
 * Score can be "transfer" to another entity, for example:
 * Bird "transfers" its score to player when it die
 */
class ScoreComponent :public Component
{

  CC_SYNTHESIZE(int, mScore, CurrentValue);

public:
  ScoreComponent(int pScore);

	/**
   * Add a value to current score
   *
   * @param pValue   score value to be added
   */
  void add(int pValue);
};

#endif