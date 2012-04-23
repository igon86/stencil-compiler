# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="andrealottarini"
__date__ ="$14-feb-2012 16.26.40$"

def kernel(t0,x):
    print t0,x

def walk(t0,t1,x0,dx0,x1,dx1):
    dt = t1-t0

    if dt ==1:
        for x in range(x0,x1):
            kernel(t0,x)
    else:

        if 2*(x1-x0) + (dx1 -dx0)*dt >= 4*dt:
            #SPACE CUT
            xm = (2*(x1+x0) + (2+dx1+dx0)*dt)/4
            walk(t0,t1,x0,dx0,xm,-1)
            walk(t0,t1,xm,-1,x1,dx1)
        else:
            s = dt/2
            walk(t0,t0+s,x0,dx0,x1,dx1)
            walk(t0+s, t1 , x0+dx0*s, dx0, x1 +dx1*s, dx1)



if __name__ == "__main__":
    walk(0,4,1,0,100,0)
