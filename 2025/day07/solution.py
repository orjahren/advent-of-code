
grid = [list(line.strip()) for line in open(0, "r", encoding="utf-8")]

start = [(r, c) for r, row in enumerate(grid)
         for c, char in enumerate(row) if char == "S"][0]
print(start)
beams = [start]
seen = {start}


def add(r, c):
    if (r, c) in seen:
        return
    seen.add((r, c))
    beams.append((r, c))


p1 = 0

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

print("Part 1:", p1)
