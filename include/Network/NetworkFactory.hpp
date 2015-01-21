#ifndef NETWORKFACTORY_HPP
#define NETWORKFACTORY_HPP
#include "stdafx.hpp"

class NetworkComponent;

class NetworkFactory
{
public:
    NetworkFactory(std::string name);
    virtual ~NetworkFactory();

    int give(NetworkComponent* pComponent);
    void free(int position);//don't adjust the list, just mark the node as null and offer it as a position to future components
    void getData(sf::Packet& rPacket);
    void process(sf::Packet& rPacket);

protected:
private:
    std::vector<NetworkComponent*> m_componentPtrs;//where we store all of them
    std::vector<int> m_freeIndexes;//spots where the ptr is null and we can give a position out!
    int m_lastSendID;

    std::string nname;
};

#endif // NETWORKFACTORY_HPP