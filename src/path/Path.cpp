
#include <chrono>
#include "Path.h"
#include "../util/dlb.h"
#include "../Game.h"

Path::Path(sf::Vector2f position) :
    BaseObject(Type::PATH, Team::NONE, position, 0),
    size(0)
{
    path = std::vector<std::shared_ptr<Path>>();

    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = std::default_random_engine(seed);
}

void Path::addPath(std::shared_ptr<Path> path)
{
    this->path.push_back(path);
    size = this->path.size();
    if (size > 0) {
        distribution = std::uniform_int_distribution<unsigned int>(0, size - 1);
    }
}

std::shared_ptr<Path> Path::getNext()
{
    if (size == 0) {
        return nullptr;
    }
    return path.at(distribution(generator));
}

void Path::draw(std::shared_ptr<sf::Sprite> sprite, sf::RenderWindow& window)
{
    //Draw this path object
    sprite->setPosition(position);
    window.draw(*sprite);

    //Use for_each to iterate through all paths and draw them.
    //Uses lambda function to recursively call the elements' draw function.
    std::for_each(path.begin(), path.end(), [sprite, &window](std::shared_ptr<Path> pathDraw){pathDraw->draw(sprite, window);});
}

void Path::setEnd() {

    Game::getLogger().log(dlb::Log(dlb::Log::Level::INFO, toString()));
    win = true;
}

bool Path::end() {
    return win;
}

int Path::update(sf::Time elapsed)
{
    return 0;
}

std::string Path::toString()
{
    return "Path #" + dlb::toString<int>(getId()) + " position (" + dlb::toString<float>(position.x) + ", " + dlb::toString<float>(position.y) + ")";
}