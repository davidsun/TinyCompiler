#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class Exception : public exception{
    public:
        Exception(const string &what);
        ~Exception() throw();

        virtual const char *what() const throw();

    private:
        string _what;
};

#endif
