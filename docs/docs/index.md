# **Welcome to Plotpp**

## **Plotpp**

A plotting library for C++ that uses Gnuplot as a backend.
Allows plotting from custom containers/vectors if they use `begin()` and `end()` iterators as well as plotting from built in arrays.

[Documentation](https://tobiaswallner.github.io/plotpp/)

## **Requirements**

- Gnuplot: [Homepage](http://gnuplot.info/index.html) [Windows Download](https://sourceforge.net/projects/gnuplot/files/gnuplot/) [Linux install](https://riptutorial.com/gnuplot/example/11275/installation-or-setup):  
	*Note: The project can be build without gnuplot,
	since this library will only communicate with gnuplot through pipes. 
	But you will need gnuplot to display the graphical plots.*
- C++20

## **Dependencies**

- {fmt}: [GitHub](https://github.com/fmtlib/fmt), [Documentation](https://fmt.dev/11.0/), [Conan](https://conan.io/center/recipes/fmt?version=)

## **Example**

=== "Output"
    ![Image of a line plot](example_output.png)

=== "Code"
    ```cpp
	#include <vector>
	#include <plotpp.hpp>

	#include "functions.hpp" //linspace, apply_func

	int main() {
		
		std::vector<float> x = linspace<float>(-2, 2, 100);
		std::vector<double> y = apply_func(x, [](double x){return -x + x * x * x;});
		
		using namespace plotpp;
		
		Figure fig("Line Plot from XY");
		fig.add(line(&x, std::move(y)).label("f1"));
		fig.grid();
		fig.show();
		fig.save("line-plot.svg");
		
		return 0;
	}
	```

## Integration

### CMake: [CPM](https://github.com/cpm-cmake/CPM.cmake)

Get and include the [CPM](https://github.com/cpm-cmake/CPM.cmake) script, then use [`CPMAddPackage()`](https://github.com/cpm-cmake/CPM.cmake?tab=readme-ov-file#usage) to add git repositories as libraries to your project

```cmake
include(CPM.cmake)

CPMAddPackage("gh:TobiasWallner/plotpp#main")

target_link_libraries(YOUR_PROJECT_NAME PUBLIC plotpp)
```

Optionally: set a download cache for your libraries by setting the environment variable `CPM_SOURCE_CACHE` to a directory of your choice

### CMake: [Add Subdirectory](https://cmake.org/cmake/help/latest/command/add_subdirectory.html)

clone plotpp into your project
```bash
git clone https://github.com/TobiasWallner/plotpp.git
```

include the project into CMake via [`add_subdirectory`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html)
```cmake
add_subdirectory(Path/to/plotpp)

target_link_libraries(YOUR_PROJECT_NAME PUBLIC plotpp)
```