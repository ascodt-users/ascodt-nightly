import subprocess
import sys
proc = subprocess.Popen(['gnuplot','-p'], 
                        shell=True,
                        stdin=subprocess.PIPE,
                        )
proc.stdin.write("set title 'Velocity Profile'\n")
proc.stdin.write("set xlabel 'Y'\n")
proc.stdin.write("set terminal svg\n")
proc.stdin.write('set xrange [0:10]; set yrange [-2:2]\n')
proc.stdin.write("set terminal svg\n")
proc.stdin.write("set output '"+sys.argv[2]+".svg'\n")
proc.stdin.write('set autoscale\n')
gnuplotstr="plot '"+sys.argv[1]+"' using 1 with lines ti  'Iteration 1'"
index = [3,5,7,9,11,19,35]
for i in index:
	gnuplotstr=gnuplotstr+",'"+sys.argv[1]+"' using "+str(i)+" with lines ti 'Iteration "+str(i)+"'"
print(gnuplotstr)
proc.stdin.write(gnuplotstr)
proc.stdin.write('\nquit\n') 
