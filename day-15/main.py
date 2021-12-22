from heapq import heappop, heappush
from collections import defaultdict
class Node:
    cnt = 0
    def __init__(self, val) -> None:
        self.val = val
        self.l = []
        self.id = Node.cnt
        Node.cnt += 1
        self.visited = False

    def __str__(self) -> str:
        return f"<NODE {self.id}, val:{self.val}, n_vos:{len(self.l)}>"

    def __repr__(self) -> str:
        return f"<node {self.val}, id:{self.id}, {len(self.l)} vos>"

    def __lt__(self, other):
        return self.val < other.val
        

ls = []
with open("input.txt", "r") as f:
#with open("test.txt", "r") as f:
    ls = [x.strip() for x in f.readlines()]

grid = []
all_nodes = []
for l in ls:
    grid.append([])
    for c in l:
        c = int(c)
        x = Node(c)
        grid[-1].append(x)

for i, row in enumerate(grid):
    for j, x in enumerate(row):
        p = q = r = s = None
        try:
            if i > 0:
                p = grid[i - 1][j]
        except Exception:
            pass
        try:
            q = grid[i + 1][j]
        except Exception:
            pass
        try:
            if j > 0:
                r = grid[i][j - 1]
        except Exception:
            pass
        try:
            s = grid[i][j + 1]
        except Exception:
            pass
            
        x.l.extend([x for x in [p, q, r, s] if x])
        all_nodes.append(x)

def buildgraph(lines):
    V = set()
    E = defaultdict(set)
    w = dict()

    for l in lines:
        v, u, weight = l
        V.add(v)
        V.add(u)
        E[v].add(u)
        w[(v, u)] = weight
    return V, E, w

l = []
for x in all_nodes:
    for y in x.l:
        l.append((x.id, y.id, y.val))
lt = l

def dijkstra(G, s):
    V, E, w = G
    Q = [(0, s)]
    D = defaultdict(lambda: float("inf"))
    D[s] = 0

    while Q:
        cost, v = heappop(Q)
        for u in E[v]:
            c = cost + w[(v, u)]
            if c < D[u]:
                D[u] = c 
                heappush(Q, (c, u))
    return D

gr = buildgraph(lt)
d = dijkstra(gr, all_nodes[0].id)
print("res:", d[all_nodes[-1].id])