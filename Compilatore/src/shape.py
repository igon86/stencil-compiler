

__author__="andrealottarini"
__date__ ="$5-feb-2012 14.42.01$"

import copy

from point import *

class Shape(object):

    def iaddOffset(self,offset):
        for index,item in enumerate(self.points):
            for index_1,item_1 in enumerate(self.points[index]):
                self.points[index] = self.points[index] + self.ordine

    def addOffset(self,offset):
        out = copy.deepcopy(self)
        out.iaddOffset(offset)

    def getNegativeShape(self):
        return self.addOffset(-self.ordine)

    def getPositiveShape(self):
        return self.addOffset(self.ordine)

    # Inizializzatore della classe
    def __init__(self, data):
        if type(data).__name__=='list':
            self.points = data
        elif type(data).__name__=='str':
            shape_coordinates = data.split('\t')

            #split different points
            for index,item in enumerate(shape_coordinates):
                shape_coordinates[index] = item.split(',')

            #print shape_coordinates

            #split and converts coordinates of every point
            for index,item in enumerate(shape_coordinates):
                for index_1,item_1 in enumerate(shape_coordinates[index]):
                    item_1 = int(item_1)
                    shape_coordinates[index][index_1] = item_1

            #print shape_coordinates

            # creates points
            for index,item in enumerate(shape_coordinates):
                shape_coordinates[index] = Point(item)

            #print shape_coordinates

            self.points = shape_coordinates

        # initialize dim attribute which corresponds to the number of coordinates in a point
        self.dim = len(self[0])

        #shape order is computed from shape points
        self.ordine = 0
        for p in self.points:
            if p.getAbsMax > self.ordine:
                self.ordine = p.getAbsMax()

        print "ordine is" ,self.ordine

    #toString
    def __str__(self):
        return " " +str(self.points)

    def __len__(self):
        return len(self.points)

    def __getitem__(self,index):
        return self.points[index]

    def __setitem__(self,index,value):
        self.points[index] = value


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
