
__author__="andrealottarini"
__date__ ="$7-mar-2012 12.17.29$"

class CommList(object):

    def __init__(self):
        self.commList = []
        self.size = 0

    def __len__(self):
        return self.size

    def __str__(self):
        out = ""
        for index,cell in enumerate(self.commList):
            out += "CELL "+str(index)+"\n"
            for item in cell:
                out += str(item.tag)+"\t"
            out+="\n"
        return out

    def __repr__(self):
        return self.__str__()
    
    def addSection(self,s):
        print "\nRICHIESTO l'add della sezione" + str(s.tag)

        # a section could be naive, this is the base case
        if len(s.shiftPoints) == 0:
            if len(self.commList) == 0:
                self.commList.append([])
            if s not in self.commList[0]:
                print "APPESO in posizione 0"
                self.commList[0].append(s)
                self.size =self.size + 1
            else:
                print str(s.tag)+"E gia presente"
        else:
            if s not in self:
                print s.tag,"Depends on others sooo I'm going to figure out if I can add it"
                #now I have to find on which sections s depends
                myIndex = 1
                for p in s.shiftPoints:
                    #i filter myself out from the list of POINTS
                    externalPoint = filter(lambda x:x != p ,s.father.getCandidates(p))

                    #outside(receive) sections are disjoind SO only one SHOULD be returned                    
                    assert len(externalPoint) == 1 , "Multiple sections for a shift point: "+str(externalPoint)
                    #lo "delifto"
                    externalPoint = externalPoint[0]
                    #then I have to find at which STEP otherSection is present
                    #print "I will search for "+str(externalPoint.father.tag)+"in " +str(self)
                    index = self.getIndex(externalPoint.father)
                    if index is not None:
                        index = index + 1
                        if index > myIndex:
                            myIndex = index
                    else:
                        #print "il punto" + str(p)+"necessario a "+str(s.tag)+"non e ancora presente in lista"
                        # I will not insert this section at THIS TIME
                        return

                # at this point I have considered every shift point and I know at which level the section must be inserted
                #print "aggiungo "+str(s.tag) +"al livello"+str(myIndex)
                #print len(self.commList)
                if len(self.commList) <= myIndex:
                    #print "aggiungo un livello a commList"
                    self.commList.append([])
                self.commList[myIndex].append(s)
                self.size = self.size + 1
            else:
                print str(s.tag)+"is already present"
                
    def __contains__(self,item):
        for cell in self.commList:
            for section in cell:
                if section == item:
                    return True
        return False

    def __getitem__(self,index):
        return self.commList[index]


    def stepsGenerator(self):
        for cell in self.commList:
            yield cell


    def getIndex(self,s):
        for index,cell in enumerate(self.commList):
            #print "cerco" +str(s.tag)+"al livello "+str(index)
            for section in cell:
                #print "confronto "+str(s.tag)+" con "+str(section.tag)
                if s == section:
                    print "sono uguali e ritorno"
                    return index
                else:
                    print "sono diversi"
        return None
    

