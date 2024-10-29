
#include <vector>

#include <plotpp.hpp>

// http://gnuplot.info/docs/Overview.html

// TODO: write examples for every plotting style, instead of having them all in the main function
// TODO: put opstream into its own GitHub repo

/* 	
http://gnuplot.info/docs/Plotting_Styles.html

	+ 2D Plots TODO:
	
		* box error bars
		* boxplotsx
		* candlesticks
		* pichart
		* filledcurves 
		* linespoints
		* redo xy-plots
			- (lines, points, linespoints, filledcurves, fillsteps, fsteps... - should all be the same class)
				- option: filled -> filledcurves
				- option: O1_interpolation -> lines
				- option: O0_interpolation_start -> fsteps
					- option: O0_interpolation_center -> histeps
				- option: impulses -> impulses
		* parallelaxes
		
	
	+ 3D Plots TODO:
		* 3D xyz plot
		* 3D boxes
		* contourfill
*/

template<size_t c, size_t r>
double at(double const (*array)[r][c], size_t row, size_t col){
	return (*array)[row][col];
}



int main() {

	
//	{
//		std::vector<double> x(20);
//		for(size_t i=0; i < x.size(); ++i) x[i] = i;
//		
//		std::vector<double> y1(20);
//		for(size_t i=0; i < y1.size(); ++i) y1[i] = 1./i*30;
//		
//		std::vector<double> y2(20);
//		for(size_t i=0; i < y2.size(); ++i) y2[i] = 1./(i*i)*30;
//		
//		double array[/*rows*/4][/*columns*/3] = {
//			{1, 2, 3},
//			{11, 12, 13},
//			{21, 22, 23},
//			{31, 32, 33}
//		};
//
//		double arrow_x1[] = {-1, -2, -3, -4, -5};
//		double arrow_y1[] = {-1, -2, -1, -2, -3};
//		double arrow_x2[] = {-2, -3, -4, -5, -6};
//		double arrow_y2[] = {-3, -4, -2, -3, -5};
//		
//		Figure fig("Title");
//		fig.legend = true;
//		
//		//fig.add(ImageFile("test_image_32x32.png"));
//		fig.add(Heatmap(array, "Heatmap"));
//		fig.add(Line(x, y1, "1/x*30"));
//		fig.add(Points(x, y2, "1/x^2*30"));
//		fig.add(Arrows(arrow_x1, arrow_y1, arrow_x2, arrow_y2, "arrow plot", DataRelation::relative));
//		
//		fig.show();
//		fig.save("script.gp");
//	}
	
//	{
//		std::vector<double> x(20);
//		for(size_t i=0; i < x.size(); ++i) x[i] = i;
//		
//		std::vector<double> y(20);
//		for(size_t i=0; i < y.size(); ++i) y[i] = 1./i*10;
//		
//		std::vector<double> yerrors(20);
//		for(size_t i=0; i < yerrors.size(); ++i) yerrors[i] = 1;
//		
//		std::vector<double> y2(20);
//		for(size_t i=0; i < y2.size(); ++i) y2[i] = i/static_cast<double>(y2.size())*10;
//		
//		std::vector<double> x2errors(20);
//		for(size_t i=0; i < x2errors.size(); ++i) x2errors[i] = i/static_cast<double>(x2errors.size()) + 0.5;
//		
//		Figure fig("Points with error Bars");
//		fig.add(XError(x, y, x2errors));	
//		fig.add(YError(x, y2, yerrors));
//		fig.add(XYError(y2, x, x2errors, yerrors));
//		fig.show();	
//	}
	
	
	
    return 0;
}