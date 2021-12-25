class Node:
    cnt = 0
    def __init__(self, val) -> None:
        self.val = val
        self.l = []
        self.id = Node.cnt
        Node.cnt += 1
        self.visited = False
        self.opp, self.ned, self.venstre, self.hoyre = None, None, None, None

    def __str__(self) -> str:
        return f"<NODE {self.id}, val:{self.val}, n_vos:{len(self.l)}>"

    def __repr__(self) -> str:
        return f"<node {self.val}, id:{self.id}, {len(self.l)} vos>"

    def __lt__(self, other):
        return self.val < other.val

    def is_free(self) -> bool:
        return self.val == "."
    
    def get_next(self):
        #print(self.val, self.id, "henter neste,", self.l)
        #print(self.opp, self.ned, self.venstre, self.hoyre)

        if not self.is_free():
            if self.val == ">":
                #print("Gir hoyre", self.hoyre)
                return self.hoyre
            elif self.val == "v":
                #print("Gir ned", self.ned)
                return self.ned
            else:
                pass
                print("Denne fant ingen neste")
        

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
#print("fikser kanter")
#for x in all_nodes:
    #x.opp, x.ned, x.venstre, x.hoyre = tuple([y for y in x.l if y])
#print("kanter fikset")
def tegn_grid():
    for row in grid:
        for x in row:
            print(x.val, end="")
            #print(x.id,",", end="")
        print()
    print()
has_m = True
res = 0
while has_m:
    tegn_grid()
    res += 1
    if res > 2:
        #break
        pass
    has_m = False
    for c in [">", "v"]:
        cmds = []    
        for x in all_nodes:
            if x.val == c:
                y = x.get_next()
                if y and y.is_free():
                    cmds.append((x, y))
        for x, y in cmds:
            if y.is_free():
                has_m = True
                print("flytter", x, "til", y)
                x.val, y.val = y.val, x.val
        """
        y = x.get_next()
        if y and y.is_free():
            cmds.append((x, y))
    #print(f"{len(cmds)} commands")
    for x, y in cmds:
        if y.is_free():
                has_m = True
                print("flytter", x, "til", y)
                x.val, y.val = y.val, x.val
        """
    
    print("curr:", res)
print("res:", res)

"""
print()
for x in all_nodes[80 : 90]:
    print(x.id, x.ned)

print()
for x in all_nodes[70 : 80]:
    print(x.id, x.ned)

print()
for x in all_nodes:
    print(x.id, x.ned, x.hoyre)
"""