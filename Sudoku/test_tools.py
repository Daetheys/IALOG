from hypothesis import given
from hypothesis.strategies import integers
from logics import encode,decode

@given(integers(min_value=0,max_value=8),integers(min_value=0,max_value=8),integers(min_value=0,max_value=8))
def test_encode_decode(x,y,nb):
    i = encode(x,y,nb)
    print("encoded",i,x,y,nb)
    assert i != 0 #Sinon on aura un pb avec le parsing des dimacs
    assert decode(i) == (x,y,nb)
