#include "Circle.hpp"

namespace plotpp{
	
	Circle::Circle(float x, float y, float radius, float startAngle, float endAngle)
		: x_(x)
		, y_(y)
		, radius_(radius)
		, start_angle(startAngle)
		, end_angle(endAngle)
	{}
	
	void Circle::printData(std::ostream& stream) const {
			stream << "$d" << this->IPlot::uid() << " << e\n";
			stream << "0\n";
			stream << "e\n\n";
		}
		
	void Circle::printPlot(std::ostream& stream) const {
		stream << "$d" << this->IPlot::uid() 
			<< " using (" << this->x_ 
			<< "):(" << this->y_ 
			<< "):(" << this->radius_ 
			<< "):(" << this->start_angle 
			<< "):(" << this->end_angle;
			
		stream << " with circles";
		
		if(this->solid_){
			stream << " fs solid " << this->opacity_;	
		}
		
		stream << " lw " << this->line_width;
		
		if(this->opt_color){
			stream << " lc rgb \"#" << this->opt_color.value().to_hex() << "\"";
		}
		
		if(this->IPlot::label().empty()){
			stream << " notitle";
		}else{
			stream <<  " title '" << this->IPlot::label() << "'";
		}
	}
	
	
}