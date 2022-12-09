ll = [(s[0], int(s[1])) for x in open("input").readlines() if (s := x.split())]
head, tail = [0, 0], [0, 0]
visited = set()
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
        tup = head[0] - tail[0], head[1] - tail[1]
        if tup in [(-2, 1), (-1, 2), (0, 2), (1, 2), (2, 1)]:
            tail[1] += 1
        if tup in [(1, 2), (2, 1), (2, 0), (2, -1), (1, -2)]:
            tail[0] += 1
        if tup in [(2, -1), (1, -2), (0, -2), (-1, -2), (-2, -1)]:
            tail[1] -= 1
        if tup in [(-1, -2), (-2, -1), (-2, -0), (-2, 1), (-1, 2)]:
            tail[0] -= 1
        visited.add(tuple(tail))
print("Part 1:", len(visited))
