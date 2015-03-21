#include "ObjectManager.h"
#include "../Game.h"
#include "../util/dlb.h"

/**
 * Constructor. No variables are instantiated in this class
 */
ObjectManager::ObjectManager()
{
    path = nullptr;
}

/**
 * Free memory for all objects.
 */
ObjectManager::~ObjectManager()
{
    for (std::map<int, std::shared_ptr<BaseObject>>::iterator itr = objects.begin(); itr != objects.end(); ++itr)
    {
        itr->second.reset();
    }
    objects.clear();
    friends.clear();
    enemies.clear();
}

/**
 * Adds an object to the map. Gets the key from the object passed in.

 * \param obj -> pointer to the object to be added to the map.
 */
void ObjectManager::addObject(std::shared_ptr<BaseObject> obj)
{
    objects.insert(std::pair<int, std::shared_ptr<BaseObject>>(obj->getId(), obj));
}

void ObjectManager::addEnemy(std::shared_ptr<BasicEnemy> enemy)
{
    objects.insert(std::pair<int, std::shared_ptr<BaseObject>>(enemy->getId(), enemy));
    enemies.insert(std::pair<int, std::shared_ptr<BasicEnemy>>(enemy->getId(), enemy));
}

void ObjectManager::addTower(std::shared_ptr<Tower> tower)
{
    objects.insert(std::pair<int, std::shared_ptr<BaseObject>>(tower->getId(), tower));
    friends.insert(std::pair<int, std::shared_ptr<Tower>>(tower->getId(), tower));
}
/**
 * Retrieves the specified object from the map.
 *
 * \return pointer to the object with the given key. Returns nullptr if object not found
 */
std::shared_ptr<BaseObject> ObjectManager::getObject(int key)
{
    std::map<int, std::shared_ptr<BaseObject>>::const_iterator result = objects.find(key);
    if (result == objects.end())
        return nullptr;

    return result->second;
}

/**
 * Frees memory for specified object and removes it from the map.
 *
 * \param key of the object to be removed.
 */
void ObjectManager::removeObject(int key)
{
    if (enemies.find(key) != enemies.end())
    {
        enemies.erase(key);
    }
    if (friends.find(key) != friends.end())
    {
        friends.erase(key);
    }
    std::map<int, std::shared_ptr<BaseObject>>::iterator result = objects.find(key);
    if (result != objects.end())
    {
        result->second.reset();
        objects.erase(key);
    }
}

/**
 * Frees memory for all objects in the map and then clears the map.
 * This function is useful for resetting the game and restarts.
 */
void ObjectManager::clearObjectManager()
{
    for (std::map<int, std::shared_ptr<BaseObject>>::iterator itr = objects.begin(); itr != objects.end(); ++itr)
    {
        itr->second.reset();
    }
    objects.clear();
    enemies.clear();
    friends.clear();
}

/**
 * Updates all objects in the map. Calls each object's update()
 *
 * \param elapsed -> Time since last update. This regulates movement of each object
 */
void ObjectManager::updateAll(sf::Time elapsed)
{
    std::vector<int> toDelete;
    for (std::map<int, std::shared_ptr<BaseObject>>::iterator itr = objects.begin(); itr != objects.end(); ++itr)
    {
        int returnCode = itr->second->update(elapsed);

        switch (returnCode) {
            case 0:
                break;
            case 1:
                toDelete.push_back(itr->second->getId());
                break;
            case 2:
                toDelete.push_back(itr->second->getId());
                Game::getLogger().log(dlb::Log(dlb::Log::Level::INFO, "You Lose"));
                break;
            default:
                Game::getLogger().log(dlb::Log(dlb::Log::WARN, "Invalid update return " + dlb::toString(returnCode) + " from " + itr->second->toString()));
                break;
        }
    }

    for (std::vector<int>::const_iterator itr = toDelete.begin(); itr != toDelete.end(); ++itr)
    {
        removeObject(*itr);
    }
}

/**
 * Draw all objects to window
 *
 * \param window is a reference to the window to draw to
 */
void ObjectManager::drawAll(sf::RenderWindow& window, GraphicsManager& graphicsManager)
{
    //Sprite to draw to the window
    std::shared_ptr<sf::Sprite> toDraw = nullptr;

    //Draw path
    toDraw = graphicsManager.getSprite(PATH);
    if (toDraw != nullptr && path != nullptr)
    {
        path->draw(toDraw, window);
    }
    //Draw all objects
    for (std::map<int, std::shared_ptr<BaseObject>>::iterator itr = objects.begin(); itr != objects.end(); ++itr)
    {
        std::shared_ptr<BaseObject> currentObj = itr->second;
        toDraw = graphicsManager.getSprite(currentObj->getType());
        if (toDraw != nullptr)
        {
            toDraw->setPosition(currentObj->getPosition());
            toDraw->setRotation(currentObj->getRotation());
            window.draw(*toDraw);
        }
    }
}

std::map<int, std::shared_ptr<BasicEnemy>>& ObjectManager::getEnemies()
{
    return enemies;
}

std::map<int, std::shared_ptr<Tower>>& ObjectManager::getFriends()
{
    return friends;
}

void ObjectManager::addStartingPath(std::shared_ptr<Path> path)
{
    if (path != nullptr)
    {
        this->path = path;
    }
    else
    {
        Game::getLogger().log(dlb::Log(dlb::Log::ERROR,  "Start path in addStartingPath not valid\n"));
    }
}

std::shared_ptr<Path> ObjectManager::getPath()
{
    return path;
}