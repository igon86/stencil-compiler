# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="andrealottarini"
__date__ ="$6-feb-2012 17.28.20$"

import util

class Node(object):

    # using [] as default argument is funny
    def __init__(self,level = -1,source = None,offsets = []):
        #print "addNODE"
        self.level = level
        self.childs = []
        self.start = self.end = -1
        self.offsets = []
        # source is None only for the root node of the tree
        if source is not None:
            self.start = self.end = source.coordinates[level]

            if self.level == len(source) - 1:
                self.offsets = offsets
            else:
                self.offsets = []

    def addChild(self,source,offsets):
        """ add a child to the tree (self)

            self     -- root node, new nodeis added to self.childs
            source   -- Point
            offsets  -- list of offsets

        """
        if self.level < len(source) - 1:
            index = source.coordinates[self.level+1]
            # check if a child with the same coordinates of source exists
            child = self.getChild(index)
            if child is None:
                child = Node(self.level+1,source,offsets)
                self.childs.append(child)
            # method is invoked recursively on the child
            # one lower level of coordinates
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

    def getInterval(self):
        """ return the interval of coordinates relative to self

            self    -- a treenode

            output  -- interval of self
        """
        return self.end - self.start

    def reduceTree(self):
        """ this method reduce the tree by collapsing similar nodes
        
            self    -- root of the tree to be reduced


        """
        if len(self.childs) > 0:
            for item in self.childs:
                item.reduceTree()

            ridotto = reduce(util.collapseTree2,self.childs)
            if hasattr(ridotto,'__iter__'):
                self.childs = ridotto
            else:
                self.childs = [ridotto]            
            

    def expandTree(self,ordine,extension):
        #print "estendo ", self
        #firstly I fix the interval

        for item in self.offsets:
            item.expand(extension,ordine)

        extended = False
        #print self.childs
        for item in self.childs:

            if extended:
                item.start += extension
                item.end += extension
            else:
                if item.getInterval() > ordine - 1 :
                    extended = True
                    item.end += extension
        #print "Ho ottenuto ", self
        for item in self.childs:
            item.expandTree(ordine,extension)


    def generaTab(self):
        tab = ""
        for i in range(self.level):
            tab +="\t"
        return tab

    def generaNode(self,secId):
        out = ""
        tab = self.generaTab()
        node = self

        # the for loop associated to this level is generated
        out += (tab+"for i"+str(node.level)+" = "+str(node.start+1)+" : " +str(node.end+1)+"\n")
        
        if len(node.offsets) > 0:
            #se ho degli offset allora sono al nodo foglia
            #_1 e per avere output separato da input
            out += (tab+"\ts"+secId+"_1(")

            for j in range(node.level):
                out+=("i"+str(j)+",")
            out+=("i"+str(j+1)+")")
            out += (" = funzione( " )
            count = 0
            for offset in node.offsets:
                if offset.isOuter is True:
                    out +=("o")
                else:
                    out +=("s")
                out += (offset.father.generaId())
                out += (offset.getStr())
                count +=1
                if count < len(node.offsets):
                    out +=(",")
            out +=(");\n")


        for c in self.childs:
            out += c.generaNode(secId)
        out +=(tab+"end\n")
        return out

    def generaNodeC(self,secId,sourceId,targetId):
        ''' Generate the code associated with the node self, a for loop is generated
            if the node contains a list of offsets: the function (kernel) invocation is generated
            otherwise generaNodeC is invoked recursively on the children of the node

            secId       -- Is the string id of the the section which owns the node self
            sourceId    -- Is the string postfix associated with the source point
            targetId    -- Is the string postfix to be used

            example of generated code:    s$(secId)_$(targetId)[][] = funzione( so2_$(sourceId) , ...  )

        '''
        out = ""
        tab = self.generaTab()
        node = self

        # the for loop associated to this level is generated
        out += (tab+"for (i"+str(node.level)+" = "+str(node.start)+" ; i"+str(node.level)+" <=" +str(node.end)+";i"+str(node.level)+"++){\n")

        #dovrei fare la generaOffset
        if len(node.offsets) > 0:
            #se ho degli offset allora sono al nodo foglia
            #_1 e per avere output separato da input
            out += (tab+"\ts"+secId+"_"+targetId)

            for j in range(node.level+1):
                out+=("[i"+str(j)+"]")
            
            
            out += (" = MACRO( " )
            count = 0
            for offset in node.offsets:
                if offset.isOuter is True:
                    out +=("o")
                else:
                    out +=("s")
                out += (offset.father.generaId())
                if offset.isOuter is not True:
                    out += ("_"+sourceId)
                out += (offset.getStrC())
                count +=1
                if count < len(node.offsets):
                    out +=(",")
            out +=(");\n")

        for c in self.childs:
            out += c.generaNodeC(secId,sourceId,targetId)
        out +=(tab+"}\n")
        return out

    def __eq__(self,other):
        #print "confronto " +str(self)+str(other)
        o = (self.offsets == other.offsets)
        c = (self.childs == other.childs)
        #print o,c
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
