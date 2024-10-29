#include "plotpp/TerminalType.hpp"

#include <string_view>
#include <sstream>

namespace plotpp{

std::string_view to_command(TerminalType t){
	switch(t){
		case TerminalType::NONE : {
			std::stringstream message;
			message << "Error in funtion: " << __FUNCTION__ << "\n"
					<< "  in file: " << __FILE__ << "\n"
					<< "  at line: " << __LINE__ << "\n"
					<< "  message: NONE is not a valid TerminalType\n";
			throw std::runtime_error(message.str());
		} break;
		case TerminalType::cairolatex : return "cairolatex";
		case TerminalType::canvas : return "canvas";
		case TerminalType::cgm : return "cgm";
		case TerminalType::context : return "context";
		case TerminalType::domterm : return "domterm";
		case TerminalType::txt : return "dumb";
		case TerminalType::dumb : return "dumb";
		case TerminalType::dxf : return "dxf";
		case TerminalType::emf : return "emf";
		case TerminalType::epscairo : return "epscairo";
		case TerminalType::epslatex : return "epslatex";
		case TerminalType::fig : return "fig";
		case TerminalType::gif : return "gif";
		case TerminalType::hpgl : return "hpgl";
		case TerminalType::jpeg : return "jpeg";
		case TerminalType::kittycairo : return "kittycairo";
		case TerminalType::kittygd : return "kittygd";
		case TerminalType::lua : return "lua";
		case TerminalType::pcl5 : return "pcl5";
		case TerminalType::pdfcairo : return "pdfcairo";
		case TerminalType::pict2e : return "pict2e";
		case TerminalType::png : return "png";
		case TerminalType::pngcairo : return "pngcairo";
		case TerminalType::postscript : return "postscript";
		case TerminalType::pslatex : return "pslatex";
		case TerminalType::pstex : return "pstex";
		case TerminalType::pstricks : return "pstricks";
		case TerminalType::qt : return "qt";
		case TerminalType::sixelgd : return "sixelgd";
		case TerminalType::svg : return "svg";
		case TerminalType::texdraw : return "texdraw";
		case TerminalType::tikz : return "tikz";
		case TerminalType::tkcanvas : return "tkcanvas";
		case TerminalType::unknown : return "unknown";
		case TerminalType::webp : return "webp";
		case TerminalType::windows : return "windows";
		case TerminalType::wxt : return "wxt";
	}
	std::stringstream message;
	message << "Error in funtion: " << __FUNCTION__ << "\n"
			<< "  in file: " << __FILE__ << "\n"
			<< "  at line: " << __LINE__ << "\n"
			<< "  message: missing switch case\n";
	throw std::runtime_error(message.str());
}

}