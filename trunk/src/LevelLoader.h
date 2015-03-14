#ifndef LEVELLOADER_H
#define LEVELLOADER_H

/**
 * This class loads the data for each individual level.
 * Currently, it only loads the path, but eventually it will load other information as well.
 */
class LevelLoader
{
private:
    //Object Manager to set the start path and other information for.
    ObjectManager& objManager;

public:
    LevelLoader(ObjectManager& objManager);
    virtual ~LevelLoader() = default;

    //Method that loads the level.
    bool loadLevel(int);
};

#endif // LEVELLOADER_H