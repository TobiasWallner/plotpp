#pragma once

#include <string_view>

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