#include <plotpp.hpp>

int main() {
	using namespace plotpp;

	float ydata[] = {5.0, 6.5, 7.8, 6.0, 7.0};
	
	float y2data[] = {3.0, 6.5, 9.8, 10.0, 2.0};
	float x2data[] = {3, 4, 5, 7, 8};
	
	const char* names[] = {"house", "bottel", "basket", "number", "apple"};
	
	Figure fig("Boxes");
	fig.add(Boxes(ydata, "boxes1"));
	fig.add(Boxes(x2data, y2data, "boxes2"));
	fig.show();
	
	Figure fig2("Boxes with text");
	fig2.add(Boxes(names, ydata, true, "boxes with names"));
	fig2.show();

    return 0;
}