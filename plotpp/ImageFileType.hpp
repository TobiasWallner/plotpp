#pragma once

#include <string_view>

namespace plotpp{

	enum class ImageFileType{
		NONE,
		png, 
		jpeg,
		webp,
		gif,
	};

	std::string_view to_string(ImageFileType filetype);

	ImageFileType image_filetype_from_filename(std::string_view filename);
	
}