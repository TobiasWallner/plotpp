#pragma once

#include <string>
#include <ostream>

namespace plotpp{

	class Text{
		public:
		
		std::string str = "";
		unsigned int height = 18;
		bool bold = false;
		bool italic = false;
		
		Text() = default;
		Text(std::string str) 
			: str(std::move(str)){}
			
		Text(const char* str) 
			: str(str){}
		
		Text(const Text&) = default;
		Text(Text&&) = default;
		
		Text& operator=(const Text&) = default;
		Text& operator=(Text&&) = default;
					  
		Text& operator=(const std::string str){this->str = str; return *this;}
		
		inline bool empty() const {return this->str.empty();}
		
		operator std::string () const {
			return this->str;
		}
	};

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