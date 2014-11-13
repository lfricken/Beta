#include "Animator.hpp"

#include "Globals.hpp"
#include "AnimAlloc.hpp"

#include "Animation.hpp"

using namespace std;

Animator::Animator(const std::string& setAnimationSheet)
{
    pSet = game.getAnimAlloc().request(setAnimationSheet);
}
Animator::~Animator()
{

}
void Animator::setAnimation(const std::string& setAnim, float duration)
{
    ///DROP WHAT WE ARE DOING, AND RESTART IN THAT STATE
}
sf::Vector2i Animator::getTile() const//what texture tile should we be on? 0,0, 1,0 ect
{
    float elapse = m_timer.getTimeElapsed();//get time elapsed since we first called this
    return sf::Vector2i(0,0);
    ///RETURN WHAT TILE WE SHOULD BE ON
}
const sf::Vector2f& Animator::getTileSize() const
{
    return pSet->tileSize;
}
