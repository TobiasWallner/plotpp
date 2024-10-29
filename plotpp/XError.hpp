#pragma once

#include <ostream>

#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"

namespace plotpp{
			
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
		
		
		virtual void print_plot(std::ostream& stream) const {
			stream << " using 1:2:3 with xerrorbars";
			stream << " ps " << this->pointSize 
					<< " pt " << static_cast<int>(pointType)
					<< " title '" << this->IPlot::title.str << "'";
		}
		
		virtual void print_data(std::ostream& stream) const {
			auto xitr = std::begin(*x);
			auto yitr = std::begin(*y);
			auto xerrItr = std::begin(*xerror);
			
			const auto xEnd = std::end(*x);
			const auto yEnd = std::end(*y);
			const auto xerrEnd = std::end(*xerror);

			for (; xitr != xEnd && yitr != yEnd && xerrItr != xerrEnd; ++xitr, (void)++yitr, (void)xerrItr)
				stream << *xitr << ' ' << *yitr << ' ' << *xerrItr << '\n';

		}
	};

}