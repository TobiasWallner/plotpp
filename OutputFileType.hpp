#pragma once

#include <string_view>

#include "TerminalType.hpp"


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

	std::string_view to_file_ending(OutputFileType t){
		switch(t){
			case OutputFileType::NONE : {
				std::stringstream message;
				message << "Error in funtion: " << __FUNCTION__ << "\n"
						<< "  in file: " << __FILE__ << "\n"
						<< "  at line: " << __LINE__ << "\n"
						<< "  message: NONE is not a valid filetype\n";
				throw std::runtime_error(message.str());
			} break;
	        case OutputFileType::tex: return ".tex";
	        case OutputFileType::cgm: return ".cgm";
	        case OutputFileType::pdf: return ".pdf";
	        case OutputFileType::dxf: return ".dxf";
	        case OutputFileType::emf: return ".emf";
	        case OutputFileType::eps: return ".eps";
	        case OutputFileType::fig: return ".fig";
	        case OutputFileType::gif: return ".gif";
	        case OutputFileType::jpeg: return ".jpeg";
	        case OutputFileType::png: return ".png";
	        case OutputFileType::svg: return ".svg";
	        case OutputFileType::webp: return ".webp";
			case OutputFileType::html: return ".html";
	        case OutputFileType::txt: return ".txt";
	        case OutputFileType::gp: return ".gp";
		}
		std::stringstream message;
		message << "Error in funtion: " << __FUNCTION__ << "\n"
				<< "  in file: " << __FILE__ << "\n"
				<< "  at line: " << __LINE__ << "\n"
				<< "  message: missing switch case\n";
		throw std::runtime_error(message.str());
	}

	TerminalType to_terminal(OutputFileType t){
		switch(t){
			case OutputFileType::NONE: return TerminalType::NONE;
	        case OutputFileType::tex:  return TerminalType::cairolatex;
	        case OutputFileType::cgm:  return TerminalType::cgm;
	        case OutputFileType::pdf:  return TerminalType::pdfcairo;
	        case OutputFileType::dxf:  return TerminalType::dxf;
	        case OutputFileType::emf:  return TerminalType::emf;
	        case OutputFileType::eps:  return TerminalType::epscairo;
	        case OutputFileType::fig:  return TerminalType::fig;
	        case OutputFileType::gif:  return TerminalType::gif;
	        case OutputFileType::jpeg: return TerminalType::jpeg;
	        case OutputFileType::png:  return TerminalType::png;
	        case OutputFileType::svg:  return TerminalType::svg;
	        case OutputFileType::webp: return TerminalType::webp;
	        case OutputFileType::html: return TerminalType::canvas;
	        case OutputFileType::txt:  return TerminalType::dumb;
			case OutputFileType::gp:   return TerminalType::NONE;
		}
		std::stringstream message;
		message << "Error in funtion: " << __FUNCTION__ << "\n"
				<< "  in file: " << __FILE__ << "\n"
				<< "  at line: " << __LINE__ << "\n"
				<< "  message: missing switch case\n";
		throw std::runtime_error(message.str());
	}

	OutputFileType filetype_from_filename(std::string_view filename){
		if(filename.ends_with(".tex"))       return OutputFileType::tex;
		else if(filename.ends_with(".cgm"))  return OutputFileType::cgm;
		else if(filename.ends_with(".pdf"))  return OutputFileType::pdf;
		else if(filename.ends_with(".dxf"))  return OutputFileType::dxf;
		else if(filename.ends_with(".emf"))  return OutputFileType::emf;
		else if(filename.ends_with(".eps"))  return OutputFileType::eps;
		else if(filename.ends_with(".fig"))  return OutputFileType::fig;
		else if(filename.ends_with(".gif"))  return OutputFileType::gif;
		else if(filename.ends_with(".jpg"))  return OutputFileType::jpeg;
		else if(filename.ends_with(".jpeg")) return OutputFileType::jpeg;
		else if(filename.ends_with(".png"))  return OutputFileType::png;
		else if(filename.ends_with(".svg"))  return OutputFileType::svg;
		else if(filename.ends_with(".webp")) return OutputFileType::webp;
		else if(filename.ends_with(".html")) return OutputFileType::html;
		else if(filename.ends_with(".txt"))  return OutputFileType::txt;
		else if(filename.ends_with(".gp"))   return OutputFileType::gp;
		else                                 return OutputFileType::NONE;
	}

}