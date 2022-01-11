#!/bin/bash

#make clean && make sincos   # Rebuild the sincos executable.
#./sincos > /tmp/sin.dat     # Place the data points into a file.

rm -f /tmp/length.dat

for n in {1..10}; do
	echo -n $n >> /tmp/length.dat
	./collatz -n $n | wc -l >> /tmp/length.dat
done

# This is the heredoc that is sent to gnuplot.
gnuplot <<END
    set terminal pdf
    set output "length.pdf"
    set title "Sequence lengths"
    set xlabel "x"
    set ylabel "y"
    set zeroaxis
    plot "/tmp/length.dat" with points title ""
END
