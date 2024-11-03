#include <plotpp.hpp>
#include <vector>
#include <cmath>

std::vector<float> linspace(float from, float to, size_t N){
	std::vector<float> result;
	result.reserve(N);
	for (size_t i = 0; i < N; ++i) result.emplace_back(((to - from) * i) / N + from);
	return result;
}


std::vector<float> apply(const std::vector<float>& x_range, float (*func)(float x)){
	std::vector<float> result;
	result.reserve(x_range.size());
	for(const float x : x_range){
		const float y = func(x);
		result.emplace_back(y);
	}
	return result;
}

std::vector<float> sin(const std::vector<float>& x) {return apply(x, std::sin);}
std::vector<float> cos(const std::vector<float>& x) {return apply(x, std::cos);}
std::vector<float> tan(const std::vector<float>& x) {return apply(x, std::sinh);}

int main(){
	using namespace plotpp;
	
	const auto x = linspace(-3.1415, 3.1415, 50);
	
	/*
	The plotting devices are crafted in a way to avoid unnecessary copies. 
	Data is taken by reference/pointers and optionally owned.
	
		pass by:
			* lvalue reference 	--> plot will store a pointer to the data
			* rvalue reference	--> plot will move the data into a smart_pointer that holds the data
			* shared_ptr 		--> plot will take the smart_pointer
			* unique_ptr		--> plot will move the unique_ptr
			* raw_ptr			--> plot will store a pointer to the data
	*/
	Multiplot mplt(2, 2, "Multiplot");
	mplt.at(0, 0).add(line(x, sin(x)).label("Top-Left"));
	mplt.at(0, 1).add(
		points(
			std::make_shared<std::vector<float>>(x), 
			std::make_unique<std::vector<float>>(cos(x))
		).label("Top-Right")
	);
	mplt.at(1, 1).add(line(&x, tan(x)).label("Bottom-Right"));
	mplt.show();
	mplt.save("multiplot.jpg");
	
	return 0;
}