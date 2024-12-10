#include "opstream.hpp"
#include <iostream>
#include <exception>

//
// Stream Buffer Functions
//

opstreambuf::opstreambuf(char const * process) {
	this->open(process);
}

opstreambuf::opstreambuf(opstreambuf&& other){
	this->buffer = std::move(other.buffer);
	this->fprocess = other.fprocess;
	other.fprocess = nullptr;	
}

opstreambuf& opstreambuf::operator=(opstreambuf&& other){
	this->close();
	if(this != &other){
		this->buffer = std::move(other.buffer);
		this->fprocess = other.fprocess;
		other.fprocess = nullptr;	
	}
	return *this;
}

opstreambuf::~opstreambuf(){
	this->close();
}

void opstreambuf::open(char const* process){
	// close an existing open stream
	if(this->is_open()) this->close();
	
	// allocating the buffer
	constexpr size_t bufferSize = 128;
	this->buffer = std::make_unique<char[]>(bufferSize);
	this->std::streambuf::setp(buffer.get(), buffer.get() + bufferSize);
	
	// open the FILE pointer
	#ifdef WIN32
	fprocess = _popen(process, "w");
	#else
	fprocess = popen(process, "w");
	#endif

	if(process == nullptr){
		std::string s;
		s = "Could not open the pipe stream with the command: ";
		s += process;
		throw std::runtime_error(s);
	}
}

void opstreambuf::close(){
	this->sync();
	
	// deallocate the buffer
	if(this->buffer){
		this->buffer.reset();
	}
	
	// close the pipe stream
	if(this->fprocess != nullptr){		
		#ifdef WIN32
		int status = _pclose(this->fprocess);
		#else
		int status = pclose(this->fprocess);
		#endif	
		
		if (status != 0) 
			throw std::runtime_error("Could not close the pipe stream");
		else 
			this->fprocess = nullptr;
	}
}

bool opstreambuf::is_open(){
	return this->fprocess != nullptr;
}

int opstreambuf::sync() {
	std::streamsize num = pptr() - pbase();
	if (num > 0) {
		size_t r = fwrite(this->std::streambuf::pbase(), sizeof(char), num, fprocess);
		this->std::streambuf::pbump(-num); 
		if(r != num){
			return -1; // error
		}
	}
	return 0;
}

int opstreambuf::overflow(int c) {
	int r = this->sync();
	if(r != 0) return -1; // error
	this->buffer[0] = static_cast<char>(c);
	this->std::streambuf::pbump(1);
	return 0;
}

// ----------------------------------------------------------
//							opstream
// ----------------------------------------------------------

opstream::opstream(char const * process) 
	: std::ostream(&buf)
	, buf(process){}
	
opstream::opstream(opstream&& other){
	this->buf = std::move(other.buf);
}

opstream& opstream::operator=(opstream&& other){
	if(this != &other){
		this->buf = std::move(other.buf);
	}
	return *this;
}	

void opstream::open(char const* process){
	this->buf.open(process);
}
	
void opstream::close(){
	this->buf.close();
}

bool opstream::is_open(){
	return this->buf.is_open();
}
