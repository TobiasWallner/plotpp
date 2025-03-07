#include <iostream>

template<typename ValueType = float>
std::vector<ValueType> linspace(ValueType from, ValueType to, size_t N){
	std::vector<ValueType> result;
	result.reserve(N);
	for (size_t i = 0; i < N; ++i) result.emplace_back(((to - from) * i) / (N-1) + from);
	return result;
}

template<class function, typename ValueType = float>
std::vector<typename std::invoke_result<function, ValueType>::type> apply_func(const std::vector<ValueType>& x_range, function&& func){
	std::vector<typename std::invoke_result<function, ValueType>::type> result;
	result.reserve(x_range.size()); 
	for(const ValueType& x : x_range){
		result.emplace_back(func(x));
	}
	return result;
}

template<class T>
std::vector<T> sin(const std::vector<T>& input) {
    std::vector<T> result;
    result.reserve(input.size()); // Pre-allocate memory
    for (const T& value : input) {
        result.push_back(std::sin(value)); // Convert degrees to radians and apply sin
    }
    return result;
}
