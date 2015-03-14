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

public:
    Path(sf::Vector2f position);
    //shared_ptr should handle deallocation
    virtual ~Path() = default;

    void addPath(std::shared_ptr<Path> path);

    std::shared_ptr<Path> getNext();

    void draw(std::shared_ptr<sf::Sprite> sprite, sf::RenderWindow& window);

    int update(sf::Time elapsed);

    std::string toString();
};

#endif // PATH_H