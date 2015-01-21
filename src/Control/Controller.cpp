#include "Controller.hpp"

#include "SlaveLocator.hpp"
#include "Chunk.hpp"

using namespace std;

Controller::Controller(const ControllerData& rData) : m_aim(0,0), m_io(rData.ioComp, &Controller::input, this), m_nw(rData.nwComp, &Controller::pack, &Controller::unpack, this, game.getUniverse().getControllerFactory().getNWFactory())
{
    m_slavePosition = -1;

    if(rData.slaveName != "NOSLAVE")
        setSlave(rData.slaveName);

    for(int i = 0; i<static_cast<int>(Directive::End); ++i)
    {
        m_directives[static_cast<Directive>(i)] = false;
    }
}
Controller::~Controller()
{

}






void Controller::setSlave(const std::string& rSlaveName)
{
    m_slaveName = rSlaveName;
    m_slavePosition = game.getUniverse().getSlaveLocator().findPos(m_slaveName);
}
const std::string& Controller::getSlaveName() const
{
    return m_slaveName;
}



IOComponent& Controller::getIOComp()
{
    return m_io;
}
void Controller::setAim(const b2Vec2& world)//send our aim coordinates
{
    m_aim = world;
    Chunk* temp = game.getUniverse().getSlaveLocator().find(m_slavePosition);
    if(temp != NULL)
        temp->setAim(m_aim);
}
const b2Vec2& Controller::getAim() const
{
    return m_aim;
}
b2Body* Controller::getBodyPtr()//return position
{
    Chunk* temp = game.getUniverse().getSlaveLocator().find(m_slavePosition);
    if(temp != NULL)
        return temp->getBodyPtr();
    else
        return NULL;
}
void Controller::directive(Directive issue)//send command to target
{
    Chunk* temp = game.getUniverse().getSlaveLocator().find(m_slavePosition);
    if(temp != NULL)
        temp->directive(issue);
}
float Controller::get(Request value)//return the requested value
{
    Chunk* temp = game.getUniverse().getSlaveLocator().find(m_slavePosition);
    if(temp != NULL)
        return temp->get(value);
    else
        return 0.f;
}
void Controller::processDirectives()//use our stored directives to send commands
{
    if(m_directives[Directive::Up])
        directive(Directive::Up);
    if(m_directives[Directive::Down])
        directive(Directive::Down);
    if(m_directives[Directive::RollCCW])
        directive(Directive::RollCCW);
    if(m_directives[Directive::RollCW])
        directive(Directive::RollCW);
    if(m_directives[Directive::FirePrimary])
        directive(Directive::FirePrimary);
    if(m_directives[Directive::FireSecondary])
        directive(Directive::FireSecondary);

    if(game.getNwBoss().isClient())//always say there is new data in this to be sent to clients
        m_nw.toggleNewData(true);
}
void Controller::toggleLocal(bool local)
{
    m_local = local;
}
void Controller::updateDirectives(const std::map<Directive, bool>& rDirs)
{
    m_directives = rDirs;
}
void Controller::setPlayerName(const std::string& rPlayerName)
{
    m_playerName = rPlayerName;
}
const std::string& Controller::getPlayerName() const
{
    return m_playerName;
}
NetworkComponent& Controller::getNWComp()
{
    return m_nw;
}
void Controller::pack(sf::Packet& rPacket)
{
    for(int i=0; i<static_cast<int>(Directive::End); ++i)
    {
        rPacket << m_directives[static_cast<Directive>(i)];
    }
}
void Controller::unpack(sf::Packet& rPacket)
{
    if(not m_local)
    {
        bool dir;
        for(int i = 0; i<static_cast<int>(Directive::End); ++i)
        {
            rPacket >> dir;
            m_directives[static_cast<Directive>(i)] = dir;
        }
    }
}
void Controller::input(std::string rCommand, sf::Packet rData)
{
    sf::Packet data(rData);
    if(rCommand == "setPlayerName")
    {
        std::string name;
        data >> name;
        setPlayerName(name);
    }
}
