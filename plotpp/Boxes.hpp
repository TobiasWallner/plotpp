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
		optional_ptr<Tx> x;
		optional_ptr<Ty> y;
		
		bool x_is_text = false;
		
		Boxes(optional_ptr<Tx> x, optional_ptr<Ty> y, Text title="")
			: x(std::move(x))
			, y(std::move(y)) 
			, x_is_text(false)
			{}
		
		virtual void printSettings(std::ostream& stream) const {
			stream << "set boxwidth 0.8 relative\n";
		}
		
		virtual void printData(std::ostream& stream) const {
			auto xitr = std::begin(*x);
			auto yitr = std::begin(*y);
			for(; yitr!=std::end(*y) && xitr!=std::end(*x); ++yitr, (void)++xitr)
				stream << *xitr << ' ' << *yitr << '\n';				
		}
		
		virtual void printPlot(std::ostream& stream) const {
			stream << "using 1:2 with boxes fs transparent solid 0.5 title '" << this->IPlot::label() << "'";
		}
		
	};
	
	/*constructor helper*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	auto boxes(U1 x, U2 y, Text title="") {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Boxes<Tx, Ty>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}
}