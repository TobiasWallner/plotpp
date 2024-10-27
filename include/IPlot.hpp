#pragma once

#include <ostream>

#include "Text.hpp"

namespace plotpp{

	class IPlot{
	public:
		IPlot() = default;
		IPlot(Text title) : title(std::move(title)){}
		virtual ~IPlot(){}
		
		virtual void print_config(std::ostream& stream) const = 0;
		virtual void print_data(std::ostream& stream) const  = 0;
		
		Text title;
	};


}



