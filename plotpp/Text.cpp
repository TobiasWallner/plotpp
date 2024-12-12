#include "plotpp/Text.hpp"

#include <string>
#include <ostream>

#include <fmt/core.h>

namespace plotpp{

	Text::Text(std::string str) 
		: str(std::move(str)){}
		
	Text::Text(const char* str) 
		: str(str){}
				  
	Text& Text::operator=(const std::string str){this->str = str; return *this;}
	
	bool Text::empty() const {return this->str.empty();}
	
	Text::operator std::string () const {
		return this->str;
	}

	// std stream object
	std::ostream& operator<<(std::ostream& stream, const Text& text){
		stream << "'";
		if(text.italic) stream << "{/:Italic ";
		if(text.bold) stream << "{/:Bold ";
		stream << text.str;
		if(text.bold) stream << "}";
		if(text.italic) stream << "}";
		stream << "'" << " font \"" << "," << text.height << "\"";
		return stream;
	}
	
	
}