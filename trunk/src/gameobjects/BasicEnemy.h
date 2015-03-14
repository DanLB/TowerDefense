#ifndef BASIC_ENEMY_H
#define BASIC_ENEMY_H

#include "MovingObject.h"
#include "../path/Path.h"
#include <memory>

class BasicEnemy : public MovingObject
{
private:
    std::shared_ptr<Path> path;
    int health;

protected:
    //Called in Game::gameLoop()
    virtual int updateLogic(sf::Time elapsed);

    virtual int calculateCollisions();

    virtual int outOfBounds();

public:
    BasicEnemy(std::shared_ptr<Path> path, double speed, Type type, int health);
    virtual ~BasicEnemy() = default;

    void changeHealth(int deltaHealth);
};
#endif // BASIC_ENEMY_H