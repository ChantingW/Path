unset key

set xlabel "latitude"
set ylabel "longitude"
plot [-1.565:-1.540][53.801:53.812] 'nodes.out' with points pointsize 1,\
 'links.out' with lines lc rgb 'blue',\
 'route.out' with linespoints lc rgb 'red' pointtype 9 linewidth 2 pointsize 1
