#pragma once

#include <ostream>

#include "plotpp/Text.hpp"

namespace plotpp{

	class Figure;

	class IPlot{
	public:
		friend class Figure;
	
		IPlot() = default;
		IPlot(std::string label) : label_(std::move(label)){}
		virtual ~IPlot(){}
		
		virtual void printPlot(std::ostream& stream) const {};
		virtual void printData(std::ostream& stream) const  {};
		virtual void printSettings(std::ostream& stream) const {}
		
		virtual void printPlot_fmt(FILE* fptr) const {};
		virtual void printData_fmt(FILE* fptr) const  {};
		virtual void printSettings_fmt(FILE* fptr) const {}
		
		inline std::string_view label() const {return this->label_;}
		inline std::string& label() {return this->label_;}
		
		inline IPlot& label(const char* label) & {this->label_ = label; return *this;}
		inline IPlot&& label(const char* label) && {this->label_ = label; return std::move(*this);}
		inline IPlot& label(std::string_view label) & {this->label_ = label; return *this;}
		inline IPlot&& label(std::string_view label) && {this->label_ = label; return std::move(*this);}
		inline IPlot& label(std::string&& label) & {this->label_ = std::move(label); return *this;}
		inline IPlot&& label(std::string&& label) && {this->label_ = std::move(label); return std::move(*this);}
	
	protected:
		inline IPlot& uid(size_t& uid_io){
			this->uid_ = uid_io; 
			uid_io += 1;
			return *this;
		}
		inline size_t uid() const {return this->uid_;}
		
	private:
		std::string label_ = "";
		size_t uid_ = 0;
	};


}



