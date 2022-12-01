x, y, z = 0, 0, 0
with open("input.txt", "r") as f:
    for l in f.readlines():
        a, b = l.split(" ")
        ins, arg = a[0].upper(), int(b)
        if ins == "F":
            x += arg
            y += z * arg
        elif ins == "U":
            z -= arg
        elif ins == "D":
            z += arg
print("res:", x*y)