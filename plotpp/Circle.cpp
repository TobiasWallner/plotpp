#include "Circle.hpp"

#include <fmt/core.h>

namespace plotpp{
	
	Circle::Circle(float x, float y, float radius, float startAngle, float endAngle)
		: x_(x)
		, y_(y)
		, radius_(radius)
		, start_angle(startAngle)
		, end_angle(endAngle)
	{
		this->fill_style.clear();
	}
	
	void Circle::printData(FILE* fptr) const {
			fmt::print(fptr, 
				"# empty data to trick gnuplot\n"
				"$d{:d} << e\n"
				"0\n"
				"e\n\n", 
				this->IPlot::uid());
	}
		
	void Circle::printPlot(FILE* fptr) const {
		// Circle data
		fmt::print(fptr, "$d{:d} using ({:g}):({:g}):({:g}):({:g}):({:g}) with circles", 
			this->IPlot::uid(), this->x_, this->y_, this->radius_, this->start_angle, this->end_angle);
		
		// Line Width, Dash and fill type
		fmt::print(fptr, " lw {:.2f} dt {:d} {}", 
			this->line_width, 
			static_cast<int>(this->lineType()),
			this->fill_style);
		
		// Color
		if(this->opt_color){
			fmt::print(fptr, " lc rgb '#{:06x}'", this->opt_color.value().to_int32());
		}
		
		// Title
		if(this->IPlot::label().empty()){
			fmt::print(fptr, " notitle");
		}else{
			fmt::print(fptr, " title '{}'", this->IPlot::label());
		}
	}
	
	
}