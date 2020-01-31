def encode(x,y,nb):
    """ Encodes (x,y,nb) in a unique int """
    return 1 + x + y*9 + nb*81

def decode(i):
    """ Decode i in (x,y,nb) """
    i -= 1
    x = i%9
    y = (i%81 - x)//9
    nb = i // 81
    assert 1<=x+1<=9
    assert 1<=y+1<=9
    assert 1<=nb+1<=9
    return (x,y,nb)

class Var:
    def __init__(self,x,y,nb):
        self.x = x
        self.y = y
        self.nb = nb

    def get_pos(self):
        return (self.x,self.y,self.nb)

    def get_name(self):
        return str(encode(self.x,self.y,self.nb))

class Literal:
    def __init__(self,var,b):
        self.var = var
        self.b = b

    def get_name(self):
        if self.b == -1:
            s = "-"
        else:
            s = ""
        return s+self.var.get_name()
        
class Clause:
    def __init__(self,l):
        self.l = l

    def __add__(self,l):
        if isinstance(l,Literal):
            self.add(l)
        if isinstance(l,Var): #Sucre syntaxique
            self.add(Literal(l,1))
        return self

    def __len__(self):
        return self.length()

    def add(self,var):
        self.l.append(var)

    def write(self):
        s = ""
        for v in self.l:
            s += v.get_name()+" "
        return s

    def length(self):
        return len(self.l)


class Logics:
    def __init__(self):
        self.clauses = []

    def __add__(self,c):
        if isinstance(c,Clause):
            self.add(c)
        if isinstance(c,Logics):
            self.fusion(c)
        return self

    def __repr__(self):
        return self.get_dimacs()

    def __len__(self):
        return self.nb_clauses()

    def add(self,c):
        self.clauses.append(c)
        
    def nb_clauses(self):
        return len(self.clauses)

    def type_clauses(self):
        d = {}
        for c in self.clauses:
            try:
                d[c.length()] += 1
            except:
                d[c.length()] = 1
        return d

    def get_dimacs(self):
        s = "c dimacs got from logics.Logics\n"
        s += "p cnf "+str(9*9*9)+" "+str(len(self))+"\n"
        for c in self.clauses:
            s += c.write()+" 0\n"
        return s

    def fusion(self,l2):
        self.clauses += l2.clauses
