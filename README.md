Plotpp
======

A plotting library for C++ that uses Gnuplot as a backend.

Allows plotting from custom containers/vectors if they use std::begin() and std::end() iterators as well as plotting from built in arrays.

Still under heavy developement!

Requirements
============
- Gnuplot:  
	[Homepage](http://gnuplot.info/index.html)  
	[Windows Download](https://sourceforge.net/projects/gnuplot/files/gnuplot/)  
	[Linux install](https://riptutorial.com/gnuplot/example/11275/installation-or-setup):
	```
	sudo apt-get update
	sudo apt-get install gnuplot
	```
	Note: The project can be build without gnuplot,
	since this library will only communicate with gnuplot through pipes. 
	But you will need gnuplot to display the graphical plots.
	
Examples
========

You can see all examples in the `examples/` folder.

Line Plot
---------

```C++
Figure fig("Line Plot");
fig.add(line(x, y1, "1/x*30"));
fig.show();
fig.save("line-plot.png");
```
![Image of a line plot](images/line-plot.png)

Arrow Plot
----------

```C++
Figure fig("Arrow-Plot");
fig.add(arrows(arrow_x1, arrow_y1, arrow_x2, arrow_y2, "arrow plot", DataRelation::relative));
fig.show();
fig.save("arrows.svg");
```

![Image of an arrow plot](images/arrows.svg)

Multiplot
---------

```C++
Multiplot mplt(2, 2, "Multiplot");
mplt.at(0, 0).add(line(x, sin(x), "Top-Left"));
mplt.at(0, 1).add(line(x, cos(x), "Top-Right"));
mplt.at(1, 1).add(line(x, sinh(x), "Bottom-Right"));
mplt.show();
mplt.save("multiplot.jpg");
```

![Multiplot Image](images/multiplot.jpg)