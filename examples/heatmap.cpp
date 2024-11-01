#include <vector>
#include <plotpp.hpp>

int main() {
	using namespace plotpp;

	{
		double array[/*rows*/4][/*columns*/3] = {
			{1, 2, 3},
			{11, 12, 13},
			{21, 22, 23},
			{31, 32, 33}
		};
		Figure fig("Heatmap from 2d array");
		fig.add(heatmap(array, "Heatmap"));
		fig.yreverse = true;
		fig.show();
	}
	
	{
		double array[4*3] = {
			1, 2, 3,
			11, 12, 13,
			21, 22, 23,
			31, 32, 33
		};
		Figure fig("Heatmap from contiguous memory");
		fig.add(heatmap(array, 4, 3, "Heatmap"));
		fig.yreverse = true;
		fig.show();
	}

    return 0;
}