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
		smartest_pointer<const Tx> x;
		smartest_pointer<const Ty> y;
		
		bool x_is_text = false;
		
		template<typename U1, typename U2>
		Boxes(U1&& x, U2&& y, Text title="")
			: IPlot(std::move(title))
			, x(std::forward<U1>(x))
			, y(std::forward<U2>(y)) 
			, x_is_text(false)
			{}
		
		virtual void print_settings(std::ostream& stream) const {
			stream << "set boxwidth 0.8 relative\n";
			if(x_is_text==true) {
				stream << "set xtics (";
				size_t i = 0;
				auto xitr = std::begin(*x);
				for(; xitr!=std::end(*x); ++xitr, (void)++i){
					if(xitr != std::begin(*x)) stream << ", ";
					stream << "\"" << *xitr << "\"" << ' ' << i;
				}
				stream << ")\n";
			}
		}
		
		virtual void print_data(std::ostream& stream) const {
			auto xitr = std::begin(*x);
			auto yitr = std::begin(*y);
			for(; yitr!=std::end(*y) && xitr!=std::end(*x); ++yitr, (void)++xitr)
				stream << *xitr << ' ' << *yitr << '\n';				
		}
		
		virtual void print_plot(std::ostream& stream) const {
			if(x_is_text){
				stream << "using 2:xtic(1) with boxes fs transparent solid 0.5 title '" << this->IPlot::title.str << "'";
			}else{
				stream << "using 1:2 with boxes fs transparent solid 0.5 title '" << this->IPlot::title.str << "'";
			}
			
			
		}
		
	};
	
	/*constructor helper*/
	template<typename U1, typename U2>
	auto boxes(U1&& x, U2&& y, Text title="") {
		using Tx = std::remove_reference_t<decltype(x)>;
		using Ty = std::remove_reference_t<decltype(y)>;
		return Boxes<Tx, Ty>(std::forward<U1>(x), std::forward<U2>(y), std::move(title));
	}
	
	/*constructor helper*/
	template<typename U1, typename U2>
	auto boxes_xtext(U1&& x, U2&& y, Text title="") {
		using Tx = std::remove_reference_t<decltype(x)>;
		using Ty = std::remove_reference_t<decltype(y)>;
		auto plot = Boxes<Tx, Ty>(std::forward<U1>(x), std::forward<U2>(y), std::move(title));
		plot.x_is_text = true;
		return plot;
	}
}