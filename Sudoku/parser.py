def parse(txt):
    li_grid = []
    grid = [[0 for i in range(9)] for j in range(9)]
    for sudo in txt:
        sudo = str(sudo)
        count = 0
        for c in sudo:
            if c in ['0','1','2','3','4','5','6','7','8','9']:
                grid[count//9][count%9] = int(c)
            count += 1
        li_grid.append(grid)
        grid = [[0 for i in range(9)] for j in range(9)]
    return li_grid
