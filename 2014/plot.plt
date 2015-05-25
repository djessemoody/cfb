set term tikz standalone color size 8in,8in font ",4"
set ylabel "Rank"
set xlabel "Score"
unset key
set xrange[0:129]
set pointsize 0.5
set bar 0.5
set xtics nomirror
set ytics nomirror
#set size square

set style line 11 lc rgb '#000000' lt 1

set term png size 2400,2400 font ",8"
set yrange[129:0]
set title "2014 Week 1"
set out "week1.png"
plot 'plot-2014-week1.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week1.txt'u 2:1:3 ls 1 w xe

set yrange[129:0]
set title "2014 Week 2"
set out "week2.png"
plot 'plot-2014-week2.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week2.txt'u 2:1:3  w xe

set title "2014 Week 3"
set out "week3.png"
plot 'plot-2014-week3.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week3.txt'u 2:1:3  w xe

set title "2014 Week 4"
set out "week4.png"
plot 'plot-2014-week4.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week4.txt'u 2:1:3  w xe

set title "2014 Week 5"
set out "week5.png"
plot 'plot-2014-week5.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week5.txt'u 2:1:3  w xe

set title "2014 Week 6"
set out "week6.png"
plot 'plot-2014-week6.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week6.txt'u 2:1:3  w xe

set title "2014 Week 7"
set out "week7.png"
plot 'plot-2014-week7.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week7.txt'u 2:1:3  w xe

set title "2014 Week 8"
set out "week8.png"
plot 'plot-2014-week8.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week8.txt'u 2:1:3  w xe

set title "2014 Week 9"
set out "week9.png"
plot 'plot-2014-week9.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week9.txt'u 2:1:3  w xe

set title "2014 Week 10"
set out "week10.png"
plot 'plot-2014-week10.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week10.txt'u 2:1:3  w xe

set title "2014 Week 11"
set out "week11.png"
plot 'plot-2014-week11.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week11.txt'u 2:1:3  w xe

set title "2014 Week 12"
set out "week12.png"
plot 'plot-2014-week12.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week12.txt'u 2:1:3  w xe

set title "2014 Week 13"
set out "week13.png"
plot 'plot-2014-week13.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week13.txt'u 2:1:3  w xe

set title "2014 Week 14"
set out "week14.png"
plot 'plot-2014-week14.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week14.txt'u 2:1:3  w xe

set title "2014 Week 15"
set out "week15.png"
plot 'plot-2014-week15.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week15.txt'u 2:1:3  w xe

#set title "2014 Week 16"
#set out "week16.png"
#plot 'plot-2014-week16.txt' u ($2+1):1:($4) w labels left, \
#	'plot-2014-week16.txt'u 2:1:3  w xe

set yrange[26:0]
unset xrange

set size square
set term png size 640,480 font ",8"
set title "2014 Week 1 - Top 25"
set out "week1-top25.png"
plot 'plot-2014-week1-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week1-top25.txt'u 2:1:3  w xe

set title "2014 Week 2 - Top 25"
set out "week2-top25.png"
plot 'plot-2014-week2-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week2-top25.txt'u 2:1:3  w xe

set title "2014 Week 3 - Top 25"
set out "week3-top25.png"
plot 'plot-2014-week3-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week3-top25.txt'u 2:1:3  w xe

set title "2014 Week 4 - Top 25"
set out "week4-top25.png"
plot 'plot-2014-week4-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week4-top25.txt'u 2:1:3  w xe

set title "2014 Week 5 - Top 25"
set out "week5-top25.png"
plot 'plot-2014-week5-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week5-top25.txt'u 2:1:3  w xe

set title "2014 Week 6 - Top 25"
set out "week6-top25.png"
plot 'plot-2014-week6-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week6-top25.txt'u 2:1:3  w xe

set title "2014 Week 7 - Top 25"
set out "week7-top25.png"
plot 'plot-2014-week7-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week7-top25.txt'u 2:1:3  w xe

set title "2014 Week 8 - Top 25"
set out "week8-top25.png"
plot 'plot-2014-week8-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week8-top25.txt'u 2:1:3  w xe

set title "2014 Week 9 - Top 25"
set out "week9-top25.png"
plot 'plot-2014-week9-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week9-top25.txt'u 2:1:3  w xe

set title "2014 Week 10 - Top 25"
set out "week10-top25.png"
plot 'plot-2014-week10-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week10-top25.txt'u 2:1:3  w xe

set title "2014 Week 11 - Top 25"
set out "week11-top25.png"
plot 'plot-2014-week11-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week11-top25.txt'u 2:1:3  w xe

set title "2014 Week 12 - Top 25"
set out "week12-top25.png"
plot 'plot-2014-week12-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week12-top25.txt'u 2:1:3  w xe

set title "2014 Week 13 - Top 25"
set out "week13-top25.png"
plot 'plot-2014-week13-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week13-top25.txt'u 2:1:3  w xe

set title "2014 Week 14 - Top 25"
set out "week14-top25.png"
plot 'plot-2014-week14-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week14-top25.txt'u 2:1:3  w xe

set title "2014 Week 15 - Top 25"
set out "week15-top25.png"
plot 'plot-2014-week15-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week15-top25.txt'u 2:1:3  w xe

set title "2014 Week 16 - Top 25"
set out "week16.png"
plot 'plot-2014-week16-top25.txt' u ($2+1):1:($4) w labels left, \
	'plot-2014-week16-top25.txt'u 2:1:3  w xe
