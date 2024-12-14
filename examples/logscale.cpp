#include <plotpp.hpp>

int main(){
	using namespace plotpp;
	
	double x[] = {0.0, 10.0, 100.0, 1000.0, 10000.0};
	
	Figure fig("logx");
	fig.add(line(&x, &x));
	fig.xLog();
	fig.show();
	
	fig.title("logy");
	fig.xLog(false);
	fig.yLog();
	fig.show();
	
	fig.title("logxy");
	fig.xLog();
	fig.yLog();
	fig.show();
	
	return 0;
	
}