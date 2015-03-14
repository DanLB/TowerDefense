#ifndef GRAPHICSMANAGER_H_INCLUDED
#define GRAPHICSMANAGER_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "../gameobjects/Type.h"
#include <map>
#include <memory>

class GraphicsManager
{
private:
    //background texture. Basic UI
    sf::Texture backTexture;

    //Gameboard texture
    sf::Texture boardTexture;

    //Texture sheet
    sf::Texture textureSheet;

    /**
     * This map uses Type as a key and holds the Sprites and other drawable objects.
     *
     * The rendering logic gets the correct drawable object,
     * transforms it if necessary for each object of the given type, and then draws it to the window.
     */
    std::map<Type, std::shared_ptr<sf::Sprite>> drawableMap;

protected:

public:
    GraphicsManager();
    virtual ~GraphicsManager();

    // function to get the drawable object associated with the specified Type
    std::shared_ptr<sf::Sprite> getSprite(Type);
};

#endif // GRAPHICSMANAGER_H_INCLUDED
