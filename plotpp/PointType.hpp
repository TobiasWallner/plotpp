#pragma once

#include <fmt/format.h>

namespace plotpp{
	enum class PointType : int {
		None = -1,
		SmallDot = 0,
		Plus = 1,
		X = 2,
		PlusX = 3,
		Square = 4,
		SquareFilled = 5,
		Circle = 6,
		CircleFilled = 7,
		TriangleUp = 8,
		TriangleUpFilled = 9,
		TriangleDown = 10,
		TriangleDownFilled = 11,
		Rhombus = 12,
		RhombusFilled = 13,
		Heptagon = 14,
		HeptagonFilled = 15
	};
}

namespace fmt{
	template<>
	struct formatter<plotpp::PointType>{
		
		constexpr auto parse(format_parse_context& ctx){
			return ctx.begin();
		}
		
		template<typename FormatContext>
		constexpr auto format(const plotpp::PointType& pt, FormatContext& ctx) const {
			fmt::format_to(ctx.out(), "pt {:d}", static_cast<int>(pt));
			return ctx.out();
		}
		
	};
}