#include "opstream.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <memory>
#include <utility>

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

enum class Terminal{
	Default,
	cairolatex, 	// LaTeX picture environment using graphicx package and Cairo backend
	canvas, 		// HTML Canvas object
	cgm, 			// Computer Graphics Metafile
	context, 		// ConTeXt with MetaFun (for PDF documents)
	domterm, 		// DomTerm terminal emulator with embedded SVG
	dumb, txt,		// ascii art for anything that prints text
	dxf, 			// dxf-file for AutoCad (default size 120x80)
	emf, 			// Enhanced Metafile format
	epscairo, 		// eps terminal based on cairo
	epslatex, 		// LaTeX picture environment using graphicx package
	fig, 			// FIG graphics language V3.2 for XFIG graphics editor
	gif, 			// GIF images using libgd and TrueType fonts
	hpgl, 			// HP7475 and relatives [number of pens] [eject]
	jpeg, 			// JPEG images using libgd and TrueType fonts
	kittycairo, 	// kitty in-terminal graphics using cairo
	kittygd, 		// kitty in-terminal graphics using libgd
	lua, 			// Lua generic terminal driver
	pcl5, 			// PCL5e/PCL5c printers using HP-GL/2
	pdfcairo, 		// pdf terminal based on cairo
	pict2e, 		// LaTeX2e picture environment
	png, 			// PNG images using libgd and TrueType fonts
	pngcairo, 		// png terminal based on cairo
	postscript, 	// PostScript graphics, including EPSF embedded files (*.eps)
	pslatex, 		// LaTeX picture environment with PostScript \specials
	pstex, 			// plain TeX with PostScript \specials
	pstricks, 		// LaTeX picture environment with PSTricks macros
	qt, 			// Qt cross-platform interactive terminal
	sixelgd, 		// sixel using libgd and TrueType fonts
	svg, 			// W3C Scalable Vector Graphics
	texdraw, 		// LaTeX texdraw environment
	tikz, 			// TeX TikZ graphics macros via the lua script driver
	tkcanvas, 		// Tk canvas widget
	unknown, 		// Unknown terminal type - not a plotting device
	webp, 			// single frame or animation using cairo, pango, and libwebp
	windows, 		// Microsoft Windows
	wxt, 			// wxWidgets cross-platform interactive terminal
};


std::string_view to_command(Terminal t){
	switch(t){
		case Terminal::Default : return "";
		case Terminal::cairolatex : return "cairolatex";
		case Terminal::canvas : return "canvas";
		case Terminal::cgm : return "cgm";
		case Terminal::context : return "context";
		case Terminal::domterm : return "domterm";
		case Terminal::txt : return "dumb";
		case Terminal::dumb : return "dumb";
		case Terminal::dxf : return "dxf";
		case Terminal::emf : return "emf";
		case Terminal::epscairo : return "epscairo";
		case Terminal::epslatex : return "epslatex";
		case Terminal::fig : return "fig";
		case Terminal::gif : return "gif";
		case Terminal::hpgl : return "hpgl";
		case Terminal::jpeg : return "jpeg";
		case Terminal::kittycairo : return "kittycairo";
		case Terminal::kittygd : return "kittygd";
		case Terminal::lua : return "lua";
		case Terminal::pcl5 : return "pcl5";
		case Terminal::pdfcairo : return "pdfcairo";
		case Terminal::pict2e : return "pict2e";
		case Terminal::png : return "png";
		case Terminal::pngcairo : return "pngcairo";
		case Terminal::postscript : return "postscript";
		case Terminal::pslatex : return "pslatex";
		case Terminal::pstex : return "pstex";
		case Terminal::pstricks : return "pstricks";
		case Terminal::qt : return "qt";
		case Terminal::sixelgd : return "sixelgd";
		case Terminal::svg : return "svg";
		case Terminal::texdraw : return "texdraw";
		case Terminal::tikz : return "tikz";
		case Terminal::tkcanvas : return "tkcanvas";
		case Terminal::unknown : return "unknown";
		case Terminal::webp : return "webp";
		case Terminal::windows : return "windows";
		case Terminal::wxt : return "wxt";
	}
	std::stringstream message;
	message << "Error in funtion: " << __FUNCTION__ << "\n"
			<< "  in file: " << __FILE__ << "\n"
			<< "  at line: " << __LINE__ << "\n"
			<< "  message: missing switch case\n";
	throw std::runtime_error(message.str());
}

