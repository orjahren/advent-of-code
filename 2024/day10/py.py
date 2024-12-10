def get_letter_pos(letter):
    yield from ((y, x) for y, l in enumerate(grid) for x, sl in enumerate(l) if sl == letter)


def cand_is_in_bounds(x: int, y: int, grid) -> bool:
    return x >= 0 and x < len(grid) and y >= 0 and y < len(grid[0])


grid = [list(y) for x in open(0).readlines() if (y := x.strip())]
part1 = -1
print("Part1:", part1)
for r, c in get_letter_pos("0"):
    l = [grid[r + dr][c + dc]
         for dr, dc in ((-1, -1), (-1, 1), (1, 1), (1, -1))if cand_is_in_bounds(r + dr, c + dc, grid)]
    print(l)
