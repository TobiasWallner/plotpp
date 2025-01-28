#include <iostream>

template<typename ValueType = float>
inline std::vector<ValueType> linspace(ValueType from, ValueType to, size_t N){
	std::vector<ValueType> result;
	result.reserve(N);
	for (size_t i = 0; i < N; ++i) result.emplace_back(((to - from) * i) / N + from);
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