#include <SFML/Graphics.hpp>
#include "gameobjects/Tower.h"
#include "gameobjects/BasicEnemy.h"
#include "Game.h"
#include "util/Log.h"
#include "gui/UserInterface.h"

/**
 * Constructor. Initializes variables and calls init()
 *
 * NOTE: window should be created in main thread (this one) and then deactivated and passed to rendering thread.
 * Events should still be handled in main thread. This is both a best practice and a requirement for MacOS.
 */
Game::Game() :
    window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tower Defense", sf::Style::Titlebar | sf::Style::Close),
    levelLoader(objManager),
    renderThread(window, objManager)
{
    logger.start();
    init();
}

/**
 * Starts the game. Called from main.
 */
int Game::run()
{
    gameLoop();
    return 0;
}

/**
 * Function to setup and various dependencies
 */
void Game::init()
{
    //window must be deactivated to be drawn in separate thread.
    window.setActive(false);

    bool levelLoaded = levelLoader.loadLevel(1);

    //TODO These are only here for testing purposes

    //Towers
    std::shared_ptr<Tower> tower(new Tower(TOWER, sf::Vector2f(108, 60), 2000, BASIC_SHOT, 48));
    objManager.addTower(tower);
    tower.reset(new Tower(TOWER, sf::Vector2f(372, 132), 2000, BASIC_SHOT, 48));
    objManager.addTower(tower);
    //Enemies
    std::shared_ptr<BasicEnemy> enemy(new BasicEnemy(objManager.getPath(), 30, BASIC_ENEMY, 10));
    objManager.addEnemy(enemy);
}

/**
 * Main gameloop.
 * Calls update logic and handles events
 */
void Game::gameLoop()
{
    sf::Clock clock;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        if (elapsed.asSeconds() > 1/15.0f)
        {
            elapsed = sf::seconds(1/15.0f);
        }
        objManager.updateAll(elapsed);

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    /** ESCAPE key to close the game */
                    case sf::Keyboard::Key::Escape:
                        window.close();
                        break;
                    /** F2 spawns another enemy */
                    case sf::Keyboard::Key::F2:
                        {
                            std::shared_ptr<BasicEnemy> enemy(new BasicEnemy(objManager.getPath(), 30, BASIC_ENEMY, 10));
                            objManager.addEnemy(enemy);
                            break;
                        }
                    default:
                        break;
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        int x = event.mouseButton.x;
                        if (x > GAME_WIDTH)
                        {
                            window.click(x, event.mouseButton.y);
                        }
                        else
                        {
                            logger.log(dlb::Log(dlb::Log::Level::INFO, "Clicked board"));
                        }
                    }
                    break;
                default:
                    break;
            }
        } //Event checking
    } //GameLoop
}

ObjectManager& Game::getObjectManager()
{
    return objManager;
}

dlb::Logger& Game::getLogger()
{
    return logger;
}

int Game::getGameWidth()
{
    return GAME_WIDTH;
}

int Game::getGameHeight()
{
    return GAME_HEIGHT;
}

dlb::UserInterface& Game::getWindow()
{
    return window;
}

/******** STATIC VARIABLE INITIALIZATION ********/
ObjectManager Game::objManager;
dlb::Logger Game::logger("log.txt", dlb::Log::Level::TRACE, dlb::Log::Level::INFO);