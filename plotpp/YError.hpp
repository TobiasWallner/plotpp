#pragma once

#include <ostream>

#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"

namespace plotpp{

	template<class Tx, class Ty, class Tyerr>
	class YError : public IPlot{
	public:
		
		smartest_pointer<Tx> x;
		smartest_pointer<Ty> y;
		smartest_pointer<Tyerr> yerror;
		PointType pointType = PointType::CircleFilled;
		float pointSize = 1.0;

		YError(smartest_pointer<Tx> x, smartest_pointer<Ty> y, smartest_pointer<Tyerr> yerr, Text title="")
			: IPlot(std::move(title))
			, x(std::move(x))
			, y(std::move(y)) 
			, yerror(std::move(yerr)) 
			{}
		
		YError(YError const &) = default;
		YError(YError&&) = default;
		YError& operator=(YError const &) = default;
		YError& operator=(YError&&) = default;
		
		
		virtual void print_plot(std::ostream& stream) const {
			stream 	<< " using 1:2:3 with yerrorbars"
					<< " ps " << this->pointSize 
					<< " pt " << static_cast<int>(pointType)
					<< " title '" << this->IPlot::title.str << "'";
		}
		
		virtual void print_data(std::ostream& stream) const {
			auto xitr = std::begin(*x);
			auto yitr = std::begin(*y);
			auto yerrItr = std::begin(*yerror);
			
			const auto xEnd = std::end(*x);
			const auto yEnd = std::end(*y);
			const auto yerrEnd = std::end(*yerror);

			for (; xitr != xEnd && yitr != yEnd && yerrItr != yerrEnd; ++xitr, (void)++yitr, (void)yerrItr)
				stream << *xitr << ' ' << *yitr << ' ' << *yerrItr << '\n';
			
		}
	};
	
	/*constructor helper*/
	template<typename U1, typename U2, typename U3>
	auto yerror(U1&& x, U2&& y, U3&& yerr, Text title="") {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		using Tyerr = remove_ptr_t<std::remove_reference_t<U3>>;
		return YError<Tx, Ty, Tyerr>(
					smartest_pointer<Tx>(std::forward<U1>(x)), 
					smartest_pointer<Ty>(std::forward<U2>(y)), 
					smartest_pointer<Tyerr>(std::forward<U3>(yerr)), 
					std::move(title));
	}
	
}