#pragma once

#include <ostream>
#include <iterator>

#include "plotpp/IPlot.hpp"


/* TODO: parameterise boxwidth 
				float width
				BoxWithType:: Absolute | Relative
*/

/* TODO: Add Color

*/


namespace plotpp{
	
	template<class Tx, class Ty>
	class Boxes : public IPlot{
	public:
		smartest_pointer<Tx> x;
		smartest_pointer<Ty> y;
		
		bool x_is_text = false;
		
		Boxes(smartest_pointer<Tx> x, smartest_pointer<Ty> y, Text title="")
			: IPlot(std::move(title))
			, x(std::move(x))
			, y(std::move(y)) 
			, x_is_text(false)
			{}
		
		virtual void print_settings(std::ostream& stream) const {
			stream << "set boxwidth 0.8 relative\n";
		}
		
		virtual void print_data(std::ostream& stream) const {
			auto xitr = std::begin(*x);
			auto yitr = std::begin(*y);
			for(; yitr!=std::end(*y) && xitr!=std::end(*x); ++yitr, (void)++xitr)
				stream << *xitr << ' ' << *yitr << '\n';				
		}
		
		virtual void print_plot(std::ostream& stream) const {
			stream << "using 1:2 with boxes fs transparent solid 0.5 title '" << this->IPlot::title.str << "'";
		}
		
	};
	
	/*constructor helper*/
	template<typename U1, typename U2>
	auto boxes(U1&& x, U2&& y, Text title="") {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Boxes<Tx, Ty>(
					smartest_pointer<Tx>(std::forward<U1>(x)), 
					smartest_pointer<Ty>(std::forward<U2>(y)), 
					std::move(title));
	}
}