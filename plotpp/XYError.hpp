#pragma once

#include <ostream>

#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"

namespace plotpp{
		
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
		
		
		virtual void print_plot(std::ostream& stream) const {
			stream << " using 1:2:3:4 with xyerrorbars";
			stream << " ps " << this->pointSize 
					<< " pt " << static_cast<int>(pointType)
					<< " title '" << this->IPlot::title.str << "'";
		}
		
		virtual void print_data(std::ostream& stream) const {
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
			
		}
	};

	
}