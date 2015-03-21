#include "Logger.h"
#include <iostream>

namespace dlb
{
    Logger::Logger(std::string logFileName, Log::Level fileLevel, Log::Level consoleLevel) :
        logQueue1(),
        logQueue2(),
        outThread(&Logger::write, this),
        file(logFileName),
        fileLevel(fileLevel),
        consoleLevel(consoleLevel),
        logFileName(logFileName)
    {
        logPointer = &logQueue1;
    }

    Logger::~Logger()
    {
        if (file.is_open())
        {
            file << "Stopping Logger \n";
            outThread.terminate();
            file.close();
        }
    }

    void Logger::start() throw (DlbException)
    {
        if (!file.is_open())
        {
            throw DlbException(logFileName + " didn't open");
        }
        logPointer->push(Log(Log::INFO, "Starting Logger thread"));
        outThread.launch();
    }

    void Logger::write()
    {
        std::queue<Log>* writePointer;

        while(true)
        {
            //Using a mutex instead of a lock because simple assignment should never throw an exception
            mutex.lock();
            if (logPointer == &logQueue1)
            {
                logPointer = &logQueue2;
                writePointer = &logQueue1;
            }
            else
            {
                logPointer = &logQueue1;
                writePointer = &logQueue2;
            }
            mutex.unlock();

            while (writePointer->size() > 0)
            {
                Log log = writePointer->front();
                writePointer->pop();
                if (log.getLevel() <= fileLevel)
                    file << log.toString() << "\n";

                if (log.getLevel() <= consoleLevel)
                    std::cout << log.toString() << "\n";
            }

            sf::sleep(sf::milliseconds(100));
        }
    }

    void Logger::log(Log log)
    {
        //Using a lock because push can throw exception
        sf::Lock lock(mutex);
        logPointer->push(log);
    }
}