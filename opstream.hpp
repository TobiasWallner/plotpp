#pragma once
#include <cstdio>
#include <ostream>

// output pipe stream buffer
class opstreambuf : public std::streambuf {
public:
    opstreambuf(char const * process);
	virtual ~opstreambuf();

protected:

    char buffer[1024];
	FILE* fprocess = nullptr;

	// specify what should be done to flush the buffer (aka. synchronise the buffer with the device)
    int sync() override; 
};

class opstream : public std::ostream {
public:
	opstream(char const * process);
	
protected:
	opstreambuf buf;
	
};
