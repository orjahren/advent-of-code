stacks = [[] for _ in range(9)]  # manuell minne-allokering??
ops = []
# print(stacks)
# with open("small", "r") as f:
with open("input", "r") as f:
    ll = f.readlines()
    lager_stax = True
    for l in ll:
        # l = l.strip()
        print(l)

        spl = l.split()
        print("spl:", spl)

        if len(spl) == 0:
            lager_stax = False
            continue

        if lager_stax:
            # this is so stupid lol
            for lix, i in enumerate(range(1, len(l), 4)):
                print("li:", l[i])
                print("i:", i)
                if l[i].strip():
                    print("l1.strip:", l[i].strip())
                    print("idx:", lix)
                    stacks[lix].append(l[i])
            # stacks.append(spl)
        else:
            ops.append(spl)

print(stacks)
print(ops)


while len(ops) > 0:
    cmd = ops.pop(0)
    n = int(cmd[1])
    fra = stacks[int(cmd[3]) - 1]
    til = stacks[int(cmd[5]) - 1]

    print("Skal flytte", n, "fra", fra, "til", til)

    for _ in range(n):
        flytt = fra.pop(0)
        til.insert(0, flytt)

print("****ferdig***")
print(stacks)
print("Part 1:", "".join([x[0] for x in stacks]))
