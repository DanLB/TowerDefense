#include "MovingObject.h"
#include "../Game.h"

#ifndef PI
    #define PI 3.14159265
#endif // PI

MovingObject::MovingObject(Type type, Team team, sf::Vector2f position, double heading, double speed) :
    // The heading should be either 0, 90, 180, or 270. Set BaseObject's rotation to that as well.
    BaseObject(type, team, position, heading),
    speed(speed)
{}

int MovingObject::update(sf::Time elapsed)
{
    int updated = updateLogic(elapsed);
    if (updated != 0)
        return updated;

    moveSelf(elapsed);

    int collided = calculateCollisions();
    if (collided != 0)
        return collided;

    if (position.x < 0 || position.x > Game::getGameWidth() || position.y < 0 || position.y > Game::getGameHeight())
    {
        int ooB = outOfBounds();
        if (ooB != 0)
            return ooB;
    }
    return 0;
}

void MovingObject::moveSelf(sf::Time elapsed)
{
    //Heading, speed, position
    double headingInRad = rotation * PI / 180;
    float y = sin(headingInRad) * speed;
    float x = cos(headingInRad) * speed;

    position.x += x * elapsed.asSeconds();
    position.y += y * elapsed.asSeconds();
}