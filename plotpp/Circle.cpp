#include "Circle.hpp"

#include <fmt/core.h>

namespace plotpp{
	
	Circle::Circle(float x, float y, float radius, float startAngle, float endAngle)
		: x_(x)
		, y_(y)
		, radius_(radius)
		, start_angle(startAngle)
		, end_angle(endAngle)
	{}
	
	void Circle::printData(FILE* fptr) const {
			fmt::print(fptr, 
				"# empty data to trick gnuplot\n"
				"$d{:d} << e\n"
				"0\n"
				"e\n\n", 
				this->IPlot::uid());
		}
		
	void Circle::printPlot(FILE* fptr) const {
		fmt::print(fptr, "$d{:d} using ({:g}):({:g}):({:g}):({:g}):({:g}) with circles", 
			this->IPlot::uid(), this->x_, this->y_, this->radius_, this->start_angle, this->end_angle);
		
		if(this->solid_){
			fmt::print(fptr, " fs solid {:02f}", this->opacity_);
		}
		
		fmt::print(fptr, " lw {:02f}", this->line_width);
		
		if(this->opt_color){
			fmt::print(fptr, " lc rgb '#{:06x}'", this->opt_color.value().to_int32());
		}
		
		if(this->IPlot::label().empty()){
			fmt::print(fptr, " notitle");
		}else{
			fmt::print(fptr, " title '{}'", this->IPlot::label());
		}
	}
	
	
}