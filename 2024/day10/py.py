def solve(trailhead):
    cand_is_in_bounds = lambda x,  y, grid: x >= 0 and x < len(grid) and y >= 0 and y < len(grid[0])
    q, d = [trailhead], {}
    while len(q):
        r, c = q.pop()
        if grid[r][c] == "9":
            d[r, c] = d.get((r, c), 0) + 1
        q += ((nr, nc) for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1))if cand_is_in_bounds((nr := r + dr), (nc := c + dc), grid) and int(grid[nr][nc]) - int(grid[r][c]) == 1)
    return len(d.keys()), sum(d.values())

grid = [list(y) for x in open(0).readlines() if (y := x.strip())]
p1, p2 = map(sum, zip(*[solve(trailhead)for trailhead in ((y, x)for y, l in enumerate(grid) for x, sl in enumerate(l) if sl == "0")]))
print("Part1:", p1)
print("Part2:", p2)
