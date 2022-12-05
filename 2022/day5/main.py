part2 = True
with open("input", "r") as f:
    stacks = [[] for _ in range(9)]
    for l in f.readlines():
        if l[0] == "m":
            spl = l.split()
            for i in range(int(spl[1])):
                stacks[int(spl[5]) - 1].insert(i if part2 else 0, stacks[int(spl[3]) - 1].pop(0))
        else:
            for lix, i in enumerate(range(1, len(l), 4)):
                if l[i].strip():
                    stacks[lix].append(l[i])
print("Part 2:" if part2 else "Part 1:", "".join([x[0] for x in stacks if x]))
