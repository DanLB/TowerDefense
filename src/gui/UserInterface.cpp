#include <string>
#include <SFML/Graphics.hpp>
#include "GraphicsManager.h"
#include "components/GuiObject.h"
#include "UserInterface.h"
#include "../Game.h"
#include "../util/dlb.h"

namespace dlb
{
    UserInterface::UserInterface(sf::VideoMode mode, const std::string& title, sf::Uint32 style) :
        sf::RenderWindow(mode, title, style)
    {

    }

    void UserInterface::click(float x, float y)
    {
        Game::getLogger().log(dlb::Log(dlb::Log::Level::INFO, "In UserInterface::click --> " + dlb::toString(x) + ", " + dlb::toString(y)));
        for (auto& obj : guiObjects)
        {
            obj->click(x, y);
        }
    }

    void UserInterface::drawAll()
    {
        for (std::vector<std::shared_ptr<GuiObject>>::iterator itr = guiObjects.begin(); itr != guiObjects.end(); ++itr) {
            std::shared_ptr<GuiObject> currentObject = *itr;
            currentObject->draw(*this);
        }
    }


    void UserInterface::add(std::shared_ptr<GuiObject> object) {
        guiObjects.push_back(object);
    }
}