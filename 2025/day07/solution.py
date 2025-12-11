from functools import lru_cache

grid = [list(line.strip()) for line in open(0, "r", encoding="utf-8")]

start = [(r, c) for r, row in enumerate(grid)
         for c, char in enumerate(row) if char == "S"][0]
print(start)


def get_p1():
    beams = [start]
    seen = {start}
    p1 = 0

    def add(r, c):
        if (r, c) in seen:
            return
        seen.add((r, c))
        beams.append((r, c))

    while len(beams) > 0:
        r, c = beams.pop(0)
        if grid[r][c] == "." or grid[r][c] == "S":
            if r == len(grid) - 1:
                continue
            add(r + 1, c)
        elif grid[r][c] == "^":
            p1 += 1
            add(r, c - 1)
            add(r, c + 1)
    return p1


def get_p2():
    @lru_cache
    def solve(r, c):
        if r >= len(grid):
            return 1

        if grid[r][c] == "." or grid[r][c] == "S":
            return solve(r + 1, c)
        elif grid[r][c] == "^":
            return solve(r, c - 1) + solve(r, c + 1)
    return solve(start[0], start[1])


print("Part 1:", get_p1())
print("Part 2:", get_p2())
