class Node:
    cnt = 0
    def __init__(self, val) -> None:
        self.val = val
        self.id = Node.cnt
        Node.cnt += 1
        self.ned, self.hoyre = None, None


    def is_free(self) -> bool:
        return self.val == "."
    
    def get_next(self):
        if not self.is_free():
            if self.val == ">":
                return self.hoyre
            elif self.val == "v":
                return self.ned        

ls = []
with open("input.txt", "r") as f:
#with open("test.txt", "r") as f:
    ls = [x.strip() for x in f.readlines()]

grid = []
all_nodes = []
for l in ls:
    grid.append([])
    for c in l:
        x = Node(c)
        grid[-1].append(x)

for i, row in enumerate(grid):
    for j, x in enumerate(row):
        h, d = None, None
                
        if i + 1 >= len(grid):
            d = grid[0][j]
        else:
            d = grid[i + 1][j]
        x.ned = d

        if j + 1 >= len(grid[i]):
            h = grid[i][0]
        else:
            #print(i, j)
            h = grid[i][j + 1]
        x.hoyre = h
            
        all_nodes.append(x)
print(f"{len(all_nodes)} nodes")

def tegn_grid():
    for row in grid:
        for x in row:
            print(x.val, end="")
            #print(x.id,",", end="")
        print()
    print()
has_m = True
res = 0
d = {
    ">": set(),
    "v": set()
}
for x in all_nodes:
    if x.val == "v":
        d["v"].add(x)
    elif x.val == ">":
        d[">"].add(x)

while has_m:
    #tegn_grid()
    res += 1
    has_m = False
    for c in d.keys():
        if res > 2:
            #break
            pass
        cmds = []    
        
        for x in d[c]:
            y = x.get_next()
            if y and y.is_free():
                cmds.append((x, y))

        for x, y in cmds:
            has_m = True
            x.val, y.val = y.val, x.val
            d[c].remove(x)
            d[c].add(y)
print("res:", res)