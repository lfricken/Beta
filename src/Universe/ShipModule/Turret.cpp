#include "Turret.hpp"

#include "Controller.hpp"

Turret::Turret(const TurretData& rData) : ShipModule(rData)
{
    if(not rData.startEmpty)
        setWep(rData.startWep);
    m_lastAngle = 0;
}
Turret::~Turret()
{

}
void Turret::prePhysUpdate()
{
    if(functioning())
    {
        m_lastAngle = atan2(m_lastAim.y-m_fix.getCenter().y, m_lastAim.x-m_fix.getCenter().x);
        m_lastAngle -= m_fix.getAngle();
    }
    m_spWep->prePhysUpdate(m_fix.getCenter(), m_lastAim, m_lastAngle+m_fix.getAngle(), m_fix.getBodyPtr());
    ShipModule::prePhysUpdate();
}
void Turret::postPhysUpdate()
{
    if(functioning())
    {
        m_lastAngle = atan2(m_lastAim.y-m_fix.getCenter().y, m_lastAim.x-m_fix.getCenter().x);
        m_lastAngle -= m_fix.getAngle();
    }
    m_spWep->postPhysUpdate(m_fix.getCenter(), m_lastAim, m_lastAngle+m_fix.getAngle(), m_fix.getBodyPtr());
    ShipModule::postPhysUpdate();
}
void Turret::directive(Directive issue)
{
    switch(issue)
    {
    case Directive::FirePrimary:
        if(m_spWep && functioning())//if we have a weapon
            if(m_spWep->fire(m_pEnergyPool, m_pBallisticPool, m_pMissilePool))//if we successfully fired
            {

            }
        break;
    default:
        break;
    }
}
void Turret::setWep(std::tr1::shared_ptr<const WeaponData> spWep)
{
    m_spWep.reset(spWep->generate());
}
void Turret::removeWep()
{
    m_spWep.reset();
}
void Turret::setAim(const b2Vec2& rTarget)
{
    m_lastAim = rTarget;
}
