# with open("small", "r") as f:
with open("input", "r") as f:
    buf = f.readline()
    for i, s in enumerate(buf):
        if i > 3:
            if len(set(buf[i - 4 : i])) == 4:
                print("Part 1:", i)
                exit()
