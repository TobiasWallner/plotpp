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

#include "TerminalType.hpp"
#include "OutputFileType.hpp"
#include "PointType.hpp"
#include "LineType.hpp"
#include "ImageFileType.hpp"

#include "IPlot.hpp"
#include "Figure.hpp"
#include "Line.hpp"
#include "Points.hpp"
#include "ImageFile.hpp"
#include "Heatmap.hpp"

namespace plotpp{


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
class Arrows : public IPlot{
public:

	T const & x1;
	T const & y1;
	T const & x2;
	T const & y2;
	DataRelation dataRelation = DataRelation::absolute; // relation from [x1, y1] to [x2, y2]
	float lineWidth = 1.5;
	ArrowHeadStyle arrowHeadStyle = ArrowHeadStyle::filled_head;
	
	Arrows(T const & x1, T const & y1, T const & x2, T const & y2, Text title="")
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


template<class Container>
class XError : public IPlot{
public:
	const Container* x;
	const Container* y;
	const Container* xerror;
	PointType pointType = PointType::CircleFilled;
	float pointSize = 1.0;

	XError(const Container& x, const Container& y, const Container& xerror, Text title="")
		: IPlot(std::move(title))
		, x(&x)
		, y(&y)
		, xerror(&xerror)
	{}
	
	XError(XError const &) = default;
	XError(XError&&) = default;
	XError& operator=(XError const &) = default;
	XError& operator=(XError&&) = default;
	
	
	virtual void print_config(std::ostream& stream) const {
		stream << "'-' using 1:2:3 with xerrorbars";
		stream << " ps " << this->pointSize 
				<< " pt " << static_cast<int>(pointType)
				<< " title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data(std::ostream& stream) const {
		stream << "# Data for " << this->IPlot::title.str << "\n";
		auto xitr = std::begin(*x);
		auto yitr = std::begin(*y);
		auto xerrItr = std::begin(*xerror);
		
		const auto xEnd = std::end(*x);
		const auto yEnd = std::end(*y);
		const auto xerrEnd = std::end(*xerror);

		for (; xitr != xEnd && yitr != yEnd && xerrItr != xerrEnd; ++xitr, (void)++yitr, (void)xerrItr)
			stream << *xitr << ' ' << *yitr << ' ' << *xerrItr << '\n';
		
		stream << "e\n";
	}
};

template<class Container>
class YError : public IPlot{
public:
	const Container* x;
	const Container* y;
	const Container* yerror;
	PointType pointType = PointType::CircleFilled;
	float pointSize = 1.0;

	YError(const Container& x, const Container& y, const Container& yerror, Text title="")
		: IPlot(std::move(title))
		, x(&x)
		, y(&y)
		, yerror(&yerror)
	{}
	
	YError(YError const &) = default;
	YError(YError&&) = default;
	YError& operator=(YError const &) = default;
	YError& operator=(YError&&) = default;
	
	
	virtual void print_config(std::ostream& stream) const {
		stream << "'-' using 1:2:3 with yerrorbars";
		stream << " ps " << this->pointSize 
				<< " pt " << static_cast<int>(pointType)
				<< " title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data(std::ostream& stream) const {
		stream << "# Data for " << this->IPlot::title.str << "\n";
		auto xitr = std::begin(*x);
		auto yitr = std::begin(*y);
		auto yerrItr = std::begin(*yerror);
		
		const auto xEnd = std::end(*x);
		const auto yEnd = std::end(*y);
		const auto yerrEnd = std::end(*yerror);

		for (; xitr != xEnd && yitr != yEnd && yerrItr != yerrEnd; ++xitr, (void)++yitr, (void)yerrItr)
			stream << *xitr << ' ' << *yitr << ' ' << *yerrItr << '\n';
		
		stream << "e\n";
	}
};

template<class Container>
class XYError : public IPlot{
public:
	const Container* x;
	const Container* y;
	const Container* xerror;
	const Container* yerror;
	PointType pointType = PointType::CircleFilled;
	float pointSize = 1.0;

