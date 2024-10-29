#pragma once

#include <string_view>

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

std::string_view to_command(TerminalType t);

}