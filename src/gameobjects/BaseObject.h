#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Type.h"
#include "Team.h"
#include <string>

class ObjectManager;

/**
 * Abstract Base class for all Game Objects (Towers, enemies, etc.)
 * Can only be instantiated by subclasses.
 */
class BaseObject
{
private:
    // unique id of the object. Will be integer between 1 and MaxInt.
    int id;

    //Type of the object
    Type type;

    Team team;

protected:
    //Protected Constructor. Only subclasses can instantiate this object.
    BaseObject(Type type, Team team, sf::Vector2f position, double rotation);

    //Location of the object
    sf::Vector2f position;

    //Direction the object is facing. Especially important for towers to know where to face
    double rotation;

public:
    virtual ~BaseObject() = default;

    //Called in Game::gameLoop()
    virtual int update(sf::Time elapsed) = 0;

    //Return the id of the object
    int getId() const;

    // Return the Type of the object
    Type getType() const;

    //Return the Team of the object
    Team getTeam() const;

    //Getters and setters for position
    void setPosition(sf::Vector2f);
    sf::Vector2f getPosition() const;

    //Getters and Setters for rotation
    double getRotation() const;
    void setRotation(double);

    virtual std::string toString();

    // int to keep track of next unique id
    static int statId;


};

#endif // BASEOBJECT_H_INCLUDED
