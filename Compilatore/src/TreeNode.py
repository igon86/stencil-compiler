# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="andrealottarini"
__date__ ="$6-feb-2012 17.28.20$"

class Node(object):

    # using [] as default argument can be not a good idea
    def __init__(self,level = -1,source = None,offsets = []):
        #print "addNODE"
        self.level = level
        self.childs = []
        self.start = self.end = -1
        self.offsets = []
        # this should not happen unless for testing purposes
        if source is not None:
            self.start = self.end = source.coordinates[level]

            if self.level == len(source) - 1:
                self.offsets = offsets
            else:
                self.offsets = []

    def addChild(self,source,offsets):
        # print "sono al livello", self.level, len(source)
        if self.level < len(source) - 1:
            index = source.coordinates[self.level+1]
            child = self.getChild(index)
            if child is None:
                child = Node(self.level+1,source,offsets)
                self.childs.append(child)
            child.addChild(source,offsets)
            

    def getChild(self,index):
        """ check if a child of self contains the index "index"

            self    -- node having a list of childs which may contain
                        the index
            index   -- coordinate which has to be found

            output  -- the child of self containing index, None if such
                        child does not exist
        """
        for child in self.childs:
            if index >= child.start and index <= child.end:
                return child
        return None



    def __eq__(self,other):
        print "confronto " +str(self)+str(other)
        o = self.offsets == other.offsets
        c = self.childs == other.childs
        print o,c
        if o and c:
            return True
        else:
            return False

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        out = ""
        for i in range(self.level+1):
            out += "\t"
        #ma perche cazzo non funziona!!
        return "\n"+out +"nodo di livello " +str(self.level) +" inizio: " +str(self.start) +" fine: " +str(self.end) +" offset "+str(self.offsets)+" figli"+ str(self.childs)

if __name__ == "__main__":
    print "Hello World"
