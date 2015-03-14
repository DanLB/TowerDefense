#ifndef DLB_H
#define DLB_H

#include <exception>
#include <string>
#include <sstream>
#include <SFML/System.hpp>

/**
 * Utility class that I transfer from program to program I use when I need a function regularly.
 * The string conversion functions shouldn't be necessary with C++11
 * but there is a bug with MingGW so the new functions don't work.
 */
namespace dlb
{
    template <class T>
    std::string toString(T num)
    {
        std::stringstream ss;
        ss << num;
        std::string string = ss.str();

        return string;
    }

    template <class T>
    T parseNum(std::string string)
    {
        std::stringstream ss(string);
        T result;
        ss >> result;

        return result;
    }

    //Method to find the distance to an object, squared
    template <class T>
    double distanceSquared(sf::Vector2<T> a, sf::Vector2<T> b)
    {
        double y = b.y - a.y;
        double x = b.x - a.x;
        return y * y + x * x;
    }

    int charToInt(char ch);

    std::vector<std::string> stringToken(std::string &source, const char delimiter = ' ', bool keepEmpty = false);

    class Exception : public std::exception
    {
    public:
        Exception(const std::string& msg) : msg_(msg) {}
        const char* what() const noexcept {return msg_.c_str();}
    private:
        std::string msg_;
    };
}

#endif
