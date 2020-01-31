from logics import *
from tools import *

from hypothesis import given
from hypothesis.strategies import integers, lists

@given(integers(),integers(),integers())
def test_var(x,y,nb):
    v = Var(x,y,nb)
    assert v.get_pos() == (x,y,nb)
    assert v.get_name() == str(1+x + y*9 + nb*81)

@given(integers(),integers(),integers(),integers())
def test_literal(x,y,nb,b):
    if b > 0:
        b = 1
    else:
        b = -1
    v = Var(x,y,nb)
    l = Literal(v,b)
    if b == 1:
        assert l.get_name() == v.get_name()
    else:
        assert l.get_name() == "-"+v.get_name()

def test_exactly_one1():
    l = exactly_one([0],[0],[0,1,2],True)
    assert len(l) == 4
