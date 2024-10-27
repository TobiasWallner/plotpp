#pragma once

#include <ostream>

#include "IPlot.hpp"
#include "PointType.hpp"

namespace plotpp{

	template<class Container>
	class YError : public IPlot{
	public:
		const Container* x;
		const Container* y;
		const Container* yerror;
		PointType pointType = PointType::CircleFilled;
		float pointSize = 1.0;

		YError(const Container& x, const Container& y, const Container& yerror, Text title="")
			: IPlot(std::move(title))
			, x(&x)
			, y(&y)
			, yerror(&yerror)
		{}
		
		YError(YError const &) = default;
		YError(YError&&) = default;
		YError& operator=(YError const &) = default;
		YError& operator=(YError&&) = default;
		
		
		virtual void print_config(std::ostream& stream) const {
			stream << "'-' using 1:2:3 with yerrorbars";
			stream << " ps " << this->pointSize 
					<< " pt " << static_cast<int>(pointType)
					<< " title '" << this->IPlot::title.str << "'";
		}
		
		virtual void print_data(std::ostream& stream) const {
			stream << "# Data for " << this->IPlot::title.str << "\n";
			auto xitr = std::begin(*x);
			auto yitr = std::begin(*y);
			auto yerrItr = std::begin(*yerror);
			
			const auto xEnd = std::end(*x);
			const auto yEnd = std::end(*y);
			const auto yerrEnd = std::end(*yerror);

			for (; xitr != xEnd && yitr != yEnd && yerrItr != yerrEnd; ++xitr, (void)++yitr, (void)yerrItr)
				stream << *xitr << ' ' << *yitr << ' ' << *yerrItr << '\n';
			
			stream << "e\n";
		}
	};
	
}