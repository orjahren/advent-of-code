def get_letter_pos(letter):
    yield from ((y, x) for y, l in enumerate(grid) for x, sl in enumerate(l) if sl == letter)


def cand_is_in_bounds(x: int, y: int, grid) -> bool:
    return x >= 0 and x < len(grid) and y >= 0 and y < len(grid[0])


def get_neighbors(r, c):
    yield from ((nr, nc) for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1))if cand_is_in_bounds((nr := r + dr), (nc := c + dc), grid) and int(grid[nr][nc]) - int(grid[r][c]) == 1)


def is_target(tup):
    r, c = tup
    return grid[r][c] == "9"


def solve(trailhead):
    q, d = [trailhead], {}
    while len(q):
        curr = q.pop()
        if is_target(curr):
            d[curr] = d.get(curr, 0) + 1
        q.extend(neighbor for neighbor in get_neighbors(*curr))
    return len(d.keys()), sum(d.values())


grid = [list(y) for x in open(0).readlines() if (y := x.strip())]
p1, p2 = map(sum, zip(*[solve(trailhead)for trailhead in get_letter_pos("0")]))
print("Part1:", p1)
print("Part2:", p2)
