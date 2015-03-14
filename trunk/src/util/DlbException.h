#ifndef DLB_EXCEPTION_H
#define DLB_EXCEPTION_H

#include <exception>
#include <string>

namespace dlb
{
    class DlbException : public std::exception
    {
    private:
        std::string message;

    public:
        DlbException(std::string message);
        ~DlbException() = default;

        virtual const char* what() const throw();
    };
}
#endif // DLB_EXCEPTION_H