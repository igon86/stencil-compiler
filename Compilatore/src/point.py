
__author__="andrealottarini"
__date__ ="$5-feb-2012 14.38.56$"

import copy

class Point(object):

    # Inizializzatore della classe
    def __init__(self, a):
        self.coordinates = a

    def __eq__(self,other):
        if other is None: return False
        if self.coordinates == other.coordinates:
            return True
        else:
            return False

    #toString
    def __str__(self):
        return " " +str(self.coordinates)

    def __repr__(self):
        return self.__str__()

    def __len__(self):
        return len(self.coordinates)

    def __getitem__(self,index):
        return self.coordinates[index]

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
        """ Method which return the maximum absolute value among the ones stored in coordinates
            Used to compute the order of shape

            self    -- a Point

            output  -- maximum absolute value of coordinates

        """
        absMax = 0
        for item in self.coordinates:
            if abs(item) > absMax:
                absMax = abs(item)
        return absMax


class Offset(Point):

    def __init__(self, coord,father,isOuter):
        Point.__init__(self,coord)
        self.father = father
        self.isOuter = isOuter

        coolness = 0
        for i in self.father.tag:
            if i == 1: coolness += 1

    def coolness(self):
        return self.coolness

    def __eq__(self,other):
        if Point.__eq__(self,other):
            if self.isOuter == other.isOuter and self.father.tag == other.father.tag:
                return True
            else:
                return False
        else:
            return False

    def getStr(self):
        out = "("
        for index,item in enumerate(self.coordinates):
            if item < 0:
                out += "i" +str(index)+str(item)+","
            else:
                out += "i" +str(index)+"+"+str(item)+","
        out = out[0:len(out)-1] +")"
        return out

    #da estendere ragionevolmente
    def __str__(self):
        return Point.__str__(self) + str(self.isOuter)[0] + " f" + str(self.father.tag)


#mooolto divertente come mi sono reimplementato la getitem e basta
class SectionPoint(Point):
    
    def __init__(self,coord,gcoord,father,isOuter):
        Point.__init__(self,coord)
        self.gcoordinates = gcoord
        self.father = father
        self.isOuter = isOuter

        coolness = 0
        for i in self.father.tag:
            if i == 1: coolness += 1

    def coolness(self):
        return self.coolness

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
        return str(self.isOuter)[0]+"(" +str(self.coordinates) + " " +str(self.gcoordinates) +" f: "+str(self.father.tag)+")"

    def __getitem__(self,index):
        return self.gcoordinates[index]

    def __setitem__(self,index,value):
        self.gcoordinates[index] = value

    def __deepcopy__(self,memo):
        coord = copy.deepcopy(self.coordinates)
        gcoord = copy.deepcopy(self.gcoordinates)
        return SectionPoint(coord,gcoord,self.father,self.isOuter)

    #override dell'addizione
    def __add__(self,p):
        #print "sto facendo l'addizione",self, p
        out = copy.deepcopy(self)
        for index in range(len(out)):
            out[index] = out[index] + p[index]
        #print out
        for index in range(len(out)):
            out.coordinates[index] = out.coordinates[index] + p.coordinates[index]
        # print "sputo ", out
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

    def getOffset(self,other):
        coord = []
        for i in range(len(self)):
            coord.append(other.coordinates[i] - self.coordinates[i])
        return Offset(coord,other.father,other.isOuter)



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
