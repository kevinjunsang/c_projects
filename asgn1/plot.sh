#!/bin/bash

#make clean && make sincos   # Rebuild the sincos executable.
#./sincos > /tmp/sin.dat     # Place the data points into a file.

rm -f /tmp/length.dat
rm -f /tmp/max.dat
rm -f /tmp/his.dat

make clean && make collatz

for n in {1..10000}; do
	./collatz -n $n | wc -l >> /tmp/length.dat
done

for n in {1..10000}; do
	./collatz -n $n | sort -n | tail -n 1 >> /tmp/max.dat
done

head -n 10000 < /tmp/length.dat | sort | uniq -c | less > /tmp/his.dat


# This is the heredoc that is sent to gnuplot.
gnuplot <<END
    set terminal pdf
    set output "length.pdf"
    set title "Collatz Sequence Lengths"
    set xlabel "n"
    set ylabel "length"
    set zeroaxis
    plot "/tmp/length.dat" with dots title ""

    set terminal pdf
    set output "max.pdf"
    set title "Maximum Collatz Sequence Value"
    set xlabel "n"
    set ylabel "value"
    set yrange [0:100000]
    set zeroaxis
    plot "/tmp/max.dat" with dots title ""

    set terminal pdf
    set output "his.pdf"
    set title "Collatz Sequence Length Histogram"
    set xlabel "length"
    set ylabel "frequency"
    set yrange [0:200]
    set xrange [0:225]
    set zeroaxis
    plot "/tmp/his.dat" using 2:1 with impulses title ""
END
