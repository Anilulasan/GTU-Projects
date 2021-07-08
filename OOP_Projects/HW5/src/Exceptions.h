#ifndef BoardException_h
#define BoardException_h

#include <stdexcept>
using namespace std;

class BoardException : public runtime_error{
public:
	BoardException()
    : runtime_error("tried to reach out of board...") {}
};

class moveException : public runtime_error{
public:
	moveException()
    : runtime_error("there is no move yet...") {}
};

#endif
