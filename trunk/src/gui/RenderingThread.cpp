#include "RenderingThread.h"

/**
 * Constructor. pass in renderingwindow (main window) and object manager.
 * Instantiate variables and then launch the renderingThread
 */
RenderingThread::RenderingThread(dlb::UserInterface& window, ObjectManager& objManager) :
    window(window),
    objManager(objManager),
    thread(&RenderingThread::renderThread, this), //Instantiate thread to call renderingThread() upon launch
    graphicsManager()
{
    thread.launch();
}

/**
 * Function started in own thread. All of the rendering logic happens here.
 */
void RenderingThread::renderThread()
{
    //Rendering loop
    while (window.isOpen())
    {
        //Get the sprite pointer and then dereference it to draw to screen
        std::shared_ptr<sf::Sprite> sprite = graphicsManager.getSprite(BACKGROUND);

        if (sprite != nullptr)
            window.draw(*sprite);

        sprite = graphicsManager.getSprite(GAME_BOARD);
        if (sprite != nullptr)
            window.draw(*sprite);

        //draw objects
        objManager.drawAll(window, graphicsManager);

        window.drawAll();

        //end the current frame
        window.display();
    }
}