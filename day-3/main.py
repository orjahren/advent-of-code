bins = []
with open("input.txt", "r") as f:
    for b in f.readlines():
        b = b.strip()
        bins.append(list(b))

gam, eps = [None for _ in range(len(bins[0]))], [None for _ in range(len(bins[0]))]
print(gam, eps)
for pos in range(len(bins[0])):
    ones, zeros = 0, 0
    for x in bins:
        if x[pos] == "1":#x.pop() == "1":
            ones += 1
        else:
            zeros += 1

    if ones > zeros:
        gam[pos] = "1"  
        eps[pos] = "0"
    else:
        gam[pos] = "0"  
        eps[pos] = "1"
print(gam, eps)
#print("res:", int("".join(gam[::-1]), 2) * int("".join(eps[::-1]), 2))
print("res:", int("".join(gam), 2) * int("".join(eps), 2))