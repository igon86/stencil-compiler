
__author__="andrealottarini"
__date__ ="$5-feb-2012 14.38.56$"

import copy

class Point(object):

    # Inizializzatore della classe
    def __init__(self, a):
        self.coordinates = a

    def __eq__(self,other):
        if other is None: return False
        if self.gcoordinates == other.gcoordinates:
            return True
        else:
            return False

    #toString
    def __str__(self):
        return " " +str(self.coordinates)

    def __len__(self):
        return len(self.coordinates)

    def __getitem__(self,index):
        return self.coordinates[index]

    def __repr__(self):
        return self.__str__()

    def __setitem__(self,index,value):
        self.coordinates[index] = value

    #override dell'addizione
    def __add__(self,p):        
        if type(p).__name__=='int':
            out = copy.deepcopy(self)
            for index in range(0,len(out)):
                out[index] = out[index] + p
            return out

        elif type(p).__name__=='Point' and len(p) == len(self):
            out = copy.deepcopy(self)
            for index in range(0, len(out)):
                out[index] = out[index] + p[index]
            return out

    def getAbsMax(self):
        absMax = 0
        for item in self.coordinates:
            if abs(item) > absMax:
                absMax = abs(item)
        return absMax

#mooolto divertente come mi sono reimplementato la getitem e basta
class SectionPoint(Point):
    def __init__(self,coord,gcoord,father,isOuter):
        Point.__init__(self,coord)
        self.gcoordinates = gcoord
        self.father = father
        self.isOuter = isOuter

    def isSimilar(self,other):
        """ Method which check if self has the same global coordinates of other

            self    -- a SectionPoint
            other   -- another SectionPoint

            output  -- true if self has the same global coordinates of other, false otherwise

        """

        # serve nella getCandidates che si confrontino le coordinate
        # globali e basta
        if other is None: return False
        #print type(other).__name__
        #print other
        if self.gcoordinates == other.gcoordinates:
            return True
        else:
            return False

    def __eq__(self,other):
        #questo va finito e testato
        super(SectionPoint, self).__eq__(other)

    def __str__(self):
        return "(" +str(self.coordinates) + " " +str(self.gcoordinates) +")"

    def __getitem__(self,index):
        return self.gcoordinates[index]

    def __setitem__(self,index,value):
        self.gcoordinates[index] = value

    #override dell'addizione
    def __add__(self,p):
        print "sto facendo l'addizione",self, p
        out = copy.deepcopy(self)
        for index in range(len(out)):
            out[index] = out[index] + p[index]
        print out
        for index in range(len(out)):
            out.coordinates[index] = out.coordinates[index] + p.coordinates[index]
        print "sputo ", out
        return out

    def __neg__(self):
        out = copy.deepcopy(self)
        for index in range(len(out)):
            out[index] = - out[index]
        #ma questa nn la posso chiamare come super?
        for index in range(len(out)):
            out.coordinates[index] = - out.coordinates[index]
        return out

    def __sub__(self,p):
        return self.__add__(-p)
        return out

    def coolness(self):
        coolness = 0
        for i in self.father.tag:
            if i == 1: coolness = coolness + 1
        return coolness

if __name__ == "__main__":
    import sys
    a = Point([1,2])
    b = Point([2,3])
    print "a", a
    print "b", b
    c = a + b
    print "a", a
    print "b", b
    print "c", c
    d = a + 1
    print "a", a
    print "d", d
    e = [a,b]
    print e
    f = Point([1,2])
    if a == f:
        print "compare implicito"
