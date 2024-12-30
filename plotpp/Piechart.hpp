#pragma once

// std
#include <ostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <optional>
#include <numeric>

// zip iterator
#include <zip_tuple.hpp>

// project
#include "plotpp/IPlot.hpp"
#include "plotpp/LineType.hpp"
#include "optional_ptr.hpp"
#include "plotpp/concepts.hpp"

namespace plotpp{
	
	template<ForwardRange Tnames>
	class Piechart : public IPlot {
	public:
		template<ForwardRange Tvalues>
		Piechart(optional_ptr<Tnames> names, const Tvalues& values)
			: names_(std::move(names)) 
			, start_angles_()
			, end_angles_()
		{
			// set the fill style to solid
			this->fill_style.solid(0.7);
			
			// calculate start and stop angles
			size_t size = std::size(values);
			this->start_angles_.reserve(size);
			this->end_angles_.reserve(size);
			
			float sum = 0.f;
			for(const auto& elem : values){
				sum += static_cast<float>(elem);
			}
			
			float angle = 0.f;
			for(const auto& elem : values){
				this->start_angles_.push_back(angle);
				angle += static_cast<float>(elem)/sum * 360.f;
				this->end_angles_.push_back(angle);
			}
			this->end_angles_.back() = 360.f;
		}
		
		
		inline Piechart& label(const char* label) & {this->IPlot::label(label); return *this;}
		inline Piechart&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		inline Piechart& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		inline Piechart&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		inline Piechart& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		inline Piechart&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		inline LineType lineType() const {return this->line_type;}
		inline Piechart& lineType(LineType lt) & {this->line_type = lt; return *this;}
		inline Piechart&& lineType(LineType lt) && {this->line_type = lt; return std::move(*this);}
		
		inline float lineWidth() const {return this->line_width;}
		inline Piechart& lineWidth(float lw) & {this->line_width = lw; return *this;}
		inline Piechart&& lineWidth(float lw) && {this->line_width = lw; return std::move(*this);}
		
		inline const FillStyle& fill() const {return this->fill_style;}
		inline Piechart& fillSolid(float opacity = 1.0, bool transparent = false) & {this->fill_style.solid(opacity, transparent); return *this;}
		inline Piechart&& fillSolid(float opacity = 1.0, bool transparent = false) && {this->fill_style.solid(opacity, transparent); return std::move(*this);}
		inline Piechart& fillEmpty() & {this->fill_style.empty(); return *this;}
		inline Piechart&& fillEmpty() && {this->fill_style.empty(); return std::move(*this);}
		inline Piechart& fillPattern(int n) & {this->fill_style.pattern(n); return *this;}
		inline Piechart&& fillPattern(int n) && {this->fill_style.pattern(n); return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		void printData([[maybe_unused]]FILE* fptr) const {}
		
		void printPlot(FILE* fptr) const {
			using NameItr = decltype(std::begin(*this->names_));
			NameItr nameItr; 
			NameItr nameEnd; 
			
			if(this->names_){
				nameItr = std::begin(*this->names_);
				nameEnd = std::end(*this->names_);
			}else{
				nameItr = nameEnd;
			}
			
			size_t i = 1;
			bool first_iteration = true;
			for(const auto && [start_angle, end_angle] : c9::zip(this->start_angles_, this->end_angles_)){
				if (first_iteration == false){
					fmt::print(fptr, ", \\\n     ");
				}
				first_iteration = false;
				
				// Circle data
				fmt::print(fptr, "'+' using (0):(0):(1):({:g}):({:g}) with circles", start_angle, end_angle);
			
				// Line Width, Dash and fill type
				fmt::print(fptr, " lw {:.2f} dt {:d} {}", 
				this->line_width, 
				static_cast<int>(this->lineType()),
				this->fill_style);
			
				// Title
				if(this->IPlot::label().empty()){
					if(nameItr != nameEnd){
						fmt::print(fptr, " title '{}'", *nameItr++);
					}else{
						fmt::print(fptr, " title '{:d}'", i++);
					}
				}else{
					if(nameItr != nameEnd){
						fmt::print(fptr, " title '{}: {}'", this->IPlot::label(), *nameItr++);
					}else{
						fmt::print(fptr, " title '{}: {:d}'", this->IPlot::label(), i++);
					}
				}
			}	

		}
		
	private:
		
		optional_ptr<Tnames> names_;
		std::vector<float> start_angles_;
		std::vector<float> end_angles_;
		
		float line_width = 1.5;
		LineType line_type = LineType::solid;
		FillStyle fill_style;
		
	};
	
	/*constructor helper*/
	
	template<PtrOrMoved U1, class U2>
	auto piechart(U1&& names, const U2& values) 
	{
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		return Piechart<Tx>(optional_ptr<Tx>(std::forward<U1>(names)), values);
	}
	
	template<PtrOrMoved U1, class U2>
	auto piechart(U1&& names, const U2* values) 
	{
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		return Piechart<Tx>(optional_ptr<Tx>(std::forward<U1>(names)), *values);
	}
	
	template<PtrOrMoved U2>
	auto piechart(const U2& values) {
		using Tx = std::vector<int>; // placeholder type
		return Piechart<Tx>(optional_ptr<Tx>(), values);
	}
	
	template<PtrOrMoved U2>
	auto piechart(const U2* values) {
		using Tx = std::vector<int>; // placeholder type
		return Piechart<Tx>(optional_ptr<Tx>(), *values);
	}

}