#pragma once

#include <string_view>
#include <sstream>

#include "plotpp/TerminalType.hpp"


namespace plotpp{

	enum class OutputFileType{
		NONE, 
		tex, 
		cgm,
		pdf,
		dxf,
		emf,
		eps,
		fig,
		gif,
		jpeg,
		png,
		svg,
		webp,
		html,
		txt,
		gp, // gnuplot script
	};

	std::string_view to_file_ending(OutputFileType t);

	TerminalType to_terminal(OutputFileType t);

	OutputFileType filetype_from_filename(std::string_view filename);

}