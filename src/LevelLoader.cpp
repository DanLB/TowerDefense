#include "gameobjects/ObjectManager.h"
#include "LevelLoader.h"
#include <fstream>
#include "util/dlb.h"
#include "Game.h"

LevelLoader::LevelLoader(ObjectManager& objManager) : objManager(objManager)
{}

bool LevelLoader::loadLevel(int lvl)
{

    Game::getLogger().log(dlb::Log(dlb::Log::Level::INFO, "Loading level " + dlb::toString(lvl)));
    bool status = true;
    int min = 1;
    int max = 0;
    std::string level = dlb::toString<int>(lvl);

    std::string filename = "path/" + level + ".txt";
    std::ifstream file(filename);

    //string to hold the line that was read in
    std::string line;

    if (!file.is_open())
    {
        Game::getLogger().log(dlb::Log(dlb::Log::Level::FATAL, "LevelLoader file " + filename + " failed to open"));
        status = false;
        return false;
    }

    std::map<int, std::shared_ptr<Path>> pathMap;
    //Get the position of all Path objects
    while (file.good())
    {
        std::getline(file, line);

        if (line.size() == 0)
            break;

        if (line.at(0) == '#')
            continue;

        //Split the comma-delimited string read from the file
        std::vector<std::string> splitString = dlb::stringToken(line, ',', false);

        int size = splitString.size();

        //If the line doesn't have at 3 values, it's bad data so return false
        if (size == 3)
        {
            float x = dlb::parseNum<float>(splitString.at(1));
            float y = dlb::parseNum<float>(splitString.at(2));

            int index = dlb::parseNum<int>(splitString.at(0));

            std::shared_ptr<Path> path(new Path(sf::Vector2f(x, y)));

            pathMap.insert(std::pair<int, std::shared_ptr<Path>>(index, path));

            if (index > max)
                max = index;
            if (index < min)
                min = index;
        }
        else
        {
            status = false;
            break;
        }
    }

    //Basic error checking before continuing
    if (!status || min != 0 || min >= max)
        return false;

    //Add the first path to the ObjectManager
    std::map<int, std::shared_ptr<Path>>::iterator firstItr = pathMap.find(0);

    if (firstItr == pathMap.end())
    {
        return false;
    }

    std::map<int, std::shared_ptr<Path>>:: iterator end = pathMap.end();
    end--;
    end->second.get()->setEnd();

    std::shared_ptr<Path> first = firstItr->second;

    objManager.addStartingPath(first);

    //Create the path
    while (file.good())
    {
        std::getline(file, line);

        if (line.size() == 0)
            break;

        if (line.at(0) == '#')
            continue;

        //Split the comma-delimited string read from the file
        std::vector<std::string> splitString = dlb::stringToken(line, '-', false);

        //If the line doesn't have at least 2 values, it's bad data so skip
        if (splitString.size() > 1)
        {
            int index = dlb::parseNum<int>(splitString.at(0));
            std::map<int, std::shared_ptr<Path>>::iterator currItr = pathMap.find(index);

            //If not found
            if (currItr == pathMap.end())
            {
                status = false;
                break;
            }

            std::shared_ptr<Path> current = currItr->second;

            std::map<int, std::shared_ptr<Path>>::iterator nextItr = pathMap.find(index);
            std::shared_ptr<Path> next;

            for (unsigned int i = 1; i < splitString.size(); ++i)
            {
                int index = dlb::parseNum<int>(splitString.at(i));
                nextItr = pathMap.find(index);

                //If next path wasn't false, bad data so escape
                if (nextItr == pathMap.end())
                {
                    status = false;
                    break;
                }

                next = nextItr->second;
                current->addPath(next);
            }

            if (status == false)
                break;
        }
    }

    return status;
}