#include "DlbException.h"

namespace dlb
{
    DlbException::DlbException(std::string message) :
        message(message)
    {}

    const char* DlbException::what() const throw()
    {
        return message.c_str();
    }
}