#pragma once

#include <ostream>
#include <iterator>
#include <optional>

#include "plotpp/IPlot.hpp"
#include "plotpp/DataRelation.hpp"
#include "plotpp/ArrowHeadStyle.hpp"

namespace plotpp{
	
	template<class Tx1, class Ty1, class Tx2, class Ty2>
	class Arrows : public IPlot{
	public:

		Arrows(optional_ptr<const Tx1> x1, optional_ptr<const Ty1> y1, optional_ptr<const Tx2> x2, optional_ptr<const Ty2> y2)
			: x1_(std::move(x1))
			, y1_(std::move(y1)) 
			, x2_(std::move(x2))
			, y2_(std::move(y2)) 
			{}
		
		// ---- setters getters ----
		
		Arrows& label(const char* label) & {this->IPlot::label(label); return *this;}
		Arrows&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		Arrows& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		Arrows&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		Arrows& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		Arrows&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		float lineWidth() const {return this->line_width;}
		Arrows& lineWidth(float lw) & {this->line_width = lw; return *this;}
		Arrows&& lineWidth(float lw) && {this->line_width = lw; return std::move(*this);}
		
		DataRelation dataRelation() const {return this->data_relation;}
		Arrows& dataRelation(float dr) & {this->data_relation = dr; return *this;}
		Arrows&& dataRelation(float dr) && {this->data_relation = dr; return std::move(*this);}
		
		ArrowHeadStyle arrowHeadStyle() const {return this->arrow_head_style;}
		Arrows& arrowHeadStyle(float ahs) & {this->arrow_head_style = ahs; return *this;}
		Arrows&& arrowHeadStyle(float ahs) && {this->arrow_head_style = ahs; return std::move(*this);}
		
		Color color() const {return this->opt_color.value_or(Color(0,0,0));}
		Arrows& color(Color col) & {this->opt_color = col; return *this;}
		Arrows&& color(Color col) && {this->opt_color = col; return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		virtual void printPlot(FILE* fptr) const {
			fmt::print(fptr, "$d{:d}", this->IPlot::uid());
			
			if(this->dataRelation() == DataRelation::absolute){
				fmt::print(fptr, " using 1:2:(($3)-($1)):($4-$2)");
			}else{
				fmt::print(fptr, " using 1:2:3:4");
			}
			
			if(this->dataRelation() == DataRelation::polar){
				fmt::print(fptr, " with arrows");
			}else{
				fmt::print(fptr, " with vectors");
			}
			
			fmt::print(fptr, " {} lw {:02f}", this->arrowHeadStyle(), this->lineWidth());
			
			if(this->opt_color){
				fmt::print(fptr, " lc rgb '#{:06x}'", this->opt_color.value().to_int32());
			}
			
			if(this->IPlot::label().empty()){
				fmt::print(fptr, " notitle");
			}else{
				fmt::print(fptr, " title '{}'", this->IPlot::label());
			}
		}
		
		virtual void printData(FILE* fptr) const {
			fmt::print(fptr, "$d{:d} << e\n", this->IPlot::uid());
			auto x1itr = std::begin(*x1_);
			auto y1itr = std::begin(*y1_);
			auto x2itr = std::begin(*x2_);
			auto y2itr = std::begin(*y2_);
			for(; x1itr != std::end(*x1_) && y1itr != std::end(*y1_) && x2itr != std::end(*x2_) && y2itr != std::end(*y2_)
				; (void)++x1itr, (void)++y1itr, (void)++x2itr, (void)++y2itr){
				fmt::print(fptr, "{} {} {} {}\n", *x1itr, *y1itr, *x2itr, *y2itr);
			}
			fmt::print(fptr, "e\n");
		}
		
	private:
		optional_ptr<const Tx1> x1_;
		optional_ptr<const Ty1> y1_;
		optional_ptr<const Tx2> x2_;
		optional_ptr<const Ty2> y2_;
		std::optional<Color> opt_color = std::nullopt;
		DataRelation data_relation = DataRelation::relative; // relation from [x1, y1] to [x2, y2]
		float line_width = 1.5;
		ArrowHeadStyle arrow_head_style = ArrowHeadStyle::filled_head;
	};
	
	/*constructor helper*/
	template<PtrOrMoved U1, PtrOrMoved U2, PtrOrMoved U3, PtrOrMoved U4>
	auto arrows(U1&& x1, U2&& y1, U3&& x2, U4&& y2) {
		using Tx1 = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty1 = remove_ptr_t<std::remove_reference_t<U2>>;
		using Tx2 = remove_ptr_t<std::remove_reference_t<U3>>;
		using Ty2 = remove_ptr_t<std::remove_reference_t<U4>>;
		return Arrows<Tx1, Ty1, Tx2, Ty2>(
					optional_ptr<const Tx1>(std::forward<U1>(x1)),
					optional_ptr<const Ty1>(std::forward<U2>(y1)),
					optional_ptr<const Tx2>(std::forward<U3>(x2)),
					optional_ptr<const Ty2>(std::forward<U4>(y2)));
	}
	
}