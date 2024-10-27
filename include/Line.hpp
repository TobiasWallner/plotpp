#pragma once

#include <ostream>

#include "IPlot.hpp"
#include "LineType.hpp"

namespace plotpp{

	template<class Container>
	class Line : public IPlot{
	public:
		const Container* x;
		const Container* y;
		
		LineType lineType = LineType::solid;
		float lineWidth = 1.5;
		/*TODO: LineColor*/
		
	public:
		
		Line(const Container& x, const Container& y, Text title="")
			: IPlot(std::move(title))
			, x(&x)
			, y(&y)
		{}
		
		Line(Line const &) = default;
		Line(Line&&) = default;
		Line& operator=(Line const &) = default;
		Line& operator=(Line&&) = default;
		
		
		virtual void print_config(std::ostream& stream) const {
			stream << "using 1:2 with lines lw " << this->lineWidth << " " 
					<< to_command(this->lineType) << " title '" << this->IPlot::title.str << "'";
		}
		
		virtual void print_data(std::ostream& stream) const {
			auto xItr = std::begin(*x);
			auto yItr = std::begin(*y);
			for (; xItr != std::end(*x) && yItr != std::end(*y); (void)++xItr, (void)++yItr) {
				stream << *xItr << ' ' << *yItr << "\n";
			}
		}
	};

}