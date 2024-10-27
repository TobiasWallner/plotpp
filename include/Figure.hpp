#pragma once

#include <memory>
#include <string>
#include <list>
#include <ostream>
#include <iostream>
#include <fstream>

#include "opstream.hpp"

#include "TerminalType.hpp"
#include "OutputFileType.hpp"
#include "Text.hpp"
#include "IPlot.hpp"

namespace plotpp{

	class Figure{
	public:
		std::list<std::unique_ptr<IPlot>> plots;
		
	public:
		Text title;
		Text xlabel;
		Text ylabel;
		bool legend = false;
		
		template<class T>
		Figure& add(std::unique_ptr<T>&& plot){
			std::unique_ptr<IPlot> p = std::move(plot);
			this->plots.push_back(std::move(plot));
			return *this;
		}
		
		/*TODO: Add enable if*/
		template<class T>
		Figure& add(T&& plot){
			using rrT = std::remove_reference_t<T>;
			std::unique_ptr<IPlot> p = std::make_unique<rrT>(std::forward<rrT>(plot));
			this->plots.emplace_back(std::move(p));
			return *this;
		}
		
		Figure(std::string title_str=""){
			title.str = title_str;
			title.height = 20;
			title.bold = true;
		}
		
		Figure(Text title, Text xlabel, Text ylabel)
			: title(title)
			, xlabel(xlabel)
			, ylabel(ylabel)
		{}
		
		void show(OutputFileType filetype){
			if(filetype == OutputFileType::gp){
				_plot(std::cout, TerminalType::NONE);
			}else{
				show(to_terminal(filetype));
			}
		}
		
		void show(TerminalType TerminalType = TerminalType::NONE){
			opstream gnuplot("gnuplot -persist");
			_plot(gnuplot, TerminalType);
		}
		
		void save(std::string filename = "", OutputFileType filetype=OutputFileType::NONE, TerminalType TerminalType = TerminalType::NONE){
			if(filename.empty()) filename = title;
			
			if(filetype == OutputFileType::NONE){
				filetype = filetype_from_filename(filename);
				if(filetype == OutputFileType::NONE){
					filetype = OutputFileType::png;
					filename += ".png";
				}
			}else if(!filename.ends_with(std::string(to_file_ending(filetype)))){
					filename += to_file_ending(filetype);
			}
			
			if(TerminalType == TerminalType::NONE){
				TerminalType = to_terminal(filetype);	
			}
			
			if(filetype==OutputFileType::gp){
				std::ofstream fstream(filename);
				_plot(fstream, TerminalType);
			}else{
				opstream gnuplot("gnuplot -persist");
				_plot(gnuplot, TerminalType, filename);	
			}
		}

	public:
		void _plot(
			std::ostream& stream, 
			TerminalType TerminalType = TerminalType::NONE,
			std::string saveAs = "")
		{
			if(!title.empty()) stream << "set title " << title << "\n";
			if(TerminalType != TerminalType::NONE) stream << "set TerminalType " << to_command(TerminalType) << "\n";
			if(!saveAs.empty()) stream << "set output '" << saveAs << "'\n";
			if(!xlabel.empty()) stream << "set xlabel " << xlabel << "\n";
			if(!ylabel.empty()) stream << "set ylabel " << ylabel << "\n";
			
			if(!this->plots.empty()) stream << "plot ";
			for(auto itr=this->plots.cbegin(); itr!=this->plots.cend(); ++itr){
				if (itr!=this->plots.begin()) stream << '\t';
				(*itr)->print_config(stream);
				auto next = itr; 
				++next;
				if(next!=this->plots.cend()) stream << ", \\\n";
			}
			

			for(auto itr=this->plots.cbegin(); itr!=this->plots.cend(); ++itr){
				stream << "\n";
				(*itr)->print_data(stream);
			}
			
			if(!saveAs.empty()) stream << "set output\n"; // reset to default
			
			stream.flush();
		}
	};


}