#pragma once

namespace plotpp{

	enum class LineType{
		none,
		solid,
		dashed,
		doted,
		dash_doted,
		dash_doted2
	};

	std::string_view to_command(LineType dt){
		switch(dt){
			case LineType::none: return "dt -1";
			case LineType::solid: return "dt 1";
			case LineType::dashed: return "dt 2";
			case LineType::doted: return "dt 3";
			case LineType::dash_doted: return "dt 4";
			case LineType::dash_doted2: return "dt 5";
		}
		std::stringstream message;
		message << "Error in funtion: " << __FUNCTION__ << "\n"
				<< "  in file: " << __FILE__ << "\n"
				<< "  at line: " << __LINE__ << "\n"
				<< "  message: missing switch case\n";
		throw std::runtime_error(message.str());
	}

}