set term tikz standalone color size 8in,8in font ",4"
set ylabel "Rank" offset -5,0
set xlabel "Score" offset 0,-5
#set term png size 1200,600 font ",8"
unset key
set yrange[129:0]
set xrange[0:129]
set pointsize 0.5
set bar 0.5
set xtics nomirror
set ytics nomirror

set title "2014 Week 1"
set out "week1.tex"
plot 'plot-2014-week1.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week1.txt'u 2:1:3  w xe

set title "2014 Week 2"
set out "week2.tex"
plot 'plot-2014-week2.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week2.txt'u 2:1:3  w xe

set title "2014 Week 3"
set out "week3.tex"
plot 'plot-2014-week3.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week3.txt'u 2:1:3  w xe

set title "2014 Week 4"
set out "week4.tex"
plot 'plot-2014-week4.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week4.txt'u 2:1:3  w xe

set title "2014 Week 5"
set out "week5.tex"
plot 'plot-2014-week5.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week5.txt'u 2:1:3  w xe

set title "2014 Week 6"
set out "week6.tex"
plot 'plot-2014-week6.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week6.txt'u 2:1:3  w xe

set title "2014 Week 7"
set out "week7.tex"
plot 'plot-2014-week7.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week7.txt'u 2:1:3  w xe

set title "2014 Week 8"
set out "week8.tex"
plot 'plot-2014-week8.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week8.txt'u 2:1:3  w xe

set title "2014 Week 9"
set out "week9.tex"
plot 'plot-2014-week9.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week9.txt'u 2:1:3  w xe

set title "2014 Week 10"
set out "week10.tex"
plot 'plot-2014-week10.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week10.txt'u 2:1:3  w xe

set title "2014 Week 11"
set out "week11.tex"
plot 'plot-2014-week11.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week11.txt'u 2:1:3  w xe

set title "2014 Week 12"
set out "week12.tex"
plot 'plot-2014-week12.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week12.txt'u 2:1:3  w xe

set title "2014 Week 13"
set out "week13.tex"
plot 'plot-2014-week13.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week13.txt'u 2:1:3  w xe

set title "2014 Week 14"
set out "week14.tex"
plot 'plot-2014-week14.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week14.txt'u 2:1:3  w xe

set title "2014 Week 15"
set out "week15.tex"
plot 'plot-2014-week15.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week15.txt'u 2:1:3  w xe

set title "2014 Week 16"
set out "week16.tex"
plot 'plot-2014-week16.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week16.txt'u 2:1:3  w xe
