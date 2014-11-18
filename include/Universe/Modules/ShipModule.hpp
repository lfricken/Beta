#ifndef SHIPMODULE_HPP
#define SHIPMODULE_HPP

#include "Module.hpp"
#include "QuadComponent.hpp"

struct ShipModuleData;

class ShipModule : public Module
{
public:
    ShipModule(const ShipModuleData& rData);
    virtual ~ShipModule() = 0;

    virtual void prePhysUpdate();
    virtual void postPhysUpdate();

protected:
private:
    QuadComponent m_baseDecor;
};



struct ShipModuleData : public ModuleData
{
    ShipModuleData() :
        baseDecor()
    {
        baseDecor.layer = GraphicsLayer::ShipModules;
    }

    QuadComponentData baseDecor;

    virtual Module* generate(b2Body* pBody, PoolCollection stuff) const
    {
        std::cout << FILELINE;
    }
};



#endif // SHIPMODULE_HPP
