#pragma once

#include <memory>
#include <string>
#include <list>
#include <ostream>
#include <iostream>
#include <fstream>

#include "opstream.hpp"

#include "plotpp/TerminalType.hpp"
#include "plotpp/OutputFileType.hpp"
#include "plotpp/Text.hpp"
#include "plotpp/IPlot.hpp"

namespace plotpp{

	class Figure{
	public:
		std::list<std::unique_ptr<IPlot>> plots;
		
		
	public:
		Text title;
		Text xlabel;
		Text ylabel;
		bool legend = false;
		
		Figure() = default;
		
		Figure(std::string title_str);
		
		Figure(Text title, Text xlabel, Text ylabel);
		
		/*TODO: Add enable if or requirement that T has to be derived from IPlot*/
		template<class T>
		Figure& add(std::unique_ptr<T>&& plot){
			std::unique_ptr<IPlot> p = std::move(plot);
			this->add(std::move(p));
			return *this;
		}
		
		/*TODO: Add enable if or requirement that T has to be derived from IPlot*/
		template<class T>
		Figure& add(T&& plot){
			using rrT = std::remove_reference_t<T>;
			std::unique_ptr<IPlot> p = std::make_unique<rrT>(std::forward<rrT>(plot));
			this->add(std::move(p));
			return *this;
		}
		
		Figure& add(std::unique_ptr<IPlot>&& plot);
		
		void show(OutputFileType filetype) const;
		
		void show(TerminalType TerminalType = TerminalType::NONE) const;
		
		void save(	std::string filename = "", 
					OutputFileType filetype=OutputFileType::NONE, 
					TerminalType TerminalType = TerminalType::NONE) const;

		void plot(
			std::ostream& stream, 
			TerminalType TerminalType = TerminalType::NONE,
			std::string saveAs = "") const;
			
		
	};
	
}