#include "opstream.hpp"
#include <iostream>
#include <exception>

//
// Stream Buffer Functions
//

opstreambuf::opstreambuf() 
	: buffer()
	, fprocess(nullptr)
{}

opstreambuf::opstreambuf(char const * process) {
	this->open(process);
}

opstreambuf::opstreambuf(opstreambuf&& other) noexcept{
	this->buffer = std::move(other.buffer);
	this->fprocess = other.fprocess;
	other.fprocess = nullptr;	
}

opstreambuf& opstreambuf::operator=(opstreambuf&& other) noexcept{
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
	if(this->is_open()){
		this->close();
	}
	
	// allocating the buffer
	constexpr size_t bufferSize = 128;
	this->buffer = std::make_unique<char[]>(bufferSize);
	if(!this->buffer){
		throw std::runtime_error("could not allocate buffer for opstreambuf in opstreambuf::open(char const* process)");
	}
	
	this->std::streambuf::setp(buffer.get(), buffer.get() + bufferSize);
	
	// open the FILE pointer
	#ifdef WIN32
	fprocess = _popen(process, "w");
	#else
	fprocess = popen(process, "w");
	#endif

	if(fprocess == nullptr){
		std::string s;
		s = "Could not open the pipe stream with the command: ";
		s += process;
		throw std::runtime_error(s);
	}
}

void opstreambuf::close(){
	if(this->is_open()){
		this->sync();
		
		// deallocate the buffer
		this->buffer.reset();
		
		// close the pipe stream
		#ifdef WIN32
		int status = _pclose(this->fprocess);
		#else
		int status = pclose(this->fprocess);
		#endif	
		
		if (status != 0) {
			throw std::runtime_error("Could not close the pipe stream");
		}
		
		this->fprocess = nullptr;
	}
}

bool opstreambuf::is_open() const{
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

opstream::opstream()
	: std::ostream(&this->buf)
	, buf() {}

opstream::opstream(char const * process) 
	: std::ostream(&this->buf)
	, buf(process){}
	
opstream::opstream(opstream&& other) noexcept  
	: std::ostream(&this->buf) {
	this->buf = std::move(other.buf);
}

opstream& opstream::operator=(opstream&& other) noexcept {
	if(this != &other){
		this->buf = std::move(other.buf);
		this->rdbuf(&this->buf);
		other.rdbuf(nullptr);
	}
	return *this;
}	

void opstream::open(char const* process){
	this->buf.open(process);
}
	
void opstream::close(){
	this->buf.close();
}

bool opstream::is_open() const{
	return this->buf.is_open();
}
