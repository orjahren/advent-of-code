data = []
with open("input.txt", "r") as f:
    for l in f.readlines():
        a, b = l.split(" ")
        data.append((a[0].upper(), int(b)))
x, y = 0, 0 

for ins, arg in data:
    if ins == "F":
        x += arg
    elif ins == "U":
        y -= arg
    elif ins == "D":
        y += arg

print("res:", x*y)