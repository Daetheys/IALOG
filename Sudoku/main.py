from parser import parse
from sudoku import Sudoku

FILE = "puzzles.sdk"

txt = open(FILE)

LI_SUDOKU = parse(txt)

for i in range(1):
    sudoku1 = Sudoku(LI_SUDOKU[i])
    sudoku1.solve_cdcl()
