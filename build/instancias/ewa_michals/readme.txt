Task file structure

Line
1		N	C
2		x_0		y_0
...
N+1		x_N-1	y_N-1
N+2		s	t	d
...
N+C+1	s	t	d

The first line contains two integers:
N - number of nodes in the considered network
C - number of connections btw nodes for assumed topology

Lines from 2 to N+1 contain x and y coordinates of the nodes - 1 node per line. The range for x any y is equal <0,1>.

Lines from N+2 to N+C+1 contain info about connections in form: 
source	target	distance

Source and target are indexed from 0 to N-1.

