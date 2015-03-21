#ifndef LOGGER_H
#define LOGGER_H

#include <queue>
#include <fstream>
#include <string>
#include "Log.h"
#include "SFML/System.hpp"
#include "DlbException.h"

namespace dlb {
    class Logger
    {
    private:
        std::queue<Log> logQueue1;
        std::queue<Log> logQueue2;

        std::queue<Log>* logPointer;
        sf::Mutex mutex;

        sf::Thread outThread;

        std::ofstream file;

        Log::Level fileLevel;
        Log::Level consoleLevel;

        std::string logFileName;
    protected:
        void write();

    public:
        Logger(std::string logFileName, Log::Level fileLevel, Log::Level consoleLevel);
        ~Logger();

        void start() throw (DlbException);

        void log(Log log);
    };
}
#endif // LOGGER_H