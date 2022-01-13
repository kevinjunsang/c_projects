#!/bin/bash


rm -f /tmp/length.dat                                                          #removes /tmp/length.dat
rm -f /tmp/max.dat                                                             #removes /tmp/max.dat
rm -f /tmp/his.dat                                                             #removes /tmp/his.dat

make clean && make collatz                                                     #cleans program of files and makes collatz via MAKEFILE

#for loop to make a list of collatz sequence lengths
for n in {1..10000}; do                                                        #for loop from 1 to 10000
	./collatz -n $n | wc -l >> /tmp/length.dat                             #finds length of collatz sequence given length and appends to /tmp/length.dat
done                                                                           #end of loop

#for loop to make a list of collatz sequence maximum values
for n in {1..10000}; do                                                        #another for loop from 1 to 10000
	./collatz -n $n | sort -n | tail -n 1 >> /tmp/max.dat                  #finds max value of collatz sequence given length and appends to /tmp/max.dat
done                                                                           #end of loop

#adding list of lengths and frequency
head -n 10000 < /tmp/length.dat | sort | uniq -c | less > /tmp/his.dat         #uses sort, uniq, pipes, and head to put list of lengths and frequency into /tmp/his.dat


# This is the heredoc that is sent to gnuplot.
gnuplot <<END
#gnuplot for collatz lengths is pretty simple
    set terminal pdf
    set output "length.pdf"
    set title "Collatz Sequence Lengths"
    set xlabel "n"
    set ylabel "length"
    set zeroaxis
    plot "/tmp/length.dat" with dots title ""

#gnuplot for max values, set yrange
    set terminal pdf
    set output "max.pdf"
    set title "Maximum Collatz Sequence Value"
    set xlabel "n"
    set ylabel "value"
    set yrange [0:100000]
    set zeroaxis
    plot "/tmp/max.dat" with dots title ""

#gnuplot for histogram, set xrange and yrange, flip x and y values when graphing
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
