#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "BaseObject.h"

class MovingObject : public BaseObject
{
private:
    /**
     * Called after subclasses update logic to calculate their current heading and speed.
     * Uses heading, speed, and position to determine and set the new position
     */
    virtual void moveSelf(sf::Time elapsed);

protected:
    double speed;

    virtual int calculateCollisions() = 0;
    virtual int outOfBounds() = 0;
    virtual int updateLogic(sf::Time elapsed) = 0;

public:
    MovingObject(Type type, Team team, sf::Vector2f position, double heading, double speed);
    virtual ~MovingObject() = default;

    //Called in Game::gameLoop()
    virtual int update(sf::Time elapsed);
};

#endif // MOVINGOBJECT_H