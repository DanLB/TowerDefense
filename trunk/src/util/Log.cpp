#include "Log.h"

#include <ctime>

namespace dlb
{
    Log::Log(Level level, std::string message) :
        level(level),
        message(message)
    {
        timeStamp = std::chrono::system_clock::now();
    }

    Log::Level Log::getLevel()
    {
        return level;
    }

    std::string Log::toString()
    {
        time_t tt = std::chrono::system_clock::to_time_t(timeStamp);
        std::string time = std::string(std::ctime(&tt));
        int n = time.find_last_of("\n");
        if (n != std::string::npos)
            time = time.replace(n, 2, "");
        return time + " (" + getEnumString(level) + "): " + message;
    }

    std::string Log::getEnumString(Level level)
    {
        switch (level)
        {
        case OFF:
            return "OFF";
            break;
        case FATAL:
            return "FATAL";
            break;
        case ERROR:
            return "ERROR";
            break;
        case WARN:
            return "WARN";
            break;
        case INFO:
            return "INFO";
            break;
        case DEBUG:
            return "DEBUG";
            break;
        case TRACE:
            return "TRACE";
            break;
        }
    }
}