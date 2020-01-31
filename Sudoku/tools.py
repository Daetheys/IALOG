from logics import Logics,Clause,Literal,Var

def exactly_one(lx,ly,lnb,whole):
    """ Returns a Logics object that represents a set of logics formulas which only allows one of all cases (x,y,nb) ,x in lx, y in ly and nb in lnb to be right. If whole is False, it will only return 2 clauses for incompatibilities """
    logics = Logics()
    #Global clause (at least 1)
    if whole:
        c = Clause([])
        for x in lx:
            for y in ly:
                for nb in lnb:
                    v = Var(x,y,nb)
                    c.add(Literal(v,1))
        logics += c
    #Specific clauses (minus than 1)
    for x in lx:
        for x2 in lx:
                for y in ly:
                    for y2 in ly:
                            for nb in lnb:
                                for nb2 in lnb:
                                    if (x,y,nb) > (x2,y2,nb2):
                                        v1 = Var(x,y,nb)
                                        v2 = Var(x2,y2,nb2)
                                        l1 = Literal(v1,-1)
                                        l2 = Literal(v2,-1)
                                        c = Clause([l1,l2])
                                        logics += c
    return logics

def encode(x,y,nb):
    """ Encodes (x,y,nb) in a unique int """
    return 1 + self.x + self.y*9 + self.nb*81

def decode(i):
    """ Decode i in (x,y,nb) """
    i -= 1
    x = i%9
    y = (i%81 - x)//9
    z = i // 81
    assert 1<=x<=9
    assert 1<=y<=9
    assert 1<=z<=9
    return (x,y,z)
    
