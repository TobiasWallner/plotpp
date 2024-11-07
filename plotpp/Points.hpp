#pragma once

#include <ostream>
#include <iterator>
#include <vector>
#include <optional>

#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"
#include "plotpp/Color.hpp"

namespace plotpp{

	template<class Tx, class Ty>
	class Points : public IPlot{
	public:
		// ---- Constructors ----
		
		Points(optional_ptr<Tx> x, optional_ptr<Ty> y)
			: x_(std::move(x))
			, y_(std::move(y)) 
			{}
		
		Points(Points const &) = default;
		Points(Points&&) = default;
		Points& operator=(Points const &) = default;
		Points& operator=(Points&&) = default;
		
		// ---- setters getters ----
		
		Points& label(const char* label) & {this->IPlot::label(label); return *this;}
		Points&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		Points& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		Points&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		Points& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		Points&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
		PointType pointType() const {return this->point_type;}
		Points& pointType(PointType pt) & {this->point_type = pt; return *this;}
		Points&& pointType(PointType pt) && {this->point_type = pt; return std::move(*this);}
		
		float pointSize() const {return this->point_size;}
		Points& pointSize(float ps) & {this->point_size = ps; return *this;}
		Points&& pointSize(float ps) && {this->point_size = ps; return std::move(*this);}
		
		Color color() const {return this->opt_color.value_or(Color(0,0,0));}
		Points& color(Color col) & {this->opt_color = col; return *this;}
		Points&& color(Color col) && {this->opt_color = col; return std::move(*this);}
		
		bool isAutoColor() const {return this->opt_color.has_value();}
		Points& setAutoColor() & {this->opt_color = std::nullopt; return *this;}
		Points&& setAutoColor() && {this->opt_color = std::nullopt; return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		virtual void printPlot(std::ostream& stream) const override {
			stream << "using 1:2 with points"
					<< " ps " << this->pointSize() 
					<< " pt " << static_cast<int>(this->pointType());
			
			if(this->opt_color){
				stream << " lc rgb \"#" << this->opt_color.value().to_hex() << "\"";
			}
			
			if(this->IPlot::label().empty()){
				stream << " notitle";
			}else{
				stream <<  " title '" << this->IPlot::label() << "'";
			}
			
		}
		
		virtual void printData(std::ostream& stream) const override {
			if(this->x_){
				auto xitr = std::begin(*x_);
				auto yitr = std::begin(*y_);
				
				for (; xitr != std::end(*x_) && yitr != std::end(*y_); ++xitr, (void)++yitr)
					stream << *xitr << ' ' << *yitr << '\n';	
			}else{
				size_t x = 0;
				auto yitr = std::begin(*y_);
				
				for (; yitr != std::end(*y_); ++x, (void)++yitr)
					stream << x << ' ' << *yitr << '\n';
			}
		}
		
		
		
	private:
		optional_ptr<Tx> x_;
		optional_ptr<Ty> y_;
		std::optional<Color> opt_color = std::nullopt;
		float point_size = 1.0;
		PointType point_type = PointType::CircleFilled;
		/*TODO: LineColor*/
		
	};
	
	/*constructor helper*/
	template<PtrOrMoved U1, PtrOrMoved U2>
	auto points(U1&& x, U2&& y) {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Points<Tx, Ty>(
					optional_ptr<Tx>(std::forward<U1>(x)), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}
	
	
	/*constructor helper*/
	template<PtrOrMoved U2>
	auto points(U2&& y) {
		using Tx = std::vector<int>; // placeholder type
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Points<Tx, Ty>(
					optional_ptr<Tx>(), 
					optional_ptr<Ty>(std::forward<U2>(y)));
	}

}