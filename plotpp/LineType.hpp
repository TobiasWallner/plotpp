#pragma once

#include <string_view>

namespace plotpp{

	enum class LineType{
		none,
		solid,
		dashed,
		doted,
		dash_doted,
		dash_doted2
	};

	std::string_view to_command(LineType dt);

}