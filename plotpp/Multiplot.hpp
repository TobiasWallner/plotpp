/*

set terminal pngcairo size 1000,500
set output 'side_by_side.png'

set multiplot layout 1,2 title "Two Side-by-Side Plots"

# First plot
set title "Sine Function"
set xlabel "x"
set ylabel "sin(x)"
plot sin(x) with lines lw 2 lc rgb "blue"

# Second plot
set title "Cosine Function"
set xlabel "x"
set ylabel "cos(x)"
plot cos(x) with lines lw 2 lc rgb "red"

unset multiplot

*/

/*

For empty plots just print a point into the middle with

$empty << EOD
0 0
EOD

plot $empty with points

*/