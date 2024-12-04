def get_letter_pos(letter):
    yield from ((y, x) for y, l in enumerate(grid) for x, sl in enumerate(l) if sl == letter)
def cand_is_in_bounds(x: int, y: int, grid) -> bool:
    return x >= 0 and x < len(grid) and y >= 0 and y < len(grid[0])

grid = [list(y) for x in open(0).readlines() if (y := x.strip())]
part1 = sum(1 for r, c in get_letter_pos("X")for dr in (-1, 0, 1)for dc in (-1, 0, 1)if (dr != 0 or dc != 0) and cand_is_in_bounds(r + 3 * dr, c + 3 * dc, grid) and grid[r + dr][c + dc] == "M" and grid[r + 2 * dr][c + 2 * dc] == "A" and grid[r + 3 * dr][c + 3 * dc] == "S")
print("Part1:", part1)
part2 = sum(("MMSS", "SSMM", "SMMS", "MSSM").count("".join([grid[r + dr][c + dc]for dr, dc in ((-1, -1), (-1, 1), (1, 1), (1, -1))if cand_is_in_bounds(r + dr, c + dc, grid)]))for r, c in get_letter_pos("A"))
print("Part2:", part2)
