#ifndef TOWER_H
#define TOWER_H

#include <SFML/System.hpp>
#include "BaseObject.h"

class Tower : public BaseObject
{
private:
    long reloadTime;
    Type shotType;
    bool canShoot;
    int range;
    sf::Clock shotTimer;

public:
    Tower(Type type, sf::Vector2f position, long reloadTime, Type shotType, int range);
    virtual ~Tower() = default;

    //Called in Game::gameLoop()
    virtual int update(sf::Time elapsed);
};

#endif // TOWER_H