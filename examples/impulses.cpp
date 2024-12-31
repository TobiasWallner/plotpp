#include <plotpp.hpp>
#include <cmath>

std::vector<float> linspace(float from, float to, size_t number_of_points) {
    std::vector<float> result;
    if (number_of_points == 0) {
        return result;
    }

    result.reserve(number_of_points); // Pre-allocate memory
    float step = (to - from) / static_cast<float>(number_of_points);
    
    for (size_t i = 0; i < number_of_points; ++i) {
        result.push_back(from + i * step);
    }

    return result;
}

std::vector<float> sin(const std::vector<float>& input) {
    std::vector<float> result;
    result.reserve(input.size()); // Pre-allocate memory
    for (float value : input) {
        result.push_back(std::sin(value)); // Convert degrees to radians and apply sin
    }
    return result;
}

int main(){
	using namespace plotpp;
	
	auto x = linspace(-10, 10, 100);
	auto y = sin(x);
	
	Figure("Impulses").add(impulses(std::move(x), std::move(y))).show();
}