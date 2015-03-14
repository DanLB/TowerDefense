#include "BaseObject.h"

/**
 * Constructor.
 */
BaseObject::BaseObject(Type type, Team team, sf::Vector2f position, double rotation) :
    type(type),
    team(team),
    position(position),
    rotation(rotation),
    id(++statId) //sets the id to the next available ID
{}

int BaseObject::getId() const
{
    return id;
}

Type BaseObject::getType() const
{
    return type;
}

Team BaseObject::getTeam() const
{
    return team;
}

void BaseObject::setPosition(sf::Vector2f position)
{
    this->position = position;
}

sf::Vector2f BaseObject::getPosition() const
{
    return position;
}

double BaseObject::getRotation() const
{
    return rotation;
}

void BaseObject::setRotation(double rotation)
{
    this->rotation = rotation;
}

std::string BaseObject::toString()
{
    return "";
}

/**
 * Static id starts at zero and is incremented each time a new object is created
 */
int BaseObject::statId = 0;

