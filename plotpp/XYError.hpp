#pragma once

#include <ostream>

#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"

namespace plotpp{
		
	template<class Tx, class Ty, class Txerr, class Tyerr>
	class XYError : public IPlot{
	public:
		smartest_pointer<Tx> x;
		smartest_pointer<Ty> y;
		smartest_pointer<Txerr> xerror;
		smartest_pointer<Tyerr> yerror;
		PointType pointType = PointType::CircleFilled;
		float pointSize = 1.0;

		XYError(
			smartest_pointer<Tx> x, 
			smartest_pointer<Ty> y, 
			smartest_pointer<Txerr> xerror, 
			smartest_pointer<Tyerr> yerror, 
			Text title=""
		)
			: IPlot(std::move(title))
			, x(std::move(x))
			, y(std::move(y))
			, xerror(std::move(xerror))
			, yerror(std::move(yerror))
		{}
		
		XYError(XYError const &) = default;
		XYError(XYError&&) = default;
		XYError& operator=(XYError const &) = default;
		XYError& operator=(XYError&&) = default;
		
		
		virtual void print_plot(std::ostream& stream) const {
			stream 	<< " using 1:2:3:4 with xyerrorbars";
			stream 	<< " ps " << this->pointSize 
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

	/*constructor helper*/
	template<typename U1, typename U2, typename U3, typename U4>
	auto xyerror(U1&& x, U2&& y, U3&& xerr, U4&& yerr, Text title="") {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		using Txerr = remove_ptr_t<std::remove_reference_t<U3>>;
		using Tyerr = remove_ptr_t<std::remove_reference_t<U4>>;
		return XYError<Tx, Ty, Txerr, Tyerr>(
					smartest_pointer<Tx>(std::forward<U1>(x)), 
					smartest_pointer<Ty>(std::forward<U2>(y)), 
					smartest_pointer<Txerr>(std::forward<U3>(yerr)), 
					smartest_pointer<Tyerr>(std::forward<U4>(yerr)), 
					std::move(title));
	}

}