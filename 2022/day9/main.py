ll = [(s[0], int(s[1])) for x in open("input").readlines() if (s := x.split())]


def update_tail_2(tail, head):
    tup = head[0] - tail[0], head[1] - tail[1]
    new_tail = list(tail)
    if tup in [(-2, 1), (-1, 2), (0, 2), (1, 2), (2, 1), (2, 2), (-2, 2)]:
        new_tail[1] += 1
    if tup in [(1, 2), (2, 1), (2, 0), (2, -1), (1, -2), (2, 2), (2, -2)]:
        new_tail[0] += 1
    if tup in [(-2, -2), (2, -1), (1, -2), (0, -2), (-1, -2), (-2, -1), (2, -2)]:
        new_tail[1] -= 1
    if tup in [(-2, -2), (-1, -2), (-2, -1), (-2, -0), (-2, 1), (-1, 2), (-2, 2)]:
        new_tail[0] -= 1
    return new_tail


def update_tail_1(tail, head):
    tup = head[0] - tail[0], head[1] - tail[1]
    if tup in [(-2, 1), (-1, 2), (0, 2), (1, 2), (2, 1)]:
        tail[1] += 1
    if tup in [(1, 2), (2, 1), (2, 0), (2, -1), (1, -2)]:
        tail[0] += 1
    if tup in [(2, -1), (1, -2), (0, -2), (-1, -2), (-2, -1)]:
        tail[1] -= 1
    if tup in [(-1, -2), (-2, -1), (-2, -0), (-2, 1), (-1, 2)]:
        tail[0] -= 1
    return tail


knots = [[0, 0] for _ in range(10)]
head, tail = knots[0], knots[-1]
part2 = set()
part1 = set()
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
            knots[i + 1] = update_tail_2(knots[i + 1], knots[i])
        tail = update_tail_1(tail, head)
        part1.add(tuple(tail))
        part2.add(tuple(knots[-1]))

print("Part 1:", len(part1))
print("Part 2:", len(part2))
