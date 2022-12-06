with open("input", "r") as f:
    buf = f.readline()
    for i in range(len(buf)):
        if i > 13 and len(set(buf[i - 14 : i])) == 14:
            print("Part 2:", i)
