#include "Path.h"
#include "../util/dlb.h"
#include <random>
#include <chrono>

Path::Path(sf::Vector2f position) :
    BaseObject(Type::PATH, Team::NONE, position, 0)
{
    path = std::vector<std::shared_ptr<Path>>();
}

void Path::addPath(std::shared_ptr<Path> path)
{
    this->path.push_back(path);
}

std::shared_ptr<Path> Path::getNext()
{
    int size = path.size();

    if (size == 0)
        return nullptr;

    if (size == 1)
        return path.at(0);
    else
    {
        size--;
        // construct a trivial random generator engine from a time-based seed:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution(0,size);
        int r = distribution(generator);
        return path.at(r);
    }
}

void Path::draw(std::shared_ptr<sf::Sprite> sprite, sf::RenderWindow& window)
{
    //Draw this path object
    sprite->setPosition(position);
    window.draw(*sprite);

    //Use for_each to iterate through all paths and draw them.
    //Uses lamda function to recursively call the elements' draw function.
    std::for_each(path.begin(), path.end(), [sprite, &window](std::shared_ptr<Path> pathDraw){pathDraw->draw(sprite, window);});
}

int Path::update(sf::Time elapsed)
{}

std::string Path::toString()
{
    return "Path #" + dlb::toString<int>(getId()) + " position (" + dlb::toString<float>(position.x) + ", " + dlb::toString<float>(position.y) + ")";
}