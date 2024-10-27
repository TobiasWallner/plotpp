#pragma once

#include <string_view>
#include <sstream>

namespace plotpp{

enum class TerminalType{
	NONE,
	cairolatex, 	// LaTeX picture environment using graphicx package and Cairo backend
	canvas, 		// HTML Canvas object
	cgm, 			// Computer Graphics Metafile
	context, 		// ConTeXt with MetaFun (for PDF documents)
	domterm, 		// DomTerm TerminalType emulator with embedded SVG
	dumb, txt,		// ascii art for anything that prints text
	dxf, 			// dxf-file for AutoCad (default size 120x80)
	emf, 			// Enhanced Metafile format
	epscairo, 		// eps TerminalType based on cairo
	epslatex, 		// LaTeX picture environment using graphicx package
	fig, 			// FIG graphics language V3.2 for XFIG graphics editor
	gif, 			// GIF images using libgd and TrueType fonts
	hpgl, 			// HP7475 and relatives [number of pens] [eject]
	jpeg, 			// JPEG images using libgd and TrueType fonts
	kittycairo, 	// kitty in-TerminalType graphics using cairo
	kittygd, 		// kitty in-TerminalType graphics using libgd
	lua, 			// Lua generic TerminalType driver
	pcl5, 			// PCL5e/PCL5c printers using HP-GL/2
	pdfcairo, 		// pdf TerminalType based on cairo
	pict2e, 		// LaTeX2e picture environment
	png, 			// PNG images using libgd and TrueType fonts
	pngcairo, 		// png TerminalType based on cairo
	postscript, 	// PostScript graphics, including EPSF embedded files (*.eps)
	pslatex, 		// LaTeX picture environment with PostScript \specials
	pstex, 			// plain TeX with PostScript \specials
	pstricks, 		// LaTeX picture environment with PSTricks macros
	qt, 			// Qt cross-platform interactive TerminalType
	sixelgd, 		// sixel using libgd and TrueType fonts
	svg, 			// W3C Scalable Vector Graphics
	texdraw, 		// LaTeX texdraw environment
	tikz, 			// TeX TikZ graphics macros via the lua script driver
	tkcanvas, 		// Tk canvas widget
	unknown, 		// Unknown TerminalType type - not a plotting device
	webp, 			// single frame or animation using cairo, pango, and libwebp
	windows, 		// Microsoft Windows
	wxt, 			// wxWidgets cross-platform interactive TerminalType
};

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