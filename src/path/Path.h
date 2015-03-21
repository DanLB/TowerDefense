#ifndef PATH_H
#define PATH_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "../gameobjects/BaseObject.h"

class Path : public BaseObject
{
private:
    std::vector<std::shared_ptr<Path>> path;

    unsigned int size;
    // a trivial random generator engine
    std::default_random_engine generator;
    std::uniform_int_distribution<unsigned int> distribution;

    bool win = false;

public:
    Path(sf::Vector2f position);
    //shared_ptr should handle deallocation
    virtual ~Path() = default;

    void addPath(std::shared_ptr<Path> path);

    std::shared_ptr<Path> getNext();

    void draw(std::shared_ptr<sf::Sprite> sprite, sf::RenderWindow& window);

    void setEnd();

    bool end();

    int update(sf::Time elapsed);

    std::string toString();
};

#endif // PATH_H