enum class SaveAsFileType{
	Default, 
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
};

Terminal to_terminal(SaveAsFileType t){
	switch(t){
		case SaveAsFileType::Default: return Terminal::Default;
        case SaveAsFileType::tex: return Terminal::cairolatex;
        case SaveAsFileType::cgm: return Terminal::cgm;
        case SaveAsFileType::pdf: return Terminal::pdfcairo;
        case SaveAsFileType::dxf: return Terminal::dxf;
        case SaveAsFileType::emf: return Terminal::emf;
        case SaveAsFileType::eps: return Terminal::epscairo;
        case SaveAsFileType::fig: return Terminal::fig;
        case SaveAsFileType::gif: return Terminal::gif;
        case SaveAsFileType::jpeg: return Terminal::jpeg;
        case SaveAsFileType::png: return Terminal::png;
        case SaveAsFileType::svg: return Terminal::svg;
        case SaveAsFileType::webp: return Terminal::webp;
        case SaveAsFileType::html: return Terminal::canvas;
        case SaveAsFileType::txt: return Terminal::dumb;
	}
	std::stringstream message;
	message << "Error in funtion: " << __FUNCTION__ << "\n"
			<< "  in file: " << __FILE__ << "\n"
			<< "  at line: " << __LINE__ << "\n"
			<< "  message: missing switch case\n";
	throw std::runtime_error(message.str());
}

std::string_view to_file_ending(SaveAsFileType t){
	switch(t){
		case SaveAsFileType::Default : return "";
        case SaveAsFileType::tex: return ".tex";
        case SaveAsFileType::cgm: return ".cgm";
        case SaveAsFileType::pdf: return ".pdf";
        case SaveAsFileType::dxf: return ".dxf";
        case SaveAsFileType::emf: return ".emf";
        case SaveAsFileType::eps: return ".eps";
        case SaveAsFileType::fig: return ".fig";
        case SaveAsFileType::gif: return ".gif";
        case SaveAsFileType::jpeg: return ".jpeg";
        case SaveAsFileType::png: return ".png";
        case SaveAsFileType::svg: return ".svg";
        case SaveAsFileType::webp: return ".webp";
		case SaveAsFileType::html: return ".html";
        case SaveAsFileType::txt: return ".txt";
	}
	std::stringstream message;
	message << "Error in funtion: " << __FUNCTION__ << "\n"
			<< "  in file: " << __FILE__ << "\n"
			<< "  at line: " << __LINE__ << "\n"
			<< "  message: missing switch case\n";
	throw std::runtime_error(message.str());
}

SaveAsFileType from_filename(std::string_view filename){
	if(filename.ends_with(to_file_ending(SaveAsFileType::tex)))       return SaveAsFileType::tex;
	else if(filename.ends_with(".cgm"))  return SaveAsFileType::cgm;
	else if(filename.ends_with(".pdf"))  return SaveAsFileType::pdf;
	else if(filename.ends_with(".dxf"))  return SaveAsFileType::dxf;
	else if(filename.ends_with(".emf"))  return SaveAsFileType::emf;
	else if(filename.ends_with(".eps"))  return SaveAsFileType::eps;
	else if(filename.ends_with(".fig"))  return SaveAsFileType::fig;
	else if(filename.ends_with(".gif"))  return SaveAsFileType::gif;
	else if(filename.ends_with(".jpg")) return SaveAsFileType::jpeg;
	else if(filename.ends_with(".jpeg")) return SaveAsFileType::jpeg;
	else if(filename.ends_with(".png"))  return SaveAsFileType::png;
	else if(filename.ends_with(".svg"))  return SaveAsFileType::svg;
	else if(filename.ends_with(".webp")) return SaveAsFileType::webp;
	else if(filename.ends_with(".html")) return SaveAsFileType::html;
	else if(filename.ends_with(".txt"))  return SaveAsFileType::txt;
	else return SaveAsFileType::Default;
}

enum class DashType{
	solid,
	dashed,
	doted,
	dash_doted,
	dash_doted2
};

