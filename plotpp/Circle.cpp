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
		this->fill_style.border(true);
	}
	
	void Circle::printData([[maybe_unused]]FILE* fptr) const {}
		
	void Circle::printPlot(FILE* fptr) const {
		fmt::print(fptr, "'+' using ({:g}):({:g}):({:g}):({:g}):({:g}) with circles lw {:.2f} {} {} {} {}", 
			this->x_, this->y_, this->radius_, this->start_angle, this->end_angle,
			this->line_width, 
			this->lineType(),
			this->fill_style,
			this->opt_color,
			this->IPlot::label());
	}
	
	
}