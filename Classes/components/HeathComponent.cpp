#include "HeathComponent.h"

HeathComponent::HeathComponent( int pHeart ):mHeart(pHeart)
{

}
bool HeathComponent::Die()
{
  return mHeart<=0;
}
