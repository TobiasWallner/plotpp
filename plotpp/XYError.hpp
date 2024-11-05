#pragma once

#include <ostream>

#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"

namespace plotpp{
		
	template<class Tx, class Ty, class Txerr, class Tyerr>
	class XYError : public IPlot{
	public:
		optional_ptr<Tx> x;
		optional_ptr<Ty> y;
		optional_ptr<Txerr> xerror;
		optional_ptr<Tyerr> yerror;
		PointType pointType = PointType::CircleFilled;
		float pointSize = 1.0;

		XYError(
			optional_ptr<Tx> x, 
			optional_ptr<Ty> y, 
			optional_ptr<Txerr> xerror, 
			optional_ptr<Tyerr> yerror, 
			Text title=""
		)
			: x(std::move(x))
			, y(std::move(y))
			, xerror(std::move(xerror))
			, yerror(std::move(yerror))
		{}
		
		XYError(XYError const &) = default;
		XYError(XYError&&) = default;
		XYError& operator=(XYError const &) = default;
		XYError& operator=(XYError&&) = default;
		
		
		virtual void printPlot(std::ostream& stream) const {
			stream 	<< " using 1:2:3:4 with xyerrorbars";
			stream 	<< " ps " << this->pointSize 
					<< " pt " << static_cast<int>(pointType)
					<< " title '" << this->IPlot::label() << "'";
		}
		
		virtual void printData(std::ostream& stream) const {
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
	template<PtrOrMoved U1, PtrOrMoved U2, PtrOrMoved U3, PtrOrMoved U4>
	auto xyerror(U1 x, U2 y, U3 xerr, U4 yerr, Text title="") {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		using Txerr = remove_ptr_t<std::remove_reference_t<U3>>;
		using Tyerr = remove_ptr_t<std::remove_reference_t<U4>>;
		return XYError<Tx, Ty, Txerr, Tyerr>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)), 
					optional_ptr<Txerr>(std::forward<U3>(yerr)), 
					optional_ptr<Tyerr>(std::forward<U4>(yerr)));
	}

}