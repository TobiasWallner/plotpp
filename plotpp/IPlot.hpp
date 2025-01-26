#pragma once

#include <ostream>

#include "plotpp/Text.hpp"

namespace plotpp{

	class Figure;

	struct PlotTitle {
		std::string str;
		
		inline PlotTitle(const PlotTitle&) = default;
		inline PlotTitle(PlotTitle&&) = default;
		inline PlotTitle& operator=(const PlotTitle&) = default;
		inline PlotTitle& operator=(PlotTitle&&) = default;
		
		template <typename... Args> 
		inline PlotTitle(Args&&... args) 
			: str(std::forward<Args>(args)...) {}
		
		template <typename Arg> 
		inline PlotTitle& operator=(Arg&& args) {
			str = std::forward<Arg>(args); 
			return *this;
		}
		
		inline bool empty() const {return str.empty();}
	};

	class IPlot{
	public:
		friend class Figure;
	
		IPlot() = default;
		IPlot(std::string label) : label_(std::move(label)){}
		virtual ~IPlot(){}
		
		virtual void printPlot(std::ostream& stream) const = delete;
		virtual void printData(std::ostream& stream) const = delete;
		virtual void printSettings(std::ostream& stream) const = delete;
		
		virtual void printPlot(FILE* fptr) const = 0;
		virtual void printData(FILE* fptr) const = 0;
		virtual void printSettings(FILE* fptr) const {};
		
		inline const PlotTitle& label() const {return this->label_;}
		inline PlotTitle& label() {return this->label_;}
		
		inline IPlot& label(const char* label) & {this->label_ = label; return *this;}
		inline IPlot&& label(const char* label) && {this->label_ = label; return std::move(*this);}
		inline IPlot& label(std::string_view label) & {this->label_ = label; return *this;}
		inline IPlot&& label(std::string_view label) && {this->label_ = label; return std::move(*this);}
		inline IPlot& label(std::string&& label) & {this->label_ = std::move(label); return *this;}
		inline IPlot&& label(std::string&& label) && {this->label_ = std::move(label); return std::move(*this);}
	
	protected:
		virtual inline IPlot& uid(size_t& uid_io){
			this->uid_ = uid_io; 
			uid_io += 1;
			return *this;
		}
		inline size_t uid() const {return this->uid_;}
		
	private:
		PlotTitle label_ = "";
		size_t uid_ = 0;
	};
}

#include <fmt/format.h>

namespace fmt{
	template<>
	struct formatter<plotpp::PlotTitle>{
		
		constexpr auto parse(format_parse_context& ctx){
			return ctx.begin();
		}
		
		template<typename FormatContext>
		constexpr auto format(const plotpp::PlotTitle& title, FormatContext& ctx) const {
			if(title.empty()){
				fmt::format_to(ctx.out(), "notitle");
			}else{
				fmt::format_to(ctx.out(), "title '{}'", title.str);
			}
			return ctx.out();
		}
		
	};

}



