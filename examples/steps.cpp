#include <plotpp.hpp>

int main(){
	using namespace plotpp;
	
	std::vector<int> randomInts = {42, 7, 19, 73, 88, 12, 5, 99};
	std::vector<float> randomFloats = {31.4f, 27.1f, 16.1f, 46.7f, 58.9f, 72.3f};
	
	Figure("steps")
		.add(steps(std::move(randomInts)))
		.add(steps(std::move(randomFloats)).color(0.5, 0.5, 0.1).fill())
		.show();
	
	return 0;
}