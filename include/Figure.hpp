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
		std::list<std::string> data_vars;
		
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
			// figure and axis configuration
			if(!title.empty()) stream << "set title " << title << "\n";
			if(TerminalType != TerminalType::NONE) stream << "set TerminalType " << to_command(TerminalType) << "\n";
			if(!saveAs.empty()) stream << "set output '" << saveAs << "'\n";
			if(!xlabel.empty()) stream << "set xlabel " << xlabel << "\n";
			if(!ylabel.empty()) stream << "set ylabel " << ylabel << "\n";
			stream << "\n";
				
			// write settings demanded by plots
			{
				auto plt_itr=this->plots.cbegin();
				for(; plt_itr!=this->plots.cend(); ++plt_itr){
					(*plt_itr)->print_settings(stream);
				}
			}
			stream << "\n";

			// write data variables
			{
				auto plt_itr=this->plots.cbegin();
				size_t i = 0;
				
				for(; plt_itr!=this->plots.cend(); ++plt_itr, (void)++i){
					std::string var_name("data");
					var_name += std::to_string(i);
					this->data_vars.push_back(var_name);
					stream << "$" << var_name << " << EOD\n";
					
					(*plt_itr)->print_data(stream);
					
					stream << "EOD\n\n";
				}	
			}
			stream << "\n";
			
			

			// write plot commands			
			{
				if(!this->plots.empty()) stream << "plot ";
				auto plot_itr = this->plots.cbegin();
				auto var_itr = this->data_vars.cbegin();
				for(; plot_itr!=this->plots.cend() && var_itr!=this->data_vars.cend(); ++plot_itr, (void)++var_itr){
					if (plot_itr!=this->plots.cbegin()) stream << "     ";
					stream << "$" << *var_itr << " ";
					(*plot_itr)->print_plot(stream);
					auto next = plot_itr; 
					++next;
					if(next!=this->plots.cend()) stream << ", \\\n";
				}
			}
			stream << "\n";
			
			if(!saveAs.empty()) stream << "set output\n"; // reset to default
			stream.flush();
		}
	};


}