std::string_view to_command(DashType dt){
	switch(dt){
		case DashType::solid: return "dt 1";
		case DashType::dashed: return "dt 2";
		case DashType::doted: return "dt 3";
		case DashType::dash_doted: return "dt 4";
		case DashType::dash_doted2: return "dt 5";
	}
	std::stringstream message;
	message << "Error in funtion: " << __FUNCTION__ << "\n"
			<< "  in file: " << __FILE__ << "\n"
			<< "  at line: " << __LINE__ << "\n"
			<< "  message: missing switch case\n";
	throw std::runtime_error(message.str());
}

enum class PlotType{
	LinePlot,
	PointPlot,
};

class IPlot{
public:
	IPlot(PlotType pt) 
		: plotType(pt)
	{}
	
	IPlot(PlotType pt, Text title) 
		: plotType(pt)
		, title(title)
	{}

	virtual ~IPlot(){}
	
	virtual void print_config(std::ostream& stream) = 0;
	virtual void print_data(std::ostream& stream) = 0;
	
	PlotType plotType;
	Text title;
};

class Figure{
public:
	std::vector<std::unique_ptr<IPlot>> plots;
	
public:
	Text title;
	Text xlabel;
	Text ylabel;
	bool legend = false;
	
	template<class T>
	Figure& add(std::unique_ptr<T>&& plot){
		std::unique_ptr<IPlot> p = std::move(plot);
		this->plots.push_back(std::move(plot));
		return *this;
	}
	
	/*TODO: Add enable if*/
	template<class T>
	Figure& add(T&& plot){
		using rrT = std::remove_reference_t<T>;
		std::unique_ptr<IPlot> p = std::make_unique<rrT>(std::forward<rrT>(plot));
		this->plots.emplace_back(std::move(p));
		return *this;
	}
	
	Figure(std::string title_str=""){
		title.str = title_str;
		title.height = 20;
		title.bold = true;
	}
	
	Figure(Text title, Text xlabel, Text ylabel)
		: title(title)
		, xlabel(xlabel)
		, ylabel(ylabel)
	{}
	
	void show(Terminal terminal = Terminal::Default, bool debug=false){
		if(debug){
			_plot(std::cout, terminal);
		}else{
			opstream gnuplot("gnuplot -persist");
			_plot(gnuplot, terminal);
		}
	}
	
	void save(std::string filename = "", SaveAsFileType filetype=SaveAsFileType::Default, Terminal terminal = Terminal::Default){
		if(filename.empty()) filename = title;
		
		if(filetype == SaveAsFileType::Default){
			filetype = from_filename(filename);
			if(filetype == SaveAsFileType::Default){
				filetype = SaveAsFileType::png;
				filename += ".png";
			}
		}else if(!filename.ends_with(std::string(to_file_ending(filetype)))){
				filename += to_file_ending(filetype);
		}
		
		if(terminal == Terminal::Default){
			terminal = to_terminal(filetype);	
		}
		
		opstream gnuplot("gnuplot -persist");
		_plot(gnuplot, terminal, filename);
	}

protected:
	void _plot(
		std::ostream& stream, 
		Terminal terminal = Terminal::Default,
		std::string saveAs = "")
	{
		if(!title.empty()) stream << "set title " << title << "\n";
		if(terminal != Terminal::Default) stream << "set terminal " << to_command(terminal) << "\n";
		if(!saveAs.empty()) stream << "set output '" << saveAs << "'\n";
		if(!xlabel.empty()) stream << "set xlabel " << xlabel << "\n";
		if(!ylabel.empty()) stream << "set ylabel " << ylabel << "\n";
		
		if(!this->plots.empty()) stream << "plot ";
		for(size_t i=0; i < this->plots.size(); ++i){
			plots[i]->print_config(stream);
			if(i+1 < this->plots.size()) stream << ", \\\n";
		}
		
		for(size_t i=0; i < this->plots.size(); ++i){
			stream << "\n";
			plots[i]->print_data(stream);
		}
		
		if(!saveAs.empty()) stream << "set output\n"; // reset to default
		
		stream.flush();
	}
};


