# Figure
----

In header: `<plotpp/Figure.hpp>`  
In namespace: `plotpp::`

## Class Figure
----

```C++
class Figure;
```

Allows to plot a variety of different 2D plots.

Contains a general settings of a figure like the scaling of axes,
a collection of plots and functions like `.show()` to display them or `.save()` to store them.

Under the hood the Figure will handle the communication with [Gnuplot](http://www.gnuplot.info/) over pipes directly,
so no temporary files will be created or stored, that convolute your directories.

### Constructors

```C++
/* 1 */Figure() = default;
/* 2 */Figure(const Figure&) = delete;
/* 3 */Figure(Figure&&) = default;
```

Figures are default constructable, and default copy constructable

Figure(std::string title_str);
Figure(Text title, Text xlabel, Text ylabel);

### Figure.title()

```C++
Figure& title(const Text& title);
Figure& title(Text&& title);
```

Set a formatted title for the Figure.

**Parameter:** [Text](TODO) **title**: The new title of the Figure  

**Returns:** A reference to the Figure for method chaining

### Figure.xLabel()

```C++
Figure& xLabel(const Text& xlabel);
Figure& xLabel(Text&& xlabel);
```

Set the label of the x-axis.

**Parameter:** [Text](TODO) **xlabel**: The new label of the x axis

**Returns:** A reference to the Figure for method chaining

### Figure.yLabel()

```C++
Figure& yLabel(const Text& xlabel);
Figure& yLabel(Text&& xlabel);
```

Set the label of the y-axis.

**Parameter:** [Text](TODO) **xlabel**: The new label of the y axis

**Returns:** A reference to the Figure for method chaining

### Figure.xMin()

```C++
Figure& xMin(float v);
```

Sets the minimal value/starting point of the x-axis.
The initialisation value for xMin is -1.

**Parameter:** *float* **v**: new minimal position of the x-axis.

**Returns:** A reference to the Figure for method chaining

### Figure.xMax()

```C++
Figure& xMax(float v);
```
Sets the maximal value/end point of the x-axis.
The initialisation value for xMax is +1.

**Parameter:** *float* **v**: new maximal position of the x-axis.

**Returns:** A reference to the Figure for method chaining

### Figure.yMin()

```C++
Figure& yMin(float v);
```

Sets the minimal value/start point of the y-axis.
The initialisation value for yMin is -1.

**Parameter:** *float* **v**: new minimal position of the y-axis.

**Returns:** A reference to the Figure for method chaining

### Figure.yMax()

```C++
Figure& yMax(float v);
```

Sets the maximal value/end point of the y-axis.
The initialisation value for yMax is +1.

**Parameter:** *float* **v**: new maximal position of the y-axis.

**Returns:** A reference to the Figure for method chaining

### Figure.xLim()

```C++
Figure& xLim(float x_min, float x_max);
```

Sets the minimal and maximal limits of the x-axis.
The initialisation value for \[xMin, xMax] is \[-1, +1].

**Parameter:** 

- *float* **x_min**: new minimal position of the x-axis.
- *float* **x_max**: new maximal position of the x-axis.

**Returns:** A reference to the Figure for method chaining

### Figure.yLim()

```C++
Figure& yLim(float y_min, float y_max)
```

Sets the minimal and maximal limits of the y-axis.
The initialisation value for \[yMin, yMax] is \[-1, +1].

**Parameter:** 

- *float* **y_min**: new minimal position of the y-axis.
- *float* **y_max**: new maximal position of the y-axis.

**Returns:** A reference to the Figure for method chaining

### Figure.lim()

```C++
Figure& lim(float x_min, float x_max, float y_min, float y_max)
```

Sets the minimal and maximal limits for the x- and y-axis.
The initialisation value for \[xMin, xMax, yMin, yMax] is \[-1, +1, -1, +1].

**Parameter:** 

- *float* **x_min**: new minimal position of the x-axis.
- *float* **x_max**: new maximal position of the x-axis.
- *float* **y_min**: new minimal position of the y-axis.
- *float* **y_max**: new maximal position of the y-axis.

**Returns:** A reference to the Figure for method chaining

### Figure.xAutoscale()

```C++
Figure& xAutoscale(bool b = true);
```

Enables or disables autoscaling for the x-axis. If enabled the x-limit will be automatically determined from the data. If disabled the scaling for the x-limits (set via [xLim()](Figure.md#figure_xlim)) will be taken instead.

**Parameter:** *bool* **b:** if

- `true` enables autoscaling
- `false` disables autoscaling

**Returns:** A reference to the Figure for method chaining

### Figure.yAutoscale()

```C++
Figure& yAutoscale(bool b = true);
```

Enables or disables autoscaling for the y-axis. If enabled the y-limit will be automatically determined from the data. If disabled the scaling for the y-limits (set via [yLim()](Figure.md#figure_xlim)) will be taken instead.

**Parameter:** *bool* **b:** if

- `true` enables autoscaling
- `false` disables autoscaling

**Returns:** A reference to the Figure for method chaining

### Figure.yAutoscale()

```C++
Figure& autoscale(bool b = true);
```

Enables or disables autoscaling for both axis. If enabled the axis limit will be automatically determined from the data. If disabled the scaling for the both limits (set via [lim()](Figure.md#figure_lim)) will be taken instead.

**Parameter:** *bool* **b:** if

- `true` enables autoscaling
- `false` disables autoscaling

**Returns:** A reference to the Figure for method chaining

### Figure.xLog()

```C++
Figure& xLog(bool b = true);
```

Enables (default) or disables logarithmic x-axes.
The default base of the logarithm is 10.

**Parameter:** 

- *bool* **b:** if 
	- `true`: enables logarithmic x-axes
	- `false`: disables logarithmic x-axes

**Returns:** A reference to the Figure for method chaining


### Figure.yLog()

```C++
Figure& yLog(bool b = true);
```

Enables (default) or disables logarithmic x-axes.
The default base of the logarithm is 10.

**Parameter:** *bool* **b:** if 
	- `true`: enables logarithmic x-axes
	- `false`: disables logarithmic x-axes

**Returns:** A reference to the Figure for method chaining

### Figure.xLogBase()

```C++
Figure& xLogBase(float base);
```

Sets the base for logarithmic scaling and also activates log axes if not already.

**Parameter:** *float* **base:** The new base of logarithm for the x-axis

**Returns:** A reference to the Figure for method chaining

### Figure.yLogBase()

```C++
Figure& yLogBase(float base);
```

Sets the base for logarithmic scaling and also activates log axes if not already.

**Parameter:** *float* **base:** The new base of logarithm for the x-axis

**Returns:** A reference to the Figure for method chaining

### Figure.xReverse()

```C++
Figure& xReverse(bool b = true);
```

Reverses/Flipps the x-axis.

**Parameter:** *bool* **b:** if 

- `true` (=default) the x-axis will be reversed (aka. ascends from right to left)
- `false` the x-axis will be normal/conventional (aka. ascends from left to right)

**Returns:** A reference to the Figure for method chaining

### Figure.yReverse()

```C++
Figure& yReverse(bool b = true);
```

Reverses/Flipps the y-axis.

**Parameter:** *bool* **b:** if 

- `true` (=default) the x-axis will be reversed (aka. ascends from top to bottom)
- `false` the x-axis will be normal/conventional (aka. ascends from bottom to top)

**Returns:** A reference to the Figure for method chaining

### Figure.xGrid()

TODO: The reset