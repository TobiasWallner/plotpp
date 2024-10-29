#pragma once

#include <string_view>

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
	
	std::string_view to_command(ArrowHeadStyle ahs);
	
}