class LinePlot : public IPlot{
public:
	std::vector<double> x;
	std::vector<double> y;
	DashType dashType = DashType::solid;
	float lineWidth = 1.5;
	/*TODO: LineColor*/
	
public:
	
	LinePlot(std::vector<double> x, std::vector<double> y)
		: IPlot(PlotType::LinePlot)
		, x(std::move(x))
		, y(std::move(y))
		{}
		
	LinePlot(std::vector<double> x, std::vector<double> y, Text title)
		: IPlot(PlotType::LinePlot, title)
		, x(std::move(x))
		, y(std::move(y))
	{}
	
	LinePlot(std::vector<double> x, std::vector<double> y, const char* title)
		: IPlot(PlotType::LinePlot, title)
		, x(std::move(x))
		, y(std::move(y))
	{}
	
	LinePlot(LinePlot const &) = default;
	LinePlot(LinePlot&&) = default;
	LinePlot& operator=(LinePlot const &) = default;
	LinePlot& operator=(LinePlot&&) = default;
	
	
	virtual void print_config(std::ostream& stream) {
		stream << " '-' using 1:2 with lines lw " << this->lineWidth << " " 
				<< to_command(this->dashType) << " title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data(std::ostream& stream){
		stream << "# Data for " << this->IPlot::title.str << "\n";
		for (size_t i = 0; i < std::min(x.size(), y.size()); ++i) {
			stream << x[i] << ' ' << y[i] << "\n";
		}
		stream << "e\n";
	}
};

enum class PointType : int {
	None = -1,
	SmallDot = 0,
	Plus = 1,
	X = 2,
	PlusX = 3,
	Square = 4,
	SquareFilled = 5,
	Circle = 6,
	CircleFilled = 7,
	TriangleUp = 8,
	TriangleUpFilled = 9,
	TriangleDown = 10,
	TriangleDownFilled = 11,
	Rhombus = 12,
	RhombusFilled = 13,
	Heptagon = 14,
	HeptagonFilled = 15
};

class PointPlot : public IPlot{
public:
	std::vector<double> x;
	std::vector<double> y;
	PointType pointType = PointType::CircleFilled;
	float pointSize = 1.0;
	/*TODO: LineColor*/
	
public:
	
	PointPlot(std::vector<double> x, std::vector<double> y)
		: IPlot(PlotType::PointPlot)
		, x(std::move(x))
		, y(std::move(y))
		{}
		
	PointPlot(std::vector<double> x, std::vector<double> y, Text title)
		: IPlot(PlotType::PointPlot, title)
		, x(std::move(x))
		, y(std::move(y))
	{}
	
	PointPlot(std::vector<double> x, std::vector<double> y, const char* title)
		: IPlot(PlotType::PointPlot, title)
		, x(std::move(x))
		, y(std::move(y))
	{}
	
	PointPlot(PointPlot const &) = default;
	PointPlot(PointPlot&&) = default;
	PointPlot& operator=(PointPlot const &) = default;
	PointPlot& operator=(PointPlot&&) = default;
	
	
	virtual void print_config(std::ostream& stream) {
		stream << " '-' using 1:2 with points ps " << this->pointSize 
				<< " pt " << static_cast<int>(pointType)
				<< " title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data(std::ostream& stream){
		stream << "# Data for " << this->IPlot::title.str << "\n";
		for (size_t i = 0; i < std::min(x.size(), y.size()); ++i) {
			stream << x[i] << ' ' << y[i] << "\n";
		}
		stream << "e\n";
	}
};

// http://gnuplot.info/docs/Overview.html

// TODO: put classes and functions into their own files
// TODO: put opstream into its own GitHub repo

int main() {
	
	std::vector<double> x(20);
	for(size_t i=0; i < x.size(); ++i) x[i] = i;
	
	std::vector<double> y1(20);
	for(size_t i=0; i < y1.size(); ++i) y1[i] = 1./i;
	
	std::vector<double> y2(20);
	for(size_t i=0; i < y2.size(); ++i) y2[i] = 1./(i*i);
	
	Figure fig("Title");
	fig.legend = true;
	fig.add(LinePlot(x, y1, "1/x"));
	fig.add(PointPlot(x, y2, "1/x^2"));
	fig.show();
	
    return 0;
}