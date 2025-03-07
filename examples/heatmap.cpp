#include <vector>
#include <plotpp.hpp>
#include <cmath>

double sinc(double x){
	if(x == 0.0){
		return 1.0;
	}else{
		return std::sin(x)/x;
	}
}

int main() {
	using namespace plotpp;

	// construct heatmap from 2D array (alternatively matrix-types work too)
	const size_t rows = 16;
	const size_t columns = 25;
	double array[rows][columns] = {};
	
	for(size_t r = 0; r < rows; r++){
		for(size_t c = 0; c < columns; c++){
			double x = r + 0.5 - rows/2;
			double y = c + 0.5 - columns/2;
			array[r][c] = sinc(std::sqrt(x*x + y*y));
		}
	}
	
	Figure fig("Heatmap");
	fig.add(heatmap(&array));
	fig.ylim(0, rows-1);
	fig.xlim(0, columns-1);
	fig.show();
	fig.save("headmap-plot.svg");

    return 0;
}