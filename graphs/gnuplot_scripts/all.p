# Gnuplot script file for ploting matrix multiplication duration in comparison to its size
# The results are from the all the solutions (solve_neopt.c, solve_opt.c, solve_blas.c)
# File name is all.p
set title "Matrix multiplication - all solutions"
set xlabel "Size (elements of type double)"
set ylabel "Time (seconds)"
set xrange[0:1600]
set yrange[0:50]
plot for [file in "../samples/neopt.txt ../samples/opt.txt ../samples/blas.txt"] file \
        using 1:2:(sprintf("(%s, %s)", stringcolumn(1), stringcolumn(2))) with labels offset -5.0, 2.0 notitle, \
        "../samples/neopt.txt" using 1:2 with lines lc rgb 'blue' title 'Average neoptimized', \
        "../samples/opt.txt" using 1:2 with lines lc rgb 'red' title 'Average optimized', \
        "../samples/blas.txt" using 1:2 with lines lc rgb 'green' title 'Average blas'
