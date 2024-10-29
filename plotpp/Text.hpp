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
		Text(std::string str);
			
		Text(const char* str);
		
		Text(const Text&) = default;
		Text(Text&&) = default;
		
		Text& operator=(const Text&) = default;
		Text& operator=(Text&&) = default;
					  
		Text& operator=(const std::string str);
		
		bool empty() const;

		operator std::string () const;
	};

	std::ostream& operator<<(std::ostream& stream, const Text& text);
}