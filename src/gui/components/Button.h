#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

//class GuiObject;

class Button : public GuiObject
{
public:
    Button(sf::Vector2f, std::string, sf::Color, sf::Color);
    virtual ~Button();

    void virtual Draw(sf::RenderWindow& window);

    void ChangeText(std::string newstring);
    void ChangeFont(sf::Font font);

    void click(float x, float y);

private:
    sf::Text sText;
    sf::Texture image;
    sf::Sprite sprite;
    sf::FloatRect rect;
};

#endif