#include <plotpp.hpp>

int main() {
	using namespace plotpp;
	
	int xdata[] = {0, 1, 2, 3, 4, 5, 6};
	float ydata[] = {5.0, 6.5, 7.8, 6.0, 7.0};
	
	float y2data[] = {3.0, 6.5, 9.8, 10.0, 2.0};
	int x2data[] = {3, 4, 5, 7, 8};
	
	const char* names[] = {"house", "bottel", "basket", "number", "apple"};
	
	Figure fig("Boxes");
	fig.add(boxes(xdata, ydata, "boxes1"));
	fig.add(boxes(x2data, y2data, "boxes2"));
	fig.show();
	fig.save("script.gp");

	Figure fig2("Boxes with text");
	fig2.xtics(names);
	fig2.add(boxes(xdata, ydata, "boxes with names"));
	fig2.show();

    return 0;
}