#ifndef GOBJECT_H
#define GOBJECT_H

class GuiObject
{
public:
    virtual void click(float x, float y) = 0;
};

#endif // GOBJECT_H