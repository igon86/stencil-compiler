# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="andrealottarini"
__date__ ="$5-feb-2012 14.40.07$"

class Cache(object):

    def __init__(self,shape):
        self.faults = 0
        self.opid = 0
        self.block = {}
        self.size = 0


    def out(self):
        min = self.opid
        mink = None
        for k, v in self.block.iteritems():
            if v < min:
                min = v
                mink = k
        del self.block[mink]

    def get(self,key):
        try:
            self.block[key]
        except KeyError:
            self.faults +=1

    def put(self,key):
        self.opid +=1
        while self.size >= 10:
            self.out()
        block[key] = self.opid