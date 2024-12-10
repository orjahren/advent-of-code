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
    tx = int(grid[tr][tc])
    diff = tx - fx
    return diff == 1


def is_target(tup):
    r, c = tup
    return grid[r][c] == "9"


grid = [list(y) for x in open(0).readlines() if (y := x.strip())]


def get_trailhood_score(trailhead):
    q, p1, p2 = [trailhead], 0, {}
    while len(q):
        curr = q.pop()
        if is_target(curr):
            if not curr in p2:
                p1 += 1
                p2[curr] = 0
            p2[curr] += 1
        q.extend([neighbor for neighbor in get_neighbors(*curr) if neighbor_is_ok(curr, neighbor)])
    return p1, sum(p2.values())


part1, part2 = map(sum, zip(*[get_trailhood_score(trailhead) for trailhead in get_letter_pos("0")]))
print("Part1:", part1)
print("Part2:", part2)
