#ifndef RENDERINGTHREAD_H_INCLUDED
#define RENDERINGTHREAD_H_INCLUDED

#include "../gameobjects/ObjectManager.h"
#include "GraphicsManager.h"
#include "UserInterface.h"

class RenderingThread
{
private:
    // Pointer to window. Created in main thread and passed in.
    dlb::UserInterface& window;
    // pointer to the object manager. Created in main thread and passed in.
    ObjectManager& objManager;
    //Graphics Manager. Holds pointers to sprites. Objects retrieve the sprites based on Type, transform the sprite, and then draw it to the window.
    GraphicsManager graphicsManager;

    //Thread where rendering logic happens.
    sf::Thread thread;

public:
    RenderingThread(dlb::UserInterface& window, ObjectManager& objManager);
    virtual ~RenderingThread() = default;

    //function passed to the thread's constructor. Where rendering happens
    void renderThread();
};


#endif // RENDERINGTHREAD_H_INCLUDED
