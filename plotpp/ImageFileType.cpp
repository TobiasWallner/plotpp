#include "plotpp/ImageFileType.hpp"

#include <string_view>
#include <sstream>

namespace plotpp{

	std::string_view to_string(ImageFileType filetype){
		switch(filetype){
			case ImageFileType::NONE : {
				std::stringstream message;
				message << "Error in funtion: " << __FUNCTION__ << "\n"
						<< "  in file: " << __FILE__ << "\n"
						<< "  at line: " << __LINE__ << "\n"
						<< "  message: NONE is not a valid filetype\n";
				throw std::runtime_error(message.str());
			} break;
			case ImageFileType::png : return "png";
			case ImageFileType::jpeg : return "jpeg";
			case ImageFileType::webp : return "webp";
			case ImageFileType::gif : return "gif";
		}
		std::stringstream message;
		message << "Error in funtion: " << __FUNCTION__ << "\n"
				<< "  in file: " << __FILE__ << "\n"
				<< "  at line: " << __LINE__ << "\n"
				<< "  message: missing switch case\n";
		throw std::runtime_error(message.str());
	}

	ImageFileType image_filetype_from_filename(std::string_view filename){
		if(filename.ends_with(".png"))       return ImageFileType::png;
		else if(filename.ends_with(".jpeg")) return ImageFileType::jpeg;
		else if(filename.ends_with(".jpg"))  return ImageFileType::jpeg;
		else if(filename.ends_with(".webp")) return ImageFileType::webp;
		else if(filename.ends_with(".gif"))  return ImageFileType::gif;
		else                                 return ImageFileType::NONE;
	}
	
}