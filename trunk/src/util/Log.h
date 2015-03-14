#ifndef LOG_H
#define LOG_H

#include <string>
#include <chrono>

namespace dlb
{
    class Log
    {
    public:
        enum Level
            {
                OFF,
                FATAL,
                ERROR,
                WARN,
                INFO,
                DEBUG,
                TRACE
            };
    private:
        Level level;
        std::string message;
        std::chrono::system_clock::time_point timeStamp;

    protected:
        std::string getEnumString(Level level);

    public:
        Log(Level level, std::string message);
        ~Log() = default;

        std::string toString();
        Level getLevel();
    };
}
#endif // LOG_H