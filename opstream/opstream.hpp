#pragma once
#include <cstdio>
#include <ostream>
#include <memory>

// output pipe stream buffer
class opstreambuf : public std::streambuf {
public:
	opstreambuf() = default;
    opstreambuf(char const * process);
	
	opstreambuf(const opstreambuf&) = delete;
	opstreambuf(opstreambuf&& other);
	
	opstreambuf& operator=(const opstreambuf&) = delete;
	opstreambuf& operator=(opstreambuf&& other);
	
	virtual ~opstreambuf();

	void open(char const* process);
	void close();
	bool is_open();

protected:

    std::unique_ptr<char[]> buffer;
	FILE* fprocess = nullptr;

	// specify what should be done to flush the buffer (aka. synchronise the buffer with the device)
    int sync() override; 
	int overflow(int c) override;
};

class opstream : public std::ostream {
public:
	opstream() = default;
	opstream(char const * process);
	
	opstream(const opstream&) = delete;
	opstream(opstream&& other);
	
	opstream& operator=(const opstream&) = delete;
	opstream& operator=(opstream&& other);
	
	void open(char const* process);
	void close();
	bool is_open();
	
protected:
	opstreambuf buf;
	
};
