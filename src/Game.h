#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <memory>

#include "gui/RenderingThread.h"
#include "gameobjects/ObjectManager.h"
#include "path/Path.h"
#include "LevelLoader.h"
#include "util/Logger.h"

class UserInterface;

/**
 * This class controls the game. It is a border-line God class.
 * As the game develops, functions and data may need to be refactored out into smaller classes
 */
class Game
{
private:
    static const int GAME_WIDTH = 480;
    static const int GAME_HEIGHT = 480;
    static const int SCREEN_WIDTH = 630;
    static const int SCREEN_HEIGHT = 480;
    //Logger
    static dlb::Logger logger;

    //Called from Constructor. Initializes window and other basics
    void init();
    //Main game loop. Called from run()
    void gameLoop();

    // Main game window
    dlb::UserInterface window;

    //Class that handles managing all game objects
    static ObjectManager objManager;

    //Class to load each level
    LevelLoader levelLoader;

    //Class to render stuff to the window in its own thread
    RenderingThread renderThread;

public:
    Game();
    virtual ~Game() = default;

    //Called from main.cpp. Starts the game
    int run();

    dlb::UserInterface& getWindow();

    static ObjectManager& getObjectManager();

    static dlb::Logger& getLogger();

    static int getGameWidth();

    static int getGameHeight();
};

#endif // GAME_H_INCLUDED
