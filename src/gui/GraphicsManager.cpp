#include "GraphicsManager.h"
#include "../util/Log.h"
#include "../Game.h"

/**
 * Constructor. Eventually should call an init() function or possibly graphicsLoading class to load the textures
 * and then will create the sprites and insert them into map
 *
 */
GraphicsManager::GraphicsManager()
{
    //Need a context to create textures or get wonky graphics creation issues
    sf::Context context;

    //pointer that will create new sprites and insert into map
    std::shared_ptr<sf::Sprite> sprite;

    //Load the background texture and if it succeeds, add to drawable map
    if (!backTexture.loadFromFile("graphics/ui.png"))
    {
        Game::getLogger().log(dlb::Log(dlb::Log::FATAL, "Error: ui.png failed to load."));
    }
    else
    {
        sprite.reset(new sf::Sprite(backTexture));
        drawableMap.insert(std::pair<Type, std::shared_ptr<sf::Sprite>>(BACKGROUND, sprite));
    }

    //Load the gameboard texture and if it succeeds, add it to drawable map
    if (!boardTexture.loadFromFile("graphics/grassTest.png"))
    {
        Game::getLogger().log(dlb::Log(dlb::Log::FATAL, "Error: graphics/gameboard.png failed to load."));
    }
    else
    {
        sprite.reset(new sf::Sprite(boardTexture));
        drawableMap.insert(std::pair<Type, std::shared_ptr<sf::Sprite>>(GAME_BOARD, sprite));
    }

    if (!textureSheet.loadFromFile("graphics/texturesheetdan.png"))
    {
        Game::getLogger().log(dlb::Log(dlb::Log::FATAL, "Error: graphics/gameboard.png failed to load."));
    }
    else
    {
        //Tower
        sprite.reset(new sf::Sprite(textureSheet));
        sprite->setTextureRect(sf::IntRect(0, 0, 24, 24));
        sprite->setOrigin(12, 12);
        drawableMap.insert(std::pair<Type, std::shared_ptr<sf::Sprite>>(TOWER, sprite));

        //Basic Enemy
        sprite.reset(new sf::Sprite(textureSheet));
        sprite->setTextureRect(sf::IntRect(24, 0, 24, 24));
        sprite->setOrigin(12, 12);
        drawableMap.insert(std::pair<Type, std::shared_ptr<sf::Sprite>>(BASIC_ENEMY, sprite));

        //Path
        sprite.reset(new sf::Sprite(textureSheet));
        sprite->setTextureRect(sf::IntRect(48, 0, 24, 24));
        sprite->setOrigin(12, 12);
        drawableMap.insert(std::pair<Type, std::shared_ptr<sf::Sprite>>(PATH, sprite));

        //Basic Solid Shot
        sprite.reset(new sf::Sprite(textureSheet));
        sprite->setTextureRect(sf::IntRect(72, 0, 24, 24));
        sprite->setOrigin(12, 12);
        drawableMap.insert(std::pair<Type, std::shared_ptr<sf::Sprite>>(BASIC_SHOT, sprite));
    }
}

/**
 * Deconstructor. Frees all memory that was allocated in this class
 */
GraphicsManager::~GraphicsManager()
{
    for (std::map<Type, std::shared_ptr<sf::Sprite>>::iterator itr = drawableMap.begin(); itr != drawableMap.end(); ++itr)
        {
            itr->second.reset();
        }
}

/**
 * Function to return the drawable object of the given type.
 *
 * \param key Type of desired drawable object
 * \return sf::Drawable pointer. If not found, return nullptr.
 */
std::shared_ptr<sf::Sprite> GraphicsManager::getSprite(Type key)
{
    std::map<Type, std::shared_ptr<sf::Sprite>>::const_iterator result = drawableMap.find(key);
    if (result == drawableMap.end())
        return nullptr;

    return result->second;
}