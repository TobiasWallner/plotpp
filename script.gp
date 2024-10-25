set title '{/:Bold Title}' font ",20"
plot  'test_image_32x32.png' binary filetype=png with rgbalpha title '', \
	'-' matrix using 2:1:3 with image title 'Heatmap', \
	'-' using 1:2 with lines lw 1.5 dt 1 title '1/x*30', \
	'-' using 1:2 with points ps 1 pt 7 title '1/x^2*30', \
	'-' using 1:2:3:4 with vectors filled head lw 1.5 title 'arrow plot'

# Data for Heatmap
1 11 21 31 
2 12 22 32 
3 13 23 33 
e

# Data for 1/x*30
0 inf
1 30
2 15
3 10
4 7.5
5 6
6 5
7 4.28571
8 3.75
9 3.33333
10 3
11 2.72727
12 2.5
13 2.30769
14 2.14286
15 2
16 1.875
17 1.76471
18 1.66667
19 1.57895
e

# Data for 1/x^2*30
0 inf
1 30
2 7.5
3 3.33333
4 1.875
5 1.2
6 0.833333
7 0.612245
8 0.46875
9 0.37037
10 0.3
11 0.247934
12 0.208333
13 0.177515
14 0.153061
15 0.133333
16 0.117188
17 0.103806
18 0.0925926
19 0.0831025
e

# Data for arrow plot
-1 -1 -2 -3
-2 -2 -3 -4
-3 -1 -4 -2
-4 -2 -5 -3
-5 -3 -6 -5
e
