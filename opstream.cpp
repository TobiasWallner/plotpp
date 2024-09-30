#include "opstream.hpp"

//
// Stream Buffer Functions
//

opstreambuf::opstreambuf(char const * process) {
	#ifdef WIN32
	fprocess = _popen(process, "w");
	#elif 
	fprocess = popen(process, "w");
	#endif
	if(process == nullptr){
		std::string s;
		s += "failed: process = popen(process, \"w\");";

	}
	setp(buffer, buffer + sizeof(buffer) - 1); // Reserve space for a null terminator
}

opstreambuf::~opstreambuf(){
	#ifdef WIN32
	_pclose(fprocess);
	#elif 
	pclose(fprocess);
	#endif
}

int opstreambuf::sync() {
	std::streamsize num = pptr() - pbase();
	if (num > 0) {
		fwrite(pbase(), sizeof(char), num, fprocess);
		pbump(-num); 
	}
	return num == EOF ? -1 : 0;;
}

//
// Stream Object Functions
//

opstream::opstream(char const * process) 
	: std::ostream(&buf)
	, buf(process){}