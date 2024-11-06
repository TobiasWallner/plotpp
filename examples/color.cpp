#include <plotpp.hpp>
#include <cmath>
#include <functional>
#include <format>

std::vector<float> linspace(float from, float to, size_t N){
	std::vector<float> result;
	result.reserve(N);
	for (size_t i = 0; i < N; ++i) result.emplace_back(((to - from) * i) / N + from);
	return result;
}

template<class function>
std::vector<float> apply(const std::vector<float>& x_range, function&& func){
	std::vector<float> result;
	result.reserve(x_range.size());
	for(const float x : x_range){
		const float y = func(x);
		result.emplace_back(y);
		
	}
	return result;
}

void plot_sin_with_color_palette(std::string title, const std::array<plotpp::Color, 9>& color_palette){
	using namespace plotpp;
	
	const auto x = linspace(-3.1415, 3.1415, 100);
	
	Figure fig(std::move(title));
	for(int i = 0; i < 9; ++i){
		float f = (i/10.+1.);
		auto function = [f](float x) -> float {return std::sin(x * f);};
		const auto y = apply(x, function);
		fig.add(line(&x, std::move(y)).lineWidth(2.5).color(color_palette[i]).label(std::format("sin({:.1f} x)", f)));
	}
	fig.show();
}

int main() {
	using namespace plotpp;
	
	plot_sin_with_color_palette("magma", colors::magma);
	plot_sin_with_color_palette("inferno", colors::inferno);
	plot_sin_with_color_palette("viridis", colors::viridis);
	
	return 0;
	
}