#include <vector>
#include "dlb.h"

int dlb::charToInt(char ch)
{
    std::string string(1, ch);
    std::stringstream ss(string);
    int result;
    ss >> result;

    return result;
}

//pass in true for keepEmpty if you want an empty element when two delimiters are encountered in a row.
std::vector<std::string> dlb::stringToken(std::string &source, const char delimiter, bool keepEmpty)
{
    std::vector<std::string> results;

    size_t prev = 0;
    size_t next = 0;

    while ((next = source.find_first_of(delimiter, prev)) != std::string::npos)
    {
        if (keepEmpty || (next - prev != 0))
        {
            results.push_back(source.substr(prev, next - prev));
        }
        prev = next + 1;
    }

    if (prev < source.size())
    {
        results.push_back(source.substr(prev));
    }

    return results;
}