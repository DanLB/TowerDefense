#ifndef DLB_WINDOW_H
#define DLB_WINDOW_H

class GuiObject;

namespace dlb
{
    class UserInterface : public sf::RenderWindow
    {
    private:
        sf::RenderWindow window;

        std::vector<std::shared_ptr<GuiObject>> guiObjects;
    protected:

    public:
        UserInterface(sf::VideoMode mode, const std::string& title, sf::Uint32 style=sf::Style::Default);
        void click(float x, float y);

        void drawAll();

        void add(std::shared_ptr<GuiObject> object);
    };
}
#endif // WINDOW_H