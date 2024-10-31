#include "opstream.hpp"
#include <iostream>

//
// Stream Buffer Functions
//

opstreambuf::opstreambuf(char const * process) {
	#ifdef WIN32
	fprocess = _popen(process, "w");
	#else
	fprocess = popen(process, "w");
	#endif
	if(process == nullptr){
		std::string s;
		s += "failed: process = popen(process, \"w\");"; 

	}
	setp(buffer, buffer + sizeof(buffer) - 1); // Reserve space for a null terminator
}

opstreambuf::~opstreambuf(){
	this->sync();
	#ifdef WIN32
	int status = _pclose(fprocess);
	#else
	int status = pclose(fprocess);
	#endif	
	if (status != 0) std::cerr << "Could not close the pipe stream" << std::endl;;
}

int opstreambuf::sync() {
	std::streamsize num = pptr() - pbase();
	if (num > 0) {
		size_t r = fwrite(pbase(), sizeof(char), num, fprocess);
		pbump(-num); 
		if(r != num){
			return -1; // error
		}
	}
	return 0;
}

int opstreambuf::overflow(int c) {
	int r = this->sync();
	if(r != 0) return -1; // error
	buffer[0] = static_cast<char>(c);
	pbump(1);
	return 0;
}

opstream::opstream(char const * process) 
	: std::ostream(&buf)
	, buf(process){}
