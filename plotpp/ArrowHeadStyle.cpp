#include "plotpp/ArrowHeadStyle.hpp"
#include <sstream>

namespace plotpp{
	
	std::string_view to_command(ArrowHeadStyle ahs){
		switch(ahs){
			case ArrowHeadStyle::nohead : return "nohead";
			case ArrowHeadStyle::head : return "head";
			case ArrowHeadStyle::filled_head : return "filled head";
			case ArrowHeadStyle::empty_head : return "empty head";
			case ArrowHeadStyle::backhead : return "backhead";
			case ArrowHeadStyle::filled_backhead : return "filled backhead";
			case ArrowHeadStyle::empty_backhead : return "empty backhead";
		}
		std::stringstream message;
		message << "Error in funtion: " << __FUNCTION__ << "\n"
				<< "  in file: " << __FILE__ << "\n"
				<< "  at line: " << __LINE__ << "\n"
				<< "  message: missing switch case\n";
		throw std::runtime_error(message.str());
	}
	
}