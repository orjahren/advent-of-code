grid = []
with open("input.txt", "r") as f:
    for line in f.readlines():
        line = line.strip()
        grid.append([])
        for char in line:
            grid[-1].append(int(char))

def is_low_point(pos: tuple) -> bool:
    val = grid[pos[0]][pos[1]]
    x, y = pos
    for a, b in [(-1, 0), (0, -1), (1, 0), (0, 1)]:
        try:
            vos = grid[x + a][y + b]
            if val >= vos:
                return False
        except Exception:
            pass
    return True
        
res = 0
for i in range(len(grid)):
    for j in range(len(grid[i])):
        if is_low_point((i, j)):
            res += 1 + grid[i][j]

print("res:", res)