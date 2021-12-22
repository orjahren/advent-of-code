from collections import defaultdict
import functools
import operator

class Cube:
    def __init__(self, x, y, z) -> None:
        self.x = x
        self.y = y
        self.z = z
        self.on = False
    
    def set_on(self):
        self.on = True

    def set_off(self):
        self.on = False

all_cubes = []
dd = defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: False)))
#with open("input.txt", "r") as f:
with open("test.txt", "r") as f:
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
                    a = dd[x][y][z]
                    if a == False:
                        ny = Cube(x, y, z)
                        dd[x][y][z] = ny
                        all_cubes.append(ny)
                        a = ny
                    if cmd == "on":
                        a.set_on()
                    else:
                        a.set_off()
res = len(list(filter(lambda x: x.on, all_cubes)))
print("res:", res)