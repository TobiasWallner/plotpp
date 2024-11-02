#pragma once

#include <ostream>

#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"

namespace plotpp{
			
	template<class Tx, class Ty, class Txerr>
	class XError : public IPlot{
	public:
		smartest_pointer<Tx> x;
		smartest_pointer<Ty> y;
		smartest_pointer<Txerr> xerror;
		PointType pointType = PointType::CircleFilled;
		float pointSize = 1.0;

		XError(smartest_pointer<Tx> x, smartest_pointer<Ty> y, smartest_pointer<Txerr> xerror, Text title="")
			: IPlot(std::move(title))
			, x(std::move(x))
			, y(std::move(y))
			, xerror(std::move(xerror))
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

	/*constructor helper*/
	template<typename U1, typename U2, typename U3>
	auto xerror(U1&& x, U2&& y, U3&& xerr, Text title="") {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		using Txerr = remove_ptr_t<std::remove_reference_t<U3>>;
		return XError<Tx, Ty, Txerr>(
					smartest_pointer<Tx>(std::forward<U1>(x)), 
					smartest_pointer<Ty>(std::forward<U2>(y)), 
					smartest_pointer<Txerr>(std::forward<U3>(xerr)), 
					std::move(title));
	}

}