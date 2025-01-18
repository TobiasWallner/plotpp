#include <plotpp.hpp>
#include <cmath>
#include <functional>
#include <format>
#include <chrono>
#include <iostream>

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

template<size_t N>
void plot_sin_with_color_palette(std::string title, const std::array<plotpp::Color, N>& color_palette){
	using namespace plotpp;
	
	const auto x = linspace(-3.1415, 3.1415, 100);
	
	Figure fig(std::move(title));
	for(int i = 0; i < color_palette.size(); ++i){
		float f = i/10.;
		auto function = [f](float x) -> float {return std::sin(x + f);};
		const auto y = apply(x, function);
		fig.add(line(std::make_shared<decltype(x)>(x), std::move(y)).lineWidth(4).color(color_palette[i]).label(std::format("sin(x + {:.1f})", f)));
	}
	fig.show();
}

template<size_t N>
void plot_sin_with_mapped_palette(std::string title, const std::array<plotpp::Color, N>& color_palette){
	using namespace plotpp;
	
	const auto x = linspace(-3.1415, 3.1415, 100);
	
	Figure fig(std::move(title));
	for(int i = 0; i < 40; ++i){
		float f = i/20.;
		auto function = [f](float x) -> float {return std::sin(x + f);};
		const auto y = apply(x, function);
		fig.add(line(std::make_shared<decltype(x)>(x), std::move(y)).lineWidth(2.5).color(map(i/40.f, color_palette)).label(std::format("sin(x + {:.2f})", f)));
	}
	fig.show();
}


int main() {
	using namespace plotpp;
	
	auto start = std::chrono::high_resolution_clock::now();
	
	plot_sin_with_mapped_palette("Special: plasma mapped", color_map::plasma);
	
	// --------------- special color ranges ---------------
	plot_sin_with_color_palette("Special: magma", color_map::magma);
	plot_sin_with_color_palette("Special: inferno", color_map::inferno);
	plot_sin_with_color_palette("Special: viridis", color_map::viridis);
	plot_sin_with_color_palette("Special: plasma", color_map::plasma);
	plot_sin_with_color_palette("Special: jet", color_map::jet);
	plot_sin_with_color_palette("Special: bentcoolwarm", color_map::bentcoolwarm);
	plot_sin_with_color_palette("Special: moreland", color_map::moreland);
	plot_sin_with_color_palette("Special: chromajs", color_map::chromajs);
	plot_sin_with_color_palette("Special: parula", color_map::parula);
	plot_sin_with_color_palette("Special: sand", color_map::sand);
	plot_sin_with_color_palette("Special: turbo", color_map::turbo);
	plot_sin_with_color_palette("Special: rainbow", color_map::rainbow);
	
	// --------------- qualitative color sets ----------------
	
	plot_sin_with_color_palette("Qualitative: set1", color_map::set1);
	plot_sin_with_color_palette("Qualitative: set1 light", color_map::set1_light);
	plot_sin_with_color_palette("Qualitative: set2", color_map::set2);
	plot_sin_with_color_palette("Qualitative: set2 light", color_map::set2_light);
	plot_sin_with_color_palette("Qualitative: set3", color_map::set3);
	plot_sin_with_color_palette("Qualitative: matlab", color_map::matlab);
	
	// ---------------- color fades -------------------
	plot_sin_with_color_palette("Fade: blues", color_map::blues);
	plot_sin_with_color_palette("Fade: blue greens", color_map::blue_greens);
	plot_sin_with_color_palette("Fade: blue purples", color_map::blue_purples);
	plot_sin_with_color_palette("Fade: green blues", color_map::green_blues);
	plot_sin_with_color_palette("Fade: greens", color_map::greens);
	plot_sin_with_color_palette("Fade: greys", color_map::greys);
	plot_sin_with_color_palette("Fade: oranges", color_map::oranges);
	plot_sin_with_color_palette("Fade: orange red", color_map::orange_reds);
	plot_sin_with_color_palette("Fade: yellow orange red", color_map::yellow_orange_reds);
	plot_sin_with_color_palette("Fade: yellow orange brown", color_map::yellow_orange_browns);
	plot_sin_with_color_palette("Fade: yellow green blues", color_map::yellow_green_blues);
	plot_sin_with_color_palette("Fade: yellow greens", color_map::yellow_greens);
	plot_sin_with_color_palette("Fade: reds", color_map::reds);
	plot_sin_with_color_palette("Fade: red purples", color_map::red_purples);
	plot_sin_with_color_palette("Fade: yellow green blues", color_map::yellow_green_blues);
	plot_sin_with_color_palette("Fade: purples", color_map::purples);
	plot_sin_with_color_palette("Fade: purple reds", color_map::purple_reds);
	plot_sin_with_color_palette("Fade: purple blue greens", color_map::purple_blue_greens);
	plot_sin_with_color_palette("Fade: purple blues", color_map::purple_blues);
	
	
	// ---------------- divergin colors ----------------- 
	plot_sin_with_color_palette("Divergin: brown white bluegreen", color_map::brown_white_bluegreen);
	plot_sin_with_color_palette("Divergin: green white purple", color_map::green_white_purple);
	plot_sin_with_color_palette("Divergin: red yellow green", color_map::red_yellow_green);
	plot_sin_with_color_palette("Divergin: red yellow blue", color_map::red_yellow_blue);
	plot_sin_with_color_palette("Divergin: red white grey", color_map::red_white_grey);
	plot_sin_with_color_palette("Divergin: red white blue", color_map::red_white_blue);
	plot_sin_with_color_palette("Divergin: orange white purple", color_map::orange_white_purple);
	plot_sin_with_color_palette("Divergin: purple white green", color_map::purple_white_green);
	plot_sin_with_color_palette("Divergin: pink white yellowgreen", color_map::pink_white_yellowgreen);
	
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Process took " << duration << " us" << std::endl;
	
	return 0;
	
}