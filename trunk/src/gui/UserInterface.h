#ifndef DLB_WINDOW_H
#define DLB_WINDOW_H

#include <SFML/Graphics.hpp>
#include "components/GuiObject.h"

namespace dlb
{
    class UserInterface : public sf::RenderWindow
    {
    private:
        sf::RenderWindow window;

        std::vector<GuiObject*> guiObjects;
    protected:

    public:
        UserInterface(sf::VideoMode mode, const std::string& title, sf::Uint32 style=sf::Style::Default);
        void click(float x, float y);

        void drawAll();
    };
}
#endif // WINDOW_H