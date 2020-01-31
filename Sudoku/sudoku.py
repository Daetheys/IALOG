from logics import Logics,Clause,Literal,Var,decode
from tools import exactly_one
import os

class Sudoku:
    def __init__(self,grid=None):
        self.grid = None
        self.solved_grid = None
        if grid is not None:
            self.load_grid(grid)
        

    def __repr__(self):
        if self.grid is None:
            return "EMPTY SUDOKU"
        else:
            s = ""
            line_separation = "-"*(5+4+4)+"\n"
            column_separation = "|"
            for i,line in enumerate(self.grid):
                if i%3 == 0:
                    s += line_separation
                for j,x in enumerate(line):
                    if j%3 == 0:
                        s += column_separation
                    s += str(x)
                s += column_separation
                s += "\n"
            s += line_separation
            return s

    def load_grid(self,grid):
        self.grid = grid

    def solve_minisat(self):
        request_file = "__tmp_request__.dimacs"
        solution_file = "__tmp_solution__.txt"
        f_request = open(request_file,"w+")
        f_request.write(str(self.get_logics()))
        f_request.close()
        os.system("minisat -verb=0 "+request_file+" "+solution_file)
        f_solution = open(solution_file,"r+")
        sat, solution,_ = f_solution.read().split("\n") #To remove SAT or unsat
        f_solution.close()
        if sat:
            self.parse_solution(solution)
            return str(self)
        else:
            return "NO SOLUTION"

    def solve_cdcl(self):
        request_file = "__tmp_request__.dimacs"
        solution_file = "__tmp_solution__.txt"
        f_request = open(request_file,"w+")
        f_request.write(str(self.get_logics()))
        f_request.close()
        directory1 = "../CDCL\ solver/"
        directory2 = "../Sudoku/"
        os.system("./"+directory1+"sat_solver "+directory2+request_file+" "+directory2+solution_file)
        f_solution = open(solution_file,"r+")
        sat, solution,_ = f_solution.read().split("\n") #To remove SAT or unsat
        f_solution.close()
        if sat:
            self.parse_solution(solution)
            return str(self)
        else:
            return "NO SOLUTION"

    def parse_solution(self,s):
        l_true = s.split(" ")[:-1] #On enleve le dernier car c'est le 0 du format
        for l in l_true:
            if l[0] != "-":
                i = int(l)
                (x,y,nb) = decode(i)
                self.solved_grid = self.grid[:]
                self.solved_grid[y][x] = nb+1
        

    def get_logics(self):
        logics = Logics()
        #Cases
        for i in range(9):
            for j in range(9):
                logics += exactly_one([i],[j],range(0,9),True)
        #Lines
        for j in range(9):
            for nb in range(0,9):
                logics += exactly_one(range(9),[j],[nb],False)

        #Column
        for i in range(9):
            for nb in range(0,9):
                logics += exactly_one([i],range(9),[nb],False)

        #Square
        for s in range(3):
            for s2 in range(3):
                for nb in range(0,9):
                    logics += exactly_one(range(3*s,3*(s+1)),range(3*s2,3*(s2+1)),[nb],False)
        return logics + self.get_grid_logics_data()
    
    def get_grid_logics_data(self):
        logics = Logics()
        #Use grid data
        for y,line in enumerate(self.grid):
            for x,nb in enumerate(line):
                if nb != 0:
                    logics += Clause([Literal(Var(x,y,nb-1),1)])
        return logics
