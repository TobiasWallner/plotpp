#pragma once

#include <string_view>
#include <fmt/format.h>

namespace plotpp{

	enum class LineType{
		none = -1,
		solid = 1,
		dashed = 2,
		doted = 3,
		dash_doted = 4,
		dash_doted2 = 5
	};

	std::string_view to_command(LineType dt);

}

namespace fmt{
	template<>
	struct formatter<plotpp::LineType>{
		
		constexpr auto parse(format_parse_context& ctx){
			return ctx.begin();
		}
		
		template<typename FormatContext>
		constexpr auto format(const plotpp::LineType& lt, FormatContext& ctx) const {
			fmt::format_to(ctx.out(), "dt {:d}", static_cast<int>(lt));
			return ctx.out();
		}
		
	};
}