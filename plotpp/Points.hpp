#pragma once

#include <ostream>
#include <iterator>

#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"

namespace plotpp{

	template<class Tx, class Ty>
	class Points : public IPlot{
	public:
		smartest_pointer<const Tx> x;
		smartest_pointer<const Ty> y;
		PointType pointType = PointType::CircleFilled;
		float pointSize = 1.0;
		/*TODO: LineColor*/
		
	public:

		template<typename U1, typename U2>
		Points(U1&& x, U2&& y, Text title="")
			: IPlot(std::move(title))
			, x(std::forward<U1>(x))
			, y(std::forward<U2>(y)) 
			{}
		
		Points(Points const &) = default;
		Points(Points&&) = default;
		Points& operator=(Points const &) = default;
		Points& operator=(Points&&) = default;
		
		
		virtual void print_plot(std::ostream& stream) const {
			stream << "using 1:2 with points"
					<< " ps " << this->pointSize 
					<< " pt " << static_cast<int>(pointType)
					<< " title '" << this->IPlot::title.str << "'";
		}
		
		virtual void print_data(std::ostream& stream) const {
			auto xitr = std::begin(*x);
			auto yitr = std::begin(*y);
			
			for (; xitr != std::end(*x) && yitr != std::end(*y); ++xitr, (void)++yitr)
				stream << *xitr << ' ' << *yitr << '\n';
		}
	};

	/*constructor helper*/
	template<typename U1, typename U2>
	auto points(U1&& x, U2&& y, Text title="") {
		using Tx = std::remove_reference_t<decltype(x)>;
		using Ty = std::remove_reference_t<decltype(y)>;
		return Points<Tx, Ty>(std::forward<U1>(x), std::forward<U2>(y), std::move(title));
	}

}