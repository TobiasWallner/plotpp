#pragma once

#include <ostream>

#include "plotpp/Text.hpp"

namespace plotpp{

	class IPlot{
	public:
		IPlot() = default;
		IPlot(std::string label) : _label(std::move(label)){}
		virtual ~IPlot(){}
		
		virtual void printPlot(std::ostream& stream) const = 0;
		virtual void printData(std::ostream& stream) const  = 0;
		virtual void printSettings(std::ostream& stream) const {}
		
		std::string_view label() const {return this->_label;}
		std::string& label() {return this->_label;}
		
		IPlot& label(const char* label) & {this->_label = label; return *this;}
		IPlot&& label(const char* label) && {this->_label = label; return std::move(*this);}
		IPlot& label(std::string_view label) & {this->_label = label; return *this;}
		IPlot&& label(std::string_view label) && {this->_label = label; return std::move(*this);}
		IPlot& label(std::string&& label) & {this->_label = std::move(label); return *this;}
		IPlot&& label(std::string&& label) && {this->_label = std::move(label); return std::move(*this);}
		
	private:
		std::string _label;
	};


}



