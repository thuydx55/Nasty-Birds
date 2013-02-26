#include "ScoreComponent.h"


ScoreComponent::ScoreComponent(int pScore):mScore(pScore)
{
}

void ScoreComponent::add(int pValue)
{
  mScore +=pValue;
}
