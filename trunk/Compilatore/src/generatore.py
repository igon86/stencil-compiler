# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__="andrealottarini"
__date__ ="$15-feb-2012 11.22.26$"

def returnSecId(section):
    out = ""
    for i in section.tag:
        out +=str(i)
    return out

class Generatore(object):

    def __init__(self,section):
        self.section = section

    def generaCodice(self,file):
        albero = self.section.root

        with open(file,'w') as f:
            self.generaNodo(albero,f)


    def generaNodo(self,node,f):
        if node is not None:
            tab=""
            if node.start is not -1:
                
                for i in range(node.level):
                    tab +="\t"
                # il +1 e per MATLAB
                f.write(tab+"for i"+str(node.level)+" = "+str(node.start+1)+" : " +str(node.end+1)+"\n")

                # qui il pezzo mui brutto
                if len(node.offsets) > 0:
                    #_1 e per avere output separato da input
                    f.write(tab+"\ts"+returnSecId(self.section)+"_1(")
                    #se ho degli offset allora sono al nodo foglia ecco perche c'e il +1
                    for j in range(node.level+1):
                        f.write("i"+str(j)+",")
                    f.seek(f.tell()-1)
                    f.write(")")
                    f.write(" = funzione( " )
                    for offset in node.offsets:
                        if offset.isOuter is True:
                            f.write("o")
                        else:
                            f.write("s")
                        f.write(returnSecId(offset.father))
                        f.write(offset.getStr())
                        f.write(",")
                    f.seek(f.tell()-1)
                    f.write(");\n")

            for c in node.childs:
                self.generaNodo(c, f)
            if node.start is not -1:
                f.write(tab+"end\n")



if __name__ == "__main__":
    print "Hello World"
