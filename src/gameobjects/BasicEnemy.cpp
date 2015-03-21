#include "BasicEnemy.h"
#include "../Game.h"
#include "../util/dlb.h"

#ifndef PI
    #define PI 3.14159265
#endif // PI

BasicEnemy::BasicEnemy(std::shared_ptr<Path> path, double speed, Type type, int health) :
    MovingObject(type, Team::ENEMY, path->getPosition(), 0, speed),
    path(path),
    health(health)
{}

int BasicEnemy::updateLogic(sf::Time elapsed)
{
    if (health <=0)
    {
        //TODO Set Score / Points
        return 1;
    }

    //If we're at the next path
    if (std::abs(position.x - path->getPosition().x) < 1 && std::abs(position.y - path->getPosition().y) < 1)
    {
        if (path->end()) {
            return 2;
        }

        path = path->getNext();

        //we're at the end
        if (path == nullptr)
            return 1;

        double angle = atan2(path->getPosition().y - position.y, path->getPosition().x - position.x);

        rotation = angle * (180.0 / PI);
    }
    return 0;
}

//No collisions checked here
int BasicEnemy::calculateCollisions()
{
    return 0;
}

//Since start out of bounds don't want to delete. Should always follow path so should be okay
int BasicEnemy::outOfBounds()
{
    return 0;
}

void BasicEnemy::changeHealth(int deltaHealth)
{
    health += deltaHealth;
    Game::getLogger().log(dlb::Log(dlb::Log::Level::INFO, "Enemy #" + dlb::toString<int>(getId()) + " - Health = " + dlb::toString<int>(health)));
}