#include "Shot.h"
#include "../Game.h"
#include "../util/dlb.h"

using dlb::Log;

Shot::Shot(Type type, sf::Vector2f position, double rotation, double speed, int damage) :
    MovingObject(type, Team::SHOT, position, rotation, speed),
    damage(damage)
{}

int Shot::updateLogic(sf::Time elapsed)
{}

int Shot::calculateCollisions()
{
    ObjectManager& objManager = Game::getObjectManager();
    std::map<int, std::shared_ptr<BasicEnemy>>& enemies = objManager.getEnemies();

    std::shared_ptr<BasicEnemy> closestEnemy = nullptr;
    double closestDistance = std::numeric_limits<double>::max();
    double currentDistance;

    for (std::map<int, std::shared_ptr<BasicEnemy>>::iterator itr = enemies.begin(); itr != enemies.end(); ++itr)
    {
        if (position.x - 12 < itr->second->getPosition().x + 12 &&
            position.x + 12 > itr->second->getPosition().x - 12 &&
            position.y - 12 < itr->second->getPosition().y + 12 &&
            position.y + 12 > itr->second->getPosition().y - 12)
        {
            itr->second->changeHealth(-damage);
            return 1;
        }
    }
    return 0;
}

int Shot::outOfBounds()
{
    return 1;
}