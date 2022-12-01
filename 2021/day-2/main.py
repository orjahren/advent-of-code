x, y = 0, 0 
with open("input.txt", "r") as f:
    for l in f.readlines():
        a, b = l.split(" ")
        ins, arg = a[0].upper(), int(b)
        if ins == "F":
            x += arg
        elif ins == "U":
            y -= arg
        elif ins == "D":
            y += arg
print("res:", x*y)