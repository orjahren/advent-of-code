from collections import defaultdict
import functools
import operator

dd = defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: 0)))

#0 = undefined, 1 = on, -1 = off

#with open("input.txt", "r") as f:
#with open("test.txt", "r") as f:
with open("storre.txt", "r") as f:
    for line in f.readlines():
        split = line.split(" ")
        cmd = split[0]
        split = split[1:][0]
        
        ranges = split.split(",")
        for i, x in enumerate(ranges):
            ranges[i] = x[2:].strip()
            ranges[i] = tuple([int(val) for val in ranges[i].split("..")])
        x_range, y_range, z_range = ranges
        for x in range(x_range[0], x_range[1] + 1):
            for y in range(y_range[0], y_range[1] + 1):
                for z in range(z_range[0], z_range[1] + 1):
                    #print(x, y, z)
                    
                    if cmd == "on":
                        dd[x][y][z] = 1
                    else:
                        dd[x][y][z] = -1
print("begnin") 
res = 0
for x in dd.values():
    for y in x.values():
        for z in y.values():
            if z == 1:
                res += 1
        
#all_cubes = dd.values().values().values()
#res = len(list(filter(lambda x: x == 1, all_cubes)))
print("res:", res)