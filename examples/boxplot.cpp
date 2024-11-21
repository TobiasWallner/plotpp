#include <plotpp.hpp>
#include <iostream>
int main(){
	using namespace plotpp;
	
	
	int data1[] = {8, 10, 10, 12, 9, 11};
	int data2[] = {9, 12, 11, 10, 13};
	int data3[] = {11, 14, 12, 10, 15};
	
	auto fig = Figure("Boxplots");
	fig.add(boxplot(&data1));
	fig.add(boxplot(2, &data2));
	fig.add(boxplot(3, &data3));
	fig.show();
	
	return 0;
	
}