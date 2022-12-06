# with open("small", "r") as f:
with open("input", "r") as f:
    buf = f.readline()
    for i, s in enumerate(buf):
        if i > 13:
            if len(set(buf[i - 14 : i])) == 14:
                print("Part 1:", i)
                # exit()
