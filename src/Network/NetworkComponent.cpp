#include "NetworkComponent.hpp"

using namespace std;

NetworkComponent::~NetworkComponent()
{
    m_rFactory.free(m_factoryID);
}
bool NetworkComponent::toggleNewData(bool newData)//set new data
{
    m_newData = newData;
}
bool NetworkComponent::hasNewData()//do we have new data
{
    return m_newData;
}
void NetworkComponent::pack(sf::Packet& rPacket)
{
    m_packFunction(rPacket);
}
void NetworkComponent::unpack(sf::Packet& rPacket)
{
    m_unpackFunction(rPacket);
}
