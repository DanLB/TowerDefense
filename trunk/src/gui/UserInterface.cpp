#include <string>
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

    }
}