	XYError(const Container& x, const Container& y, const Container& xerror, const Container& yerror, Text title="")
		: IPlot(std::move(title))
		, x(&x)
		, y(&y)
		, xerror(&xerror)
		, yerror(&yerror)
	{}
	
	XYError(XYError const &) = default;
	XYError(XYError&&) = default;
	XYError& operator=(XYError const &) = default;
	XYError& operator=(XYError&&) = default;
	
	
	virtual void print_config(std::ostream& stream) const {
		stream << "'-' using 1:2:3:4 with xyerrorbars";
		stream << " ps " << this->pointSize 
				<< " pt " << static_cast<int>(pointType)
				<< " title '" << this->IPlot::title.str << "'";
	}
	
	virtual void print_data(std::ostream& stream) const {
		stream << "# Data for " << this->IPlot::title.str << "\n";
		auto xitr = std::begin(*x);
		auto yitr = std::begin(*y);
		auto xerrItr = std::begin(*xerror);
		auto yerrItr = std::begin(*yerror);
		
		const auto xEnd = std::end(*x);
		const auto yEnd = std::end(*y);
		const auto xerrEnd = std::end(*xerror);
		const auto yerrEnd = std::end(*yerror);

		for (; xitr != xEnd && yitr != yEnd && xerrItr != xerrEnd && yerrItr != yerrEnd; ++xitr, (void)++yitr, (void)yerrItr)
			stream << *xitr << ' ' << *yitr << ' ' << *xerrItr << ' ' << *yerrItr << '\n';
		
		stream << "e\n";
	}
};

// http://gnuplot.info/docs/Overview.html

// TODO: put classes and functions into their own files
// TODO: put opstream into its own GitHub repo

/* 	
http://gnuplot.info/docs/Plotting_Styles.html

	+ 2D Plots TODO:
		
		? make an class of Plot2D. with 1:2:3:4 - x:y:xerror:yerror
			an enum should set the concrete plotting type. 
		? ... or should every plotting type be its own type?
		? Interchangeing from points to lines to bars on a moments notice would be nice though
	
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

}//plotpp

template<size_t c, size_t r>
double at(double const (*array)[r][c], size_t row, size_t col){
	return (*array)[row][col];
}



int main() {
	using namespace plotpp;
	{
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
		
		fig.add(ImageFile("test_image_32x32.png"));
		fig.add(Heatmap(array, "Heatmap"));
		fig.add(Line(x, y1, "1/x*30"));
		fig.add(Points(x, y2, "1/x^2*30"));
		
		auto arrows = Arrows(arrow_x1, arrow_y1, arrow_x2, arrow_y2, "arrow plot");
		arrows.dataRelation = DataRelation::relative;
		fig.add(arrows);
		
		fig.show();
		fig.save("script.gp");
	}
	{
		std::vector<double> x(20);
		for(size_t i=0; i < x.size(); ++i) x[i] = i;
		
		std::vector<double> y(20);
		for(size_t i=0; i < y.size(); ++i) y[i] = 1./i*10;
		
		std::vector<double> yerrors(20);
		for(size_t i=0; i < yerrors.size(); ++i) yerrors[i] = 1;
		
		std::vector<double> y2(20);
		for(size_t i=0; i < y2.size(); ++i) y2[i] = i/static_cast<double>(y2.size())*10;
		
		std::vector<double> x2errors(20);
		for(size_t i=0; i < x2errors.size(); ++i) x2errors[i] = i/static_cast<double>(x2errors.size()) + 0.5;
		
		Figure fig("Points with error Bars");
		fig.add(XError(x, y, x2errors));	
		fig.add(YError(x, y2, yerrors));
		fig.add(XYError(y2, x, x2errors, yerrors));
		fig.show();	
	}
	
	
	
    return 0;
}