#include "GuiObject.h"
#include "Button.h"

Button::Button(sf::Vector2f location, std::string text, sf::Color backColor, sf::Color foreColor):
    sText()
{
   sText.setString(text);
   sText.setOrigin(sText.getLocalBounds().width / 2.f, sText.getLocalBounds().height / 2.f);
   sText.setPosition(location);
   sText.setColor(foreColor);

   sf::Image img;
   img.create(((unsigned int)(sText.getLocalBounds().width) + 10), ((unsigned int)(sText.getLocalBounds().height) + 10), backColor);
   image.loadFromImage(img);
   sprite = sf::Sprite(image);
   sprite.setOrigin(image.getSize().x / 2.f, image.getSize().y / 2.f);
   sprite.setPosition(location);
   sf::Vector2f size = sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
   rect = sf::FloatRect(location.x - (size.x / 2.f), location.y - (size.y / 2.f), location.x + size.x / 2.f, location.y + size.y / 2.f);
}

Button::~Button()
{}

void Button::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(sText);
}

void Button::ChangeText(std::string newstring)
{
    sText.setString(newstring);
    sText.setOrigin(sText.getLocalBounds().width / 2.f, sText.getLocalBounds().height / 2.f);
}

void Button::ChangeFont(sf::Font font)
{
    sText.setFont(font);
}

void Button::click(float x, float y)
{
    if (rect.contains(x, y))
    {
        //todo clickable actions
    }
}