stacks = [[] for _ in range(9)]
with open("input", "r") as f:
    lager_stax = True
    for l in f.readlines():
        spl = l.split()
        if len(spl) == 0:
            lager_stax = False
        elif lager_stax:
            # this is so stupid lol
            for lix, i in enumerate(range(1, len(l), 4)):
                if l[i].strip():
                    stacks[lix].append(l[i])
        else:
            fra = stacks[int(spl[3]) - 1]
            til = stacks[int(spl[5]) - 1]
            for i in range(int(spl[1])):
                til.insert(i, fra.pop(0))

print("Part 2:", "".join([x[0] for x in stacks if x]))
