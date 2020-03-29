#!/usr/bin/env python3
import numpy as np
import pyswarm as ps
from pyswarm import pso

def banana(x, *args):
    #x1 = x[0]
    #x2 = x[1]
    #print(x[0],x[1])
    #print(x1**4 - 2*x2*x1**2 + x2**2 + x1**2 - 2*x1 + 5)
    #return x1**4 - 2*x2*x1**2 + x2**2 + x1**2 - 2*x1 + 5
    x0 = x[0] * 10000 # [<probpoth_>] 
    x1 = x[1] * 10000 # [<probpotl_>] 
    x2 = x[2] * 10000 # [<probzeros_>] 
    x3 = x[3] * 10000 # [<probr1normh_>] 
    x4 = x[4] * 10000 # [<probr1norml_>]                         
    x5 = x[5] * 10000 # [<probrmaxnormh_>] 
    x6 = x[6] * 10000 # [<probrmaxnorml_>] 
    x7 = x[7] * 10000 # [<probmin_>] 
    x8 = x[8] * 10000 # [<cthpos_>] 
    x9 = x[9] * 10000 # [<cthneg_>]                         
    x10= x[10]* 10000 # [<thpoth_>]
    x11= x[11]* 10000 # [<thpotl_>] 
    x12= x[12]        # [<thzeros_>] 
    x13= x[13]* 10000 # [<thr1h_>] 
    x14= x[14]* 10000 # [<thr1l_>]                         
    x15= x[15]* 10000 # [<thrmaxh_>] 
    x16= x[16]* 10000 # [<thrmaxl_>]
    string = "scripts/PSO_run_get_pitch.sh %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d" %(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16)
    #string = "prova.sh 40000 70000"
    print(string)
    import subprocess as sp
    p = sp.Popen(string, shell = True, stdout=sp.PIPE, universal_newlines=True)
    exitcode = float(p.communicate()[0])/10000
    print(exitcode)
    return 100 - exitcode

#def con(x, *args):
#    x1 = x[0]
#    #x2 = x[1]
#    return [-(x1 + 0.25)**2 + 0.75*x2]

# [<probpoth_>] [<probpotl_>] 
# [<probzeros_>] [<probr1normh_>] 
# [<probr1norml_>] [<probrmaxnormh_>] 
# [<probrmaxnorml_>] [<probmin_>]
    
lb = [60,   0.0,    0.1,   0.97,   0.01,   1.01,   0.1,   50.0,     0.01,   0.01, 29.9, 56.9, 500, 0.80, 0.35, 0.30, 0.10]
ub = [120,  40 ,    0.85,   3.0,   0.65,   3.50,   0.6,   100.0,    0.99,   0.99, 30.1, 57.1, 3000, 0.99, 0.75, 0.50, 0.30]



#a = 0
#b = 0
#args = (a, b)
xopt, fopt = pso(banana, lb, ub, maxiter=30, swarmsize=300)#f_ieqcons=con, maxiter=20, swarmsize = 20)
print(xopt)
print(100 - fopt)

# Optimum should be around x=[0.5, 0.76] with banana(x)=4.5 and con(x)=0
