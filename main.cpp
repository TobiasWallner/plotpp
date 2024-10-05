#include "opstream.hpp"
#include <iostream>
#include <fstream>
#include <iterator>
#include <type_traits>
#include <utility>
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
	NONE,
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
		case Terminal::NONE : {
			std::stringstream message;
			message << "Error in funtion: " << __FUNCTION__ << "\n"
					<< "  in file: " << __FILE__ << "\n"
					<< "  at line: " << __LINE__ << "\n"
					<< "  message: NONE is not a valid terminal\n";
			throw std::runtime_error(message.str());
		} break;
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

Terminal to_terminal(OutputFileType t){
	switch(t){
		case OutputFileType::NONE: return Terminal::NONE;
        case OutputFileType::tex:  return Terminal::cairolatex;
        case OutputFileType::cgm:  return Terminal::cgm;
        case OutputFileType::pdf:  return Terminal::pdfcairo;
        case OutputFileType::dxf:  return Terminal::dxf;
        case OutputFileType::emf:  return Terminal::emf;
        case OutputFileType::eps:  return Terminal::epscairo;
        case OutputFileType::fig:  return Terminal::fig;
        case OutputFileType::gif:  return Terminal::gif;
        case OutputFileType::jpeg: return Terminal::jpeg;
        case OutputFileType::png:  return Terminal::png;
        case OutputFileType::svg:  return Terminal::svg;
        case OutputFileType::webp: return Terminal::webp;
        case OutputFileType::html: return Terminal::canvas;
        case OutputFileType::txt:  return Terminal::dumb;
		case OutputFileType::gp:   return Terminal::NONE;
	}
	std::stringstream message;
	message << "Error in funtion: " << __FUNCTION__ << "\n"
			<< "  in file: " << __FILE__ << "\n"
			<< "  at line: " << __LINE__ << "\n"
			<< "  message: missing switch case\n";
	throw std::runtime_error(message.str());
}

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

class IPlot{
public:
	IPlot() = default;
	IPlot(Text title) : title(std::move(title)){}
	virtual ~IPlot(){}
	
	virtual void print_config(std::ostream& stream) const = 0;
	virtual void print_data(std::ostream& stream) const  = 0;
	
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
	
	void show(OutputFileType filetype){
		if(filetype == OutputFileType::gp){
			_plot(std::cout, Terminal::NONE);
		}else{
			show(to_terminal(filetype));
		}
	}
	
	void show(Terminal terminal = Terminal::NONE){
		opstream gnuplot("gnuplot -persist");
		_plot(gnuplot, terminal);
	}
	
