#include <cmath>
#include "Tower.h"
#include "../Game.h"
#include <limits>
#include "../util/dlb.h"
#include "BaseObject.h"
#include "Shot.h"

#ifndef PI
    #define PI 3.14159265
#endif //PI

Tower::Tower(Type type, sf::Vector2f position, long reloadTime, Type shotType, int range) :
    BaseObject(type, Team::FRIEND, position, 0),
    reloadTime(reloadTime),
    shotType(shotType),
    canShoot(true),
    range(range)
{}

/**
 * Called upon each iteration of the game loop to update the logic for Tower objects
 * Finds the nearest enemy and rotates to face them.
 */
 //TODO Should the algorithm to choose the enemy to target account for power, speed, etc.?
int Tower::update(sf::Time elapsed)
{
    ObjectManager& objManager = Game::getObjectManager();

    std::map<int, std::shared_ptr<BasicEnemy>>& enemies = objManager.getEnemies();

    std::shared_ptr<BasicEnemy> closestEnemy = nullptr;
    double closestDistance = std::numeric_limits<double>::max();
    double currentDistance;

    for (std::map<int, std::shared_ptr<BasicEnemy>>::iterator itr = enemies.begin(); itr != enemies.end(); ++itr)
    {
        currentDistance = dlb::distanceSquared(position, itr->second->getPosition());
        if (currentDistance < closestDistance)
        {
            closestDistance = currentDistance;
            closestEnemy = itr->second;
        }
    }

    //Initialize angle to an invalid angle (10, because should never be more than +-PI rad) to check if angle found
    //Angle in radians
    double angle = (rotation * PI ) / 180.0;

    if (closestEnemy != nullptr)
    {
        angle = atan2(closestEnemy->getPosition().y - position.y, closestEnemy->getPosition().x - position.x);
    }
    //Rotate to face the nearest enemy
    rotation = angle * (180.0 / PI);

    //If closest enemy is in range and tower can shoot, shoot
    if (closestDistance < range * range && canShoot)
    {
        std::shared_ptr<BaseObject> shot(new Shot(BASIC_SHOT, position, rotation + 360, 35, 5));
        objManager.addObject(shot);
        canShoot = false;
        shotTimer.restart();
    }
    else if (!canShoot)
    {
        if (shotTimer.getElapsedTime().asMilliseconds() > reloadTime)
        {
            canShoot = true;
        }
    }
}