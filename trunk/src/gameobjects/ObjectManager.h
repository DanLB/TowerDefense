#ifndef OBJECTMANAGER_H_INCLUDED
#define OBJECTMANAGER_H_INCLUDED

#include <map>
#include <memory>
#include "../path/Path.h"
#include "BaseObject.h"
#include "../gui/GraphicsManager.h"
#include "Tower.h"
#include "BasicEnemy.h"

/**
 * Class to manage all gameObjects
 */
class ObjectManager
{
private:
    /**
     * Stores game objects. Maps object IDs to a pointer to the object
     */    std::map<int, std::shared_ptr<BaseObject>> objects;

    // Holds pointers to enemy objects
    std::map<int, std::shared_ptr<BasicEnemy>> enemies;

    // Holds pointers to friend objects
    std::map<int, std::shared_ptr<Tower>> friends;

    std::shared_ptr<Path> path;

protected:

public:
    ObjectManager();
    virtual ~ObjectManager();

    void addObject(std::shared_ptr<BaseObject>);

    void addEnemy(std::shared_ptr<BasicEnemy> enemy);

    void addTower(std::shared_ptr<Tower> tower);

    std::shared_ptr<BaseObject> getObject(int);

    void removeObject(int);

    // Deletes all objects in the map and clears the map.
    void clearObjectManager();

    // Update all objects
    void updateAll(sf::Time);

    // Draw all objects
    void drawAll(sf::RenderWindow&, GraphicsManager&);

    //TODO Possibly have these return vectors or lists
    std::map<int, std::shared_ptr<BasicEnemy>>& getEnemies();

    std::map<int, std::shared_ptr<Tower>>& getFriends();

    void addStartingPath(std::shared_ptr<Path> path);

    std::shared_ptr<Path> getPath();
};

#endif // OBJECTMANAGER_H_INCLUDED
