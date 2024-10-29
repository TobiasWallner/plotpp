#pragma once

#include <ostream>

#include "plotpp/Text.hpp"

namespace plotpp{

	class IPlot{
	public:
		IPlot() = default;
		IPlot(Text title) : title(std::move(title)){}
		virtual ~IPlot(){}
		
		virtual void print_plot(std::ostream& stream) const = 0;
		virtual void print_data(std::ostream& stream) const  = 0;
		virtual void print_settings(std::ostream& stream) const {}
		
		Text title;
	};


}



