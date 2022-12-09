ll = [(s[0], int(s[1])) for x in open("input").readlines() if (s := x.split())]


def update_common(tail, head, is_part_2=False):
    tup = head[0] - tail[0], head[1] - tail[1]
    new_tail = list(tail)

    dt = [(-2, 1), (-1, 2), (0, 2), (1, 2), (2, 1)]
    rt = [(1, 2), (2, 1), (2, 0), (2, -1), (1, -2)]
    ot = [(2, -1), (1, -2), (0, -2), (-1, -2), (-2, -1)]
    lt = [(-1, -2), (-2, -1), (-2, -0), (-2, 1), (-1, 2)]

    # add diagonal movement for part 2
    if is_part_2:
        dt.extend([(2, 2), (-2, 2)])
        rt.extend([(2, 2), (2, -2)])
        ot.extend([(-2, -1), (2, -2), (-2, -2)])
        lt.extend([(-1, 2), (-2, 2), (-2, -2)])

    if tup in dt:
        new_tail[1] += 1
    if tup in rt:
        new_tail[0] += 1
    if tup in ot:
        new_tail[1] -= 1
    if tup in lt:
        new_tail[0] -= 1
    return new_tail


knots = [[0, 0] for _ in range(10)]
head, tail = knots[0], knots[-1]
part1, part2 = set(), set()
part2.add(tuple(tail))
part1.add(tuple(tail))

for act, val in ll:
    for _ in range(val):
        match (act):
            case "U":
                head[1] += 1
            case "D":
                head[1] -= 1
            case "R":
                head[0] += 1
            case "L":
                head[0] -= 1

        for i in range(len(knots) - 1):
            knots[i + 1] = update_common(knots[i + 1], knots[i], True)
        tail = update_common(tail, head)
        part1.add(tuple(tail))
        part2.add(tuple(knots[-1]))

print("Part 1:", len(part1))
print("Part 2:", len(part2))
