#pragma once

#include <ostream>
#include <iterator>
#include <vector>

#include "plotpp/IPlot.hpp"
#include "plotpp/PointType.hpp"

namespace plotpp{

	template<class Tx, class Ty>
	class Points : public IPlot{
	public:
		// ---- Constructors ----
		
		Points(smartest_pointer<Tx> x, smartest_pointer<Ty> y)
			: x_(std::move(x))
			, y_(std::move(y)) 
			{}
		
		Points(Points const &) = default;
		Points(Points&&) = default;
		Points& operator=(Points const &) = default;
		Points& operator=(Points&&) = default;
		
		// ---- setters getters ----
		
		PointType pointType() const {return this->point_type;}
		Points& pointType(PointType pt) & {this->point_type = pt; return *this;}
		Points&& pointType(PointType pt) && {this->point_type = pt; return std::move(*this);}
		
		float pointSize() const {return this->point_size;}
		Points& pointSize(float ps) & {this->point_size = ps; return *this;}
		Points&& pointSize(float ps) && {this->point_size = ps; return std::move(*this);}
		
		// ---- IPlot overloads ----
		
		virtual void printPlot(std::ostream& stream) const override {
			stream << "using 1:2 with points"
					<< " ps " << this->pointSize() 
					<< " pt " << static_cast<int>(this->pointType())
					<< " title '" << this->IPlot::label() << "'";
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
		
		Points& label(const char* label) & {this->IPlot::label(label); return *this;}
		Points&& label(const char* label) && {this->IPlot::label(label); return std::move(*this);}
		Points& label(std::string_view label) & {this->IPlot::label(label); return *this;}
		Points&& label(std::string_view label) && {this->IPlot::label(label); return std::move(*this);}
		Points& label(std::string&& label) & {this->IPlot::label(label); return *this;}
		Points&& label(std::string&& label) && {this->IPlot::label(std::move(label)); return std::move(*this);}
		
	private:
		smartest_pointer<Tx> x_;
		smartest_pointer<Ty> y_;
		//Color color
		float point_size = 1.0;
		PointType point_type = PointType::CircleFilled;
		/*TODO: LineColor*/
		
	};
	
	/*constructor helper*/
	template<typename U1, typename U2>
	auto points(U1&& x, U2&& y) {
		using Tx = remove_ptr_t<std::remove_reference_t<U1>>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Points<Tx, Ty>(
					smartest_pointer<Tx>(std::forward<U1>(x)), 
					smartest_pointer<Ty>(std::forward<U2>(y)));
	}
	
	
	/*constructor helper*/
	template<typename U2>
	auto points(U2&& y) {
		using Tx = std::vector<int>;
		using Ty = remove_ptr_t<std::remove_reference_t<U2>>;
		return Points<Tx, Ty>(
					smartest_pointer<Tx>(), 
					smartest_pointer<Ty>(std::forward<U2>(y)));
	}

}