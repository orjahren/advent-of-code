grid = []
with open("input.txt", "r") as f:
    for line in f.readlines():
        line = line.strip()
        grid.append([])
        for char in line:
            grid[-1].append(int(char))

print(grid)
print(len(grid))

def get_voisins(x: int, y:int) -> list:
    l = []
    for a, b in [(-1, 0), (0, -1), (1, 0), (0, 1)]:
        try:
            vos = grid[x + a][y + b]
            l.append(vos)
        except Exception:
            pass
    return l
            

def is_low_point(pos: tuple, voisins: list) -> bool:
    val = grid[pos[0]][pos[1]]
    for char in voisins:
        if val >= char:
            return False
    return True
        
low_points = []
for i, line in enumerate(grid):
    for j, char in enumerate(line):
        print(i, j)
        voisins = get_voisins(i, j)
        if is_low_point((i, j), voisins):
            #low_points.append((i, j))
            low_points.append(grid[i][j])
        print(voisins)

print("antall low_points:", len(low_points))
print("res:", sum([x + 1 for x in low_points]))