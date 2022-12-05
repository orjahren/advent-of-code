stacks = [[] for _ in range(9)]  # manuell minne-allokering??
ops = []
# with open("small", "r") as f:
with open("input", "r") as f:
    ll = f.readlines()
    lager_stax = True
    for l in ll:
        spl = l.split()
        if len(spl) == 0:
            lager_stax = False
            continue
        if lager_stax:
            # this is so stupid lol
            for lix, i in enumerate(range(1, len(l), 4)):
                if l[i].strip():
                    stacks[lix].append(l[i])
        else:
            ops.append(spl)

while len(ops) > 0:
    cmd = ops.pop(0)
    fra = stacks[int(cmd[3]) - 1]
    til = stacks[int(cmd[5]) - 1]

    for i in range(int(cmd[1])):
        til.insert(i, fra.pop(0))

print("Part 2:", "".join([x[0] for x in stacks if x]))
