#pragma once

#include "IPlot.hpp"
#include "DataRelation.hpp"
#include "ArrowHeadStyle.hpp"

namespace plotpp{
	
	template<class T>
	class Arrows : public IPlot{
	public:

		T const & x1;
		T const & y1;
		T const & x2;
		T const & y2;
		DataRelation dataRelation; // relation from [x1, y1] to [x2, y2]
		float lineWidth = 1.5;
		ArrowHeadStyle arrowHeadStyle = ArrowHeadStyle::filled_head;
		
		Arrows(T const & x1, T const & y1, T const & x2, T const & y2, Text title="", DataRelation drel = DataRelation::relative)
			: IPlot(std::move(title))
			, x1(x1)
			, y1(y1)
			, x2(x2)
			, y2(y2)
			, dataRelation(drel)
		{}
		
		virtual void print_config(std::ostream& stream) const {
			if(dataRelation == DataRelation::absolute){
				stream << "using 1:2:(($3)-($1)):($4-$2)";
			}else{
				stream << "using 1:2:3:4";
			}
			
			if(dataRelation == DataRelation::polar){
				stream << " with arrows";
			}else{
				stream << " with vectors";
			}
			
			stream << " " << to_command(arrowHeadStyle);
			stream << " lw " << lineWidth;
			stream << " title '" << this->IPlot::title.str << "'";	
		}
		
		virtual void print_data(std::ostream& stream) const {
			auto x1itr = std::begin(x1);
			auto y1itr = std::begin(y1);
			auto x2itr = std::begin(x2);
			auto y2itr = std::begin(y2);
			for(; x1itr != std::end(x1) && y1itr != std::end(y1) && x2itr != std::end(x2) && y2itr != std::end(y2)
				; (void)++x1itr, (void)++y1itr, (void)++x2itr, (void)++y2itr){
				stream << *x1itr << ' ' << *y1itr << ' ' << *x2itr << ' ' << *y2itr << '\n';
			}
		}
	};
	
}