	void save(std::string filename = "", OutputFileType filetype=OutputFileType::NONE, Terminal terminal = Terminal::NONE){
		if(filename.empty()) filename = title;
		
		if(filetype == OutputFileType::NONE){
			filetype = filetype_from_filename(filename);
			if(filetype == OutputFileType::NONE){
				filetype = OutputFileType::png;
				filename += ".png";
			}
		}else if(!filename.ends_with(std::string(to_file_ending(filetype)))){
				filename += to_file_ending(filetype);
		}
		
		if(terminal == Terminal::NONE){
			terminal = to_terminal(filetype);	
		}
		
		if(filetype==OutputFileType::gp){
			std::ofstream fstream(filename);
			_plot(fstream, terminal);
		}else{
			opstream gnuplot("gnuplot -persist");
			_plot(gnuplot, terminal, filename);	
		}
	}

public:
	void _plot(
		std::ostream& stream, 
		Terminal terminal = Terminal::NONE,
		std::string saveAs = "")
	{
		if(!title.empty()) stream << "set title " << title << "\n";
		if(terminal != Terminal::NONE) stream << "set terminal " << to_command(terminal) << "\n";
		if(!saveAs.empty()) stream << "set output '" << saveAs << "'\n";
		if(!xlabel.empty()) stream << "set xlabel " << xlabel << "\n";
		if(!ylabel.empty()) stream << "set ylabel " << ylabel << "\n";
		
		if(!this->plots.empty()) stream << "plot ";
		for(size_t i=0; i < this->plots.size(); ++i){
			if (i!= 0) stream << '\t';
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

template<class Container>
class LinePlot : public IPlot{
public:
	Container x;
	Container y;
	
	DashType dashType = DashType::solid;
	float lineWidth = 1.5;
	/*TODO: LineColor*/
	
public:
	
	LinePlot(Container x, Container y, Text title="")
		: IPlot(std::move(title))
		, x(std::move(x))
		, y(std::move(y))
	{}
	
	LinePlot(LinePlot const &) = default;
	LinePlot(LinePlot&&) = default;
	LinePlot& operator=(LinePlot const &) = default;
	LinePlot& operator=(LinePlot&&) = default;
	
	
	virtual void print_config(std::ostream& stream) const {
		stream << "'-' using 1:2 with lines lw " << this->lineWidth << " " 
				<< to_command(this->dashType) << " title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data(std::ostream& stream) const {
		stream << "# Data for " << this->IPlot::title.str << "\n";
		auto xItr = std::begin(x);
		auto yItr = std::begin(y);
		for (; xItr != std::end(x) && yItr != std::end(y); (void)++xItr, (void)++yItr) {
			stream << *xItr << ' ' << *yItr << "\n";
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

template<class Container>
class PointPlot : public IPlot{
public:
	Container x;
	Container y;
	PointType pointType = PointType::CircleFilled;
	float pointSize = 1.0;
	/*TODO: LineColor*/
	
public:

	PointPlot(Container x, Container y, Text title="")
		: IPlot(std::move(title))
		, x(std::move(x))
		, y(std::move(y))
	{}
	
	PointPlot(PointPlot const &) = default;
	PointPlot(PointPlot&&) = default;
	PointPlot& operator=(PointPlot const &) = default;
	PointPlot& operator=(PointPlot&&) = default;
	
	
	virtual void print_config(std::ostream& stream) const {
		stream << "'-' using 1:2 with points ps " << this->pointSize 
				<< " pt " << static_cast<int>(pointType)
				<< " title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data(std::ostream& stream) const {
		stream << "# Data for " << this->IPlot::title.str << "\n";
		for (size_t i = 0; i < std::min(x.size(), y.size()); ++i) {
			stream << x[i] << ' ' << y[i] << "\n";
		}
		stream << "e\n";
	}
};

enum class ImageFileType{
	NONE,
	png, 
	jpeg,
	webp,
	gif,
};

std::string_view to_string(ImageFileType filetype){
	switch(filetype){
		case ImageFileType::NONE : {
			std::stringstream message;
			message << "Error in funtion: " << __FUNCTION__ << "\n"
					<< "  in file: " << __FILE__ << "\n"
					<< "  at line: " << __LINE__ << "\n"
					<< "  message: NONE is not a valid filetype\n";
			throw std::runtime_error(message.str());
		} break;
		case ImageFileType::png : return "png";
		case ImageFileType::jpeg : return "jpeg";
		case ImageFileType::webp : return "webp";
		case ImageFileType::gif : return "gif";
	}
	std::stringstream message;
	message << "Error in funtion: " << __FUNCTION__ << "\n"
			<< "  in file: " << __FILE__ << "\n"
			<< "  at line: " << __LINE__ << "\n"
			<< "  message: missing switch case\n";
	throw std::runtime_error(message.str());
}

ImageFileType image_filetype_from_filename(std::string_view filename){
	if(filename.ends_with(".png"))       return ImageFileType::png;
	else if(filename.ends_with(".jpeg")) return ImageFileType::jpeg;
	else if(filename.ends_with(".jpg"))  return ImageFileType::jpeg;
	else if(filename.ends_with(".webp")) return ImageFileType::webp;
	else if(filename.ends_with(".gif"))  return ImageFileType::gif;
	else                                 return ImageFileType::NONE;
}

class ImageFilePlot : public IPlot {
	public:
	std::string filename;
	ImageFileType filetype;
	
	ImageFilePlot(std::string filename, Text title="")
		: IPlot(std::move(title))
		, filename(std::move(filename))
		, filetype(image_filetype_from_filename(this->filename))
	{
		if(filetype == ImageFileType::NONE){
			std::stringstream message;
			message << "Error in funtion: " << __FUNCTION__ << "\n"
					<< "  in file: " << __FILE__ << "\n"
					<< "  at line: " << __LINE__ << "\n"
					<< "  message: NONE is not a valid filetype\n";
			throw std::runtime_error(message.str());
		}
	}
	
	ImageFilePlot(std::string filename, ImageFileType filetype, Text title = "")
		: IPlot(std::move(title))
		, filename(std::move(filename))
		, filetype((filetype == ImageFileType::NONE) ? image_filetype_from_filename(filename) : filetype)
	{
		if(filetype == ImageFileType::NONE){
			std::stringstream message;
			message << "Error in funtion: " << __FUNCTION__ << "\n"
					<< "  in file: " << __FILE__ << "\n"
					<< "  at line: " << __LINE__ << "\n"
					<< "  message: NONE is not a valid filetype\n";
			throw std::runtime_error(message.str());
		}
	}
	
	virtual void print_config(std::ostream& stream) const {
		stream << " '" << this->filename << "' binary filetype=" << to_string(this->filetype) 
				<< " with rgbalpha title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data([[maybe_unused]]std::ostream& stream) const {}
	
};

template<class T, size_t ROWS=0, size_t COLS=0>
class HeatmapPlot : public IPlot{
	const T (&_matrix)[ROWS][COLS];
public:
	
	HeatmapPlot(const T (&array)[ROWS][COLS], Text title)
		: IPlot(std::move(title))
		, _matrix(array)
	{}
	
	virtual void print_config(std::ostream& stream) const {
		stream << "'-' matrix using 2:1:3 with image title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data(std::ostream& stream) const {
		stream << "# Data for " << this->IPlot::title.str << "\n";
		for(size_t col=0; col < COLS; ++col){
			for(size_t row=0; row < ROWS; ++row){
				stream << _matrix[row][col] << ' ';
			}
			stream << '\n';
		}
		stream << "e\n";
	}
	
};

template<class T>
class HeatmapPlot<T, 0, 0> : public IPlot{
	T const & _matrix = nullptr;
	size_t _rows = 0;
	size_t _columns = 0;
	double (*_at)(T const * matrix, size_t row, size_t col);
	
public:

	HeatmapPlot(T const & matrix, size_t rows, size_t columns, double (*at)(T const & matrix, size_t row, size_t col), Text title="")
		: IPlot(std::move(title))
		, _matrix(matrix)
		, _rows(rows)
		, _columns(columns)
		, _at(at)
	{}
	
	virtual void print_config(std::ostream& stream) const {
		stream << "'-' matrix using 2:1:3 with image title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data(std::ostream& stream) const {
		stream << "# Data for " << this->IPlot::title.str << "\n";
		for(size_t col=0; col < this->_columns; ++col){
			for(size_t row=0; row < this->_rows; ++row){
				stream << (this->_at)(this->_matrix, row, col) << ' ';
			}
			stream << '\n';
		}
		stream << "e\n";
	}
	
};

enum class DataRelation{
	absolute,
	relative,
	polar,
};

enum class ArrowHeadStyle{
	nohead,
	head,
	filled_head,
	empty_head,
	backhead,
	filled_backhead,
	empty_backhead,
};

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

template<class T>
class ArrowPlot : public IPlot{
public:

	T const & x1;
	T const & y1;
	T const & x2;
	T const & y2;
	DataRelation dataRelation = DataRelation::absolute; // relation from [x1, y1] to [x2, y2]
	float lineWidth = 1.5;
	ArrowHeadStyle arrowHeadStyle = ArrowHeadStyle::filled_head;
	
	ArrowPlot(T const & x1, T const & y1, T const & x2, T const & y2, Text title="")
		: IPlot(std::move(title))
		, x1(x1)
		, y1(y1)
		, x2(x2)
		, y2(y2)
	{}
	
	virtual void print_config(std::ostream& stream) const {
		stream << "'-' using";
		if(dataRelation == DataRelation::absolute){
			stream << " 1:2:(($3)-($1)):($4-$2)";
		}else{
			stream << " 1:2:3:4";
		}
		
		if(dataRelation == DataRelation::polar){
			stream << " with arrows";
		}else{
			stream << " with vectors";
		}
		
		stream << " " << to_command(arrowHeadStyle);
		stream << " lw " << lineWidth;
		stream << " title '" << this->IPlot::title.str << "'";	
	}
	
	virtual void print_data(std::ostream& stream) const {
		stream << "# Data for " << this->IPlot::title.str << "\n";
		auto x1itr = std::begin(x1);
		auto y1itr = std::begin(y1);
		auto x2itr = std::begin(x2);
		auto y2itr = std::begin(y2);
		for(; x1itr != std::end(x1) && y1itr != std::end(y1) && x2itr != std::end(x2) && y2itr != std::end(y2)
			; (void)++x1itr, (void)++y1itr, (void)++x2itr, (void)++y2itr){
			stream << *x1itr << ' ' << *y1itr << ' ' << *x2itr << ' ' << *y2itr << '\n';
		}
		stream << "e\n";
	}
};

// http://gnuplot.info/docs/Overview.html

// TODO: put classes and functions into their own files
// TODO: put opstream into its own GitHub repo

/* 	
http://gnuplot.info/docs/Plotting_Styles.html

	+ 2D Plots TODO:
		* Bee swarm plots
		* box error bars
		* 2d boxes
		* boxplotsx
		* candlesticks
		* pichart
		* filledcurves 
		* linespoints
		* redo xy-plots
			- (lines, points, linespoints, filledcurves, fillsteps, fsteps... - should all be the same class)
				- option: filled -> filledcurves
				- option: O1_interpolation -> lines
				- option: O0_interpolation_start -> fsteps
					- option: O0_interpolation_center -> histeps
				- option: impulses -> impulses
		* parallelaxes
		
	
	+ 3D Plots TODO:
		* 3D xyz plot
		* 3D boxes
		* contourfill
		


*/

template<size_t c, size_t r>
double at(double const (*array)[r][c], size_t row, size_t col){
	return (*array)[row][col];
}

int main() {
	
	std::vector<double> x(20);
	for(size_t i=0; i < x.size(); ++i) x[i] = i;
	
	std::vector<double> y1(20);
	for(size_t i=0; i < y1.size(); ++i) y1[i] = 1./i*30;
	
	std::vector<double> y2(20);
	for(size_t i=0; i < y2.size(); ++i) y2[i] = 1./(i*i)*30;
	
	double array[/*rows*/4][/*columns*/3] = {
		{1, 2, 3},
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33}
	};

	double arrow_x1[] = {-1, -2, -3, -4, -5};
	double arrow_y1[] = {-1, -2, -1, -2, -3};
	double arrow_x2[] = {-2, -3, -4, -5, -6};
	double arrow_y2[] = {-3, -4, -2, -3, -5};
	
	Figure fig("Title");
	fig.legend = true;
	
	fig.add(ImageFilePlot("test_image_32x32.png"));
	fig.add(HeatmapPlot(array, "Heatmap"));
	fig.add(LinePlot(x, y1, "1/x*30"));
	fig.add(PointPlot(x, y2, "1/x^2*30"));
	
	auto arrowplot = ArrowPlot(arrow_x1, arrow_y1, arrow_x2, arrow_y2, "arrow plot");
	arrowplot.dataRelation = DataRelation::relative;
	fig.add(arrowplot);
	
	fig.show();
	fig.save("script.gp");
	
	
    return 0;
}