#ifndef SHOT_H
#define SHOT_H

#include "MovingObject.h"

class Shot : public MovingObject
{
private:
    int damage;

protected:
    virtual int updateLogic(sf::Time elapsed);

    virtual int calculateCollisions();
    virtual int outOfBounds();

public:
    Shot(Type type, sf::Vector2f position, double rotation, double speed, int damage);
    virtual ~Shot() = default;
};

#endif // SHOT_H