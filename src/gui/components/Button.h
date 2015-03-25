#ifndef BUTTON_H
#define BUTTON_H

#include "GuiObject.h"

class Button : public GuiObject
{
public:
    Button(sf::Vector2f, std::string, sf::Color, sf::Color);
    virtual ~Button();

    void ChangeText(std::string newstring);
    void ChangeFont(sf::Font font);

    void click(float x, float y);

    void virtual draw(sf::RenderWindow& window);

private:
    //Texture and font need to be in scope when draw is called.
    sf::Font font;
    sf::Texture image;

    sf::Text sText;
    sf::Sprite sprite;
    sf::FloatRect rect;
};

#endif