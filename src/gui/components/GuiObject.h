#ifndef GOBJECT_H
#define GOBJECT_H

#include <SFML/Graphics.hpp>

class GuiObject
{
public:
    virtual void click(float x, float y) = 0;

    virtual void draw(sf::RenderWindow& window) = 0;
};

#endif // GOBJECT_H