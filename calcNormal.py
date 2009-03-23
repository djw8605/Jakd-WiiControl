
import sys

x1 = float(sys.argv[1])
y1 = float(sys.argv[2])
z1 = float(sys.argv[3])

x2 = float(sys.argv[4])
y2 = float(sys.argv[5])
z2 = float(sys.argv[6])

x3 = float(sys.argv[7])
y3 = float(sys.argv[8])
z3 = float(sys.argv[9])



normal_x = (y2 - y1)*(z3 - z1) - (z2 - z1)*(y3 - y1)
normal_y = (z2 - z1)*(x3 - x1) - (y2 - y1)*(z3 - z1)
normal_z = (x2 - x1)*(y3 - y1) - (x2 - x1)*(x3 - x1)

print "(%lf, %lf, %lf)" % (normal_x, normal_y, normal_z)
