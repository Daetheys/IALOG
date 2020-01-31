from parser import parse
from sudoku import Sudoku

FILE = "puzzles.sdk"

txt = open(FILE)

LI_SUDOKU = parse(txt)

for i in range(100):
    sudoku1 = Sudoku(LI_SUDOKU[i])
    assert sudoku1.solve_cdcl() == sudoku1.solve_minisat()
