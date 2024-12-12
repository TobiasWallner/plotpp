#pragma once

#include <string_view>

#include <fmt/core.h>
#include <fmt/format.h>

namespace plotpp{

	enum class ArrowHeadStyle{
		nohead,
		head,
		filled_head,
		empty_head,
		backhead,
		filled_backhead,
		empty_backhead,
	};
	
	constexpr const char* to_command(ArrowHeadStyle ahs){
		switch(ahs){
			case ArrowHeadStyle::nohead : return "nohead";
			case ArrowHeadStyle::head : return "head";
			case ArrowHeadStyle::filled_head : return "filled head";
			case ArrowHeadStyle::empty_head : return "empty head";
			case ArrowHeadStyle::backhead : return "backhead";
			case ArrowHeadStyle::filled_backhead : return "filled backhead";
			case ArrowHeadStyle::empty_backhead : return "empty backhead";
		}
		throw std::runtime_error(
				fmt::format(
					"Error in funtion: {}n"
					"  in file: {}\n"
					"  at line: {}\n"
					"  message: missing switch case\n",
					__FUNCTION__, __FILE__, __LINE__));
		return "";
	}
	
	
}

// fmt formater
namespace fmt{
	template<>
	struct formatter<plotpp::ArrowHeadStyle>{
		
		constexpr auto parse(format_parse_context& ctx){
			return ctx.begin();
		}
		
		template<typename FormatContext>
		constexpr auto format(const plotpp::ArrowHeadStyle& ahs, FormatContext& ctx) const {
			using namespace plotpp;
			fmt::format_to(ctx.out(), "{}", to_command(ahs));
			return ctx.out();
		}
		
	};
}