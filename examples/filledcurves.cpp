#include <plotpp.hpp>

int main(){
	using namespace plotpp;
	
	float x[] = {-1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1,
                  0.0,  0.1,  0.2,  0.3,  0.4,  0.5,  0.6,  0.7,  0.8,  0.9,  1.0};
    float sin[] = {-0.8415, -0.7833, -0.7174, -0.6442, -0.5646, -0.4794, -0.3894, -0.2955, -0.1987, -0.0998,
                    0.0000,  0.0998,  0.1987,  0.2955,  0.3894,  0.4794,  0.5646,  0.6442,  0.7174,  0.7833,  0.8415};
    float tan[] = {-1.5574, -1.2602, -1.0296, -0.8423, -0.6841, -0.5463, -0.4228, -0.3093, -0.2027, -0.1003,
                    0.0000,  0.1003,  0.2027,  0.3093,  0.4228,  0.5463,  0.6841,  0.8423,  1.0296,  1.2602,  1.5574};

	Figure("filled curves sin-tan")
		.add(filledcurves(&x, &sin, &tan).color(0xf00000).label("sin-tan"))
		.add(line(&x, &sin).label("sin").lineWidth(2))
		.add(line(&x, &tan).label("tan").lineWidth(2))
		.grid()
		.show()
		.save("filledcurves-plot.svg");
	
	return 0;
}