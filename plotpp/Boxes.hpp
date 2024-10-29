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
	
	template<class Ty, class Tx=int[1]>
	class Boxes : public IPlot{
	public:
		const Tx* x = nullptr;
		const Ty* y = nullptr;
		bool x_is_text = false;
		
		Boxes(const Ty& y, Text title)
			: IPlot(std::move(title))
			, x(nullptr)
			, y(&y)
			, x_is_text(false)
			{}
			
		Boxes(const Ty& y, const char* title="")
			: IPlot(std::move(title))
			, x(nullptr)
			, y(&y)
			, x_is_text(false)
			{}
		
		Boxes(const Tx& x, const Ty& y, Text title)
			: IPlot(std::move(title))
			, x(&x)
			, y(&y)
			, x_is_text(false)
			{}
			
		Boxes(const Tx& x, const Ty& y, const char* title="")
			: IPlot(std::move(title))
			, x(&x)
			, y(&y)
			, x_is_text(false)
			{}
		
		Boxes(const Tx& x, const Ty& y, bool x_is_text, Text title)
			: IPlot(std::move(title))
			, x(&x)
			, y(&y)
			, x_is_text(x_is_text)
			{}
			
		Boxes(const Tx& x, const Ty& y, bool x_is_text, const char* title="")
			: IPlot(std::move(title))
			, x(&x)
			, y(&y)
			, x_is_text(x_is_text)
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
			if(x==nullptr){
				for(auto yitr = std::begin(*y); yitr!=std::end(*y); ++yitr)
					stream << *yitr << '\n';	
			}else{
				auto xitr = std::begin(*x);
				auto yitr = std::begin(*y);
				for(; yitr!=std::end(*y) && xitr!=std::end(*x); ++yitr, (void)++xitr)
					stream << *xitr << ' ' << *yitr << '\n';	
			}
			
		}
		
		virtual void print_plot(std::ostream& stream) const {
			if(x==nullptr){
				stream << "with boxes fs transparent solid 0.5 title '" << this->IPlot::title.str << "'";
			}else if(x_is_text){
				stream << "using 2:xtic(1) with boxes fs transparent solid 0.5 title '" << this->IPlot::title.str << "'";
			}else{
				stream << "using 1:2 with boxes fs transparent solid 0.5 title '" << this->IPlot::title.str << "'";
			}
			
			
		}
		
	};
	
}