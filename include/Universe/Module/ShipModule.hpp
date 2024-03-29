#ifndef SHIPMODULE_HPP
#define SHIPMODULE_HPP

#include "Module.hpp"
#include "QuadComponent.hpp"
#include "Health.hpp"


enum class HealthState
{
    Nominal,//the module should work all the way!
    Damaged,//the module is damaged and may not work
    Broken,//the module is severely damaged and almost certainly doesnt work
};


struct ShipModuleData;

class ShipModule : public Module
{
public:
    ShipModule(const ShipModuleData& rData);
    virtual ~ShipModule() = 0;

    virtual void prePhysUpdate();
    virtual void postPhysUpdate();

    bool functioning();//does this module still do its function
    void setHealthState(HealthState newState);
    virtual void setHealthStateHook(HealthState newState);

protected:
    virtual void input(std::string rCommand, sf::Packet rData);
    virtual void pack(sf::Packet& rPacket);
    virtual void unpack(sf::Packet& rPacket);

    Health m_health;
    HealthState m_healthState;
    bool m_functionsDamaged;

private:
    QuadComponent m_baseDecor;
};



struct ShipModuleData : public ModuleData
{
    ShipModuleData() :
        baseDecor(),
        health(),
        initHealthState(HealthState::Nominal),///NOT IN DATA
        functionsDamaged(false)///NOT IN DATA
    {
        baseDecor.layer = GraphicsLayer::ShipModules;
    }

    QuadComponentData baseDecor;
    HealthData health;
    HealthState initHealthState;
    bool functionsDamaged;//does this module still function when damaged?

    virtual Module* generate(b2Body* pBody, PoolCollection stuff) const
    {
        std::cout << FILELINE;
    }
    virtual ModuleData* clone() const
    {
        std::cout << FILELINE;
    }
};



#endif // SHIPMODULE_HPP
