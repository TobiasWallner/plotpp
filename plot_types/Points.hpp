#pragma once

#include <ostream>

#include "IPlot.hpp"
#include "PointType.hpp"

namespace plotpp{

	template<class Container>
	class Points : public IPlot{
	public:
		const Container* x;
		const Container* y;
		PointType pointType = PointType::CircleFilled;
		float pointSize = 1.0;
		/*TODO: LineColor*/
		
	public:

		Points(const Container& x, const Container& y, Text title="")
			: IPlot(std::move(title))
			, x(&x)
			, y(&y)
		{}
		
		Points(Points const &) = default;
		Points(Points&&) = default;
		Points& operator=(Points const &) = default;
		Points& operator=(Points&&) = default;
		
		
		virtual void print_config(std::ostream& stream) const {
			stream << "'-' using 1:2 with points"
					<< " ps " << this->pointSize 
					<< " pt " << static_cast<int>(pointType)
					<< " title '" << this->IPlot::title.str << "'";
		}
		
		virtual void print_data(std::ostream& stream) const {
			stream << "# Data for " << this->IPlot::title.str << "\n";
			auto xitr = std::begin(*x);
			auto yitr = std::begin(*y);
			
			for (; xitr != std::end(*x) && yitr != std::end(*y); ++xitr, (void)++yitr)
				stream << *xitr << ' ' << *yitr << '\n';

			stream << "e\n";
		}
	};

}