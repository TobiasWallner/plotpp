#pragma once

#include <ostream>
#include <iterator>
#include <memory>

#include "plotpp/IPlot.hpp"
#include "plotpp/LineType.hpp"

#include "smartest_pointer.hpp"

namespace plotpp{

	template<class Tx, class Ty>
	class Line : public IPlot{
	public:
		smartest_pointer<const Tx> x;
		smartest_pointer<const Ty> y;
		
		LineType lineType = LineType::solid;
		float lineWidth = 1.5;
		/*TODO: LineColor*/
		
	public:
		
		template<typename U1, typename U2>
		Line(U1&& x, U2&& y, Text title="")
			: IPlot(std::move(title))
			, x(std::forward<U1>(x))
			, y(std::forward<U2>(y)) 
			{}
		
		Line(Line const &) = default;
		Line(Line&&) = default;
		Line& operator=(Line const &) = default;
		Line& operator=(Line&&) = default;
		
		
		virtual void print_plot(std::ostream& stream) const {
			stream << "using 1:2 with lines lw " << this->lineWidth << " " 
					<< to_command(this->lineType) << " title '" << this->IPlot::title.str << "'";
		}
		
		virtual void print_data(std::ostream& stream) const {
			auto xItr = std::begin(*x);
			auto yItr = std::begin(*y);
			for (; xItr != std::end(*x) && yItr != std::end(*y); (void)++xItr, (void)++yItr) {
				stream << *xItr << ' ' << *yItr << "\n";
			}
		}
	};

	/*constructor helper
		Deduces the template parameters for `Line` and constructs it with perfect argument forwarding.
		This guarantees that no unnecessary copies are made for what could be huge datasets for `x` and `y`.
	*/
	template<typename U1, typename U2>
	auto line(U1&& x, U2&& y, Text title="") {
		using Tx = std::remove_reference_t<decltype(x)>;
		using Ty = std::remove_reference_t<decltype(y)>;
		return Line<Tx, Ty>(std::forward<U1>(x), std::forward<U2>(y), std::move(title));
	}

}