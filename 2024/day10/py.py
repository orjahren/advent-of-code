def get_letter_pos(letter):
    yield from ((y, x) for y, l in enumerate(grid) for x, sl in enumerate(l) if sl == letter)


def cand_is_in_bounds(x: int, y: int, grid) -> bool:
    return x >= 0 and x < len(grid) and y >= 0 and y < len(grid[0])


def get_neighbors(r, c):
    yield from ((r + dr, c + dc) for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1))if cand_is_in_bounds(r + dr, c + dc, grid))


def neighbor_is_ok(_from, to):
    fr, fc = _from
    tr, tc = to
    fx = int(grid[fr][fc])
    vx = grid[tr][tc]
    if vx == ".":
        return 0
    tx = int(grid[tr][tc])
    diff = fx - tx
    diff = tx - fx
    print("Diff mellom", _from, fx, "og", to, tx, "er", diff)
    return diff == 1


def is_target(tup):
    r, c = tup
    return grid[r][c] == "9"


grid = [list(y) for x in open(0).readlines() if (y := x.strip())]
trailhead_ress = []


def get_trailhood_score(trailhead):
    r, c = trailhead
    res = 0
    print("0:", r, c)
    q = [(r, c)]
    # visited = set(q[0])
    rs = {}
    while len(q):
        print(q)
        curr = q.pop()
        if is_target(curr):
            print("\t**** FOUND MATCH")
            rs[curr] = rs.get(curr, 0) + 1

            continue
        for neighbor in get_neighbors(*curr):
            # for neighbor in graph[s]:
            print(neighbor)
            if neighbor_is_ok(curr, neighbor):
                print("OK")
                # if neighbor not in visited:
                q.append(neighbor)
                # visited.add(neighbor)
            else:
                # print("Not OK")
                pass
    """
    l = [grid[r + dr][c + dc]
        for dr, dc in ((-1, -1), (-1, 1), (1, 1), (1, -1))if cand_is_in_bounds(r + dr, c + dc, grid)]
    """
    trailhead_ress.append(res)
    # print(l)
    return rs


trailheads = list(get_letter_pos("0"))
print(trailheads)
part1 = 0
for trailhead in trailheads:
    print(trailhead)
    ts = get_trailhood_score(trailhead)
    print(ts)
    part1 += sum(ts.values())
print("Part1:", part1)
