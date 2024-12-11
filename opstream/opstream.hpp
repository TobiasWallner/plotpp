#pragma once
#include <cstdio>
#include <ostream>
#include <memory>

// output pipe stream buffer
class opstreambuf : public std::streambuf {
public:
	opstreambuf();
    opstreambuf(char const * process);
	
	opstreambuf(const opstreambuf&) = delete;
	opstreambuf(opstreambuf&& other) noexcept;
	
	opstreambuf& operator=(const opstreambuf&) = delete;
	opstreambuf& operator=(opstreambuf&& other) noexcept;
	
	virtual ~opstreambuf();

	void open(char const* process);
	void close();
	bool is_open() const;

protected:

    std::unique_ptr<char[]> buffer = nullptr;
	FILE* fprocess = nullptr;

    int sync() override; 
	int overflow(int c) override;
};

class opstream : public std::ostream {
public:
	opstream();
	opstream(char const * process);
	
	opstream(const opstream&) = delete;
	opstream(opstream&& other) noexcept;
	
	opstream& operator=(const opstream&) = delete;
	opstream& operator=(opstream&& other) noexcept;
	
	void open(char const* process);
	void close();
	bool is_open() const;
	
protected:
	opstreambuf buf;
	
};
