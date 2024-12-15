#pragma once

#include <exception>

namespace plotpp{
	class FillStyle{
	public:
		enum class Type{Empty, Solid, Pattern};
		
		inline void empty(){
			this->type_ = Type::Empty;
		}
		
		inline void solid(float opacity = 1.0, bool transparent = false){
			if(!(0.0 <= opacity && opacity <= 1.0)){
				throw std::invalid_argument(
					"Invalid argument for plotpp::FillStyle::solid(float opacity). "
					"'opacity' has to be within the range [0.0, 1.0]");
			}
			this->type_ = Type::Solid;
			this->opacity_ = opacity;
			this->transparent_ = transparent;
		}
		
		inline void pattern(int n){
			if(!(0 <= n && n <= 9)){
				throw std::invalid_argument(
					"Invalid argument for plotpp::FillStyle::pattern(int n). "
					"'n' has to be within the range [1, 8]");
			}
			this->pattern_ = n;
			this->type_ = Type::Pattern;
		}
		
		inline void border(bool b){
			this->border_ = b;
		}
		
		inline Type type() const {return this->type_;}
		
		inline float opacity() const {
			if(!(this->type_ == Type::Solid)){
				throw std::runtime_error(
					"plotpp::FillStyle is not of type 'Solid'. "
					"Thus the call to FillStyle::opacity() is invalid.");
			}
			return this->opacity_;
		}
		
		inline bool transparent() const {
			if(!(this->type_ == Type::Solid)){
				throw std::runtime_error(
					"plotpp::FillStyle is not of type 'Solid'. "
					"Thus the call to FillStyle::transparent() is invalid.");
			}
			return this->opacity_;
		}
		
		inline bool pattern() const {
			if(!(this->type_ == Type::Pattern)){
				throw std::runtime_error(
					"plotpp::FillStyle is not of type 'Solid'. "
					"Thus the call to FillStyle::pattern() is invalid.");
			}
			return this->pattern_;
		}
		
		inline bool border() const {
			return this->border_;
		}
		
	private:
		Type type_ = Type::Solid;
		float opacity_ = 0.5;
		int pattern_ = 1;
		bool transparent_ = false;
		bool border_ = true;	
		
	};
}

// fmt formater
namespace fmt{
	template<>
	struct formatter<plotpp::FillStyle>{
		
		constexpr auto parse(format_parse_context& ctx){
			return ctx.begin();
		}
		
		template<typename FormatContext>
		constexpr auto format(const plotpp::FillStyle& fill, FormatContext& ctx) const {
			switch(fill.type()){
				break; case plotpp::FillStyle::Type::Empty : {
					fmt::format_to(ctx.out(), 
						"fs empty {:s}", 
						fill.border() ? "border" : "noborder");
				}
				break; case plotpp::FillStyle::Type::Solid : {
					fmt::format_to(ctx.out(), 
						"fs {:s} solid {:.2f} {:s}", 
						fill.transparent() ? "transparent" : "",
						fill.opacity(),
						fill.border() ? "border" : "noborder");
				}
				break; case plotpp::FillStyle::Type::Pattern : {
					fmt::format_to(ctx.out(),
						"fs pattern {:d} {:s}",
						fill.pattern(),
						fill.border() ? "border" : "noborder");
				}
				 break; default: {
					throw std::invalid_argument("Invalid switch argument for type plotpp::FillStyle::Type");
				}
			};
			
			return ctx.out();
		}
		
	};
}