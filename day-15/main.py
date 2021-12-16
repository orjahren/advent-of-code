from collections import defaultdict

ls = []
s = None
dd = defaultdict(lambda x: False)
cnt = defaultdict(int)
with open("input.txt", "r") as f:
    s = f.readline().rstrip()
    f.readline()
    ls = [x.strip() for x in f.readlines()]
    
grid = []
for l in ls:
    grid.append([])
    for c in l:
        grid[-1].append(int(c))
print(grid)