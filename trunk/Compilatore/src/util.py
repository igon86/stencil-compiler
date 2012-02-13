# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="andrealottarini"
__date__ ="$5-feb-2012 14.43.04$"

def absolute(data):
    a = list()
    for index,item in enumerate(data):
        a.append(abs(item))
    return a

#removes one level of nesting as concat in haskell
def concatenate(x,y):
    out = []
    for i in x:
        print i
        out.append(i)

    for j in y:
        print j
        out.append(j)

    return out

#removes all levels of nesting in a list
def splat(x):
    #if x is a list of lists
    if hasattr(x,'__iter__') and x[0] is not None and hasattr(x[0],'__iter__'):
        y = reduce(concatenate,x)
        return splat(y)
    else:
        return x

def addList(a,b):
    out = []
    for i in range(len(a)):
        out.append(a[i]+b[i])
    return out

def collapseTree(a,b):
    #print "invocata la collapse\nA:",a ,"\nB",b
    if len(b.childs) > 0 :
        #print "invoco la collapse su b"
        b.childs = reduce(collapseTree,b.childs)
    if hasattr(a,'__iter__'):
        #print "a e una lista"
        lastElement = a[len(a)-1]
        if lastElement == b:
            lastElement.end = b.end
            #print "spiaccico b sull'ultimo di a"
            return a
        else:
            #print "appendo b ad a"
            a.append(b)
            #print a
            return a
    else:
        #print "a non e una lista"
        if len(a.childs) > 0:
            #print "invoco la collapse su a"
            a.childs = reduce(collapseTree,a.childs)
        if a == b:
            #print "unisco i due nodi"
            a.end = b.end
            return [a]
        else:
            #print "concateno i due nodi"
            return [a,b]




if __name__ == "__main__":
    print "Hello World"
