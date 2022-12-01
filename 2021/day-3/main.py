with open("input.txt", "r") as f:
    bins = [list(b.strip()) for b in f.readlines()]

gam, eps = [None for _ in range(len(bins[0]))], [None for _ in range(len(bins[0]))]
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
print("res:", int("".join(gam), 2) * int("".join(eps), 2))