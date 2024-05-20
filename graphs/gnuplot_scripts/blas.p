# Gnuplot script file for ploting matrix multiplication duration in comparison to its size
# The results are from the blas solution (solve_blas.c)
# File name is blas.p
set title "Matrix multiplication - blas"
set xlabel "Size (elements of type double)"
set ylabel "Time (seconds)"
set xrange[0:1600]
set yrange[0:50]
plot "../samples/blas.txt" using 1:2 title "Average time" with linespoints,\
    "" using 1:2:(sprintf("(%s, %s)", stringcolumn(1), stringcolumn(2))) with labels offset -5.0, 2.0 notitle
