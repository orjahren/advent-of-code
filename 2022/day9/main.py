# ll = [(s[0], int(s[1])) for x in open("small").readlines() if (s := x.split())]
ll = [(s[0], int(s[1])) for x in open("input").readlines() if (s := x.split())]

print(ll)


def get_tup(head, old_tail, new_tail):
    return head[0] - old_tail[0], head[1] - old_tail[1]
    return head[0] - new_tail[0], head[1] - new_tail[1]


def update_tail(old_tail, head):
    print("Old tail:", old_tail)
    new_tail = list(old_tail)
    tup = get_tup(head, old_tail, new_tail)  # head[0] - new_tail[0], head[1] - new_tail[1]
    print("Tup er:", tup)
    if tup in [(-2, 1), (-1, 2), (0, 2), (1, 2), (2, 1)]:
        print("**************       matchet 1")
        new_tail[1] += 1
    else:
        print("Matchet ikke 1")

    tup = get_tup(head, old_tail, new_tail)  # head[0] - new_tail[0], head[1] - new_tail[1]
    # match ((head[0] - old_tail[0], head[1] - old_tail[1])):
    if tup in [(1, 2), (2, 1), (2, 0), (2, -1), (1, -2)]:
        print("**************       matchet 2")
        new_tail[0] += 1
    else:
        print("Matchet ikke 2")
    tup = get_tup(head, old_tail, new_tail)  # head[0] - new_tail[0], head[1] - new_tail[1]
    # match tup:  # (head[0] - old_tail[0], head[1] - old_tail[1]):
    # match ((head[0] - old_tail[0], head[1] - old_tail[1])):
    if tup in [(2, -1), (1, -2), (0, -2), (-1, -2), (-2, -1)]:
        print("**************       matchet 3")
        new_tail[1] -= 1
    else:
        print("Matchet ikke 3")
    tup = get_tup(head, old_tail, new_tail)  # head[0] - new_tail[0], head[1] - new_tail[1]
    # match tup:  # (head[0] - old_tail[0], head[1] - old_tail[1]):
    # match ((head[0] - old_tail[0], head[1] - old_tail[1])):
    if tup in [(-1, -2), (-2, -1), (-2, -0), (-2, 1), (-1, 2)]:
        print("**************       matchet 4")
        new_tail[0] -= 1
    else:
        print("Matchet ikke 4")

    print("New tail:", new_tail)
    return new_tail
    return tuple(new_tail)


# sjekk chess-distance for hver action
# hvis den ligger an til å bli mer enn 1 etter neste action må tail følge etter head
# hvis T og H ikke er i samme rad eller kolonne går T opp diagonalt

head, tail = [0, 0], [0, 0]
visited = set()
# visited.add(tuple(tail))

for act, val in ll:

    print("Head skal gå", val, "i retning", act)

    print("pre: Head, tail:", tuple(head), tuple(tail))
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

        tail = update_tail(tail, head)
        visited.add(tuple(tail))
        print("post: Head, tail:", tuple(head), tuple(tail))
print("Part 1:", len(visited))
