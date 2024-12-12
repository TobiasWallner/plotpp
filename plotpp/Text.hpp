#pragma once

#include <string>
#include <ostream>

#include <fmt/format.h>

namespace plotpp{

	class Text{
		public:
		
		std::string str = "";
		unsigned int height = 18;
		bool bold = false;
		bool italic = false;
		
		Text() = default;
		Text(std::string str);
			
		Text(const char* str);
		
		Text(const Text&) = default;
		Text(Text&&) = default;
		
		Text& operator=(const Text&) = default;
		Text& operator=(Text&&) = default;
					  
		Text& operator=(const std::string str);
		
		bool empty() const;

		operator std::string () const;
	};

	std::ostream& operator<<(std::ostream& stream, const Text& text);
}

// fmt formater
namespace fmt{
	template<>
	struct formatter<plotpp::Text>{
		
		constexpr auto parse(format_parse_context& ctx){
			return ctx.begin();
		}
		
		template<typename FormatContext>
		constexpr auto format(const plotpp::Text& text, FormatContext& ctx) const {
			fmt::format_to(
				ctx.out(),
				"'{0}{1}{2}{3}{4}' font \",{5}\"",
				text.italic ? "{/:Italic " : "",
				text.bold ? "{/:Bold " : "",
				text.str,
				text.bold ? "}" : "",
				text.italic ? "}" : "",
				text.height);
			return ctx.out();
		}
		
	};
}