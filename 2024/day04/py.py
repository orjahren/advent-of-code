from typing import List, Set, Tuple


def get_letter_pos(grid, letter):
    return [(y, x) for y, l in enumerate(grid) for x, sl in enumerate(l) if sl == letter]


def cand_is_in_bounds(x: int, y: int, grid) -> bool:
    return x >= 0 and x < len(grid) and y >= 0 and y < len(grid[0])


def part1(grid):

    res = 0
    for r, c in get_letter_pos(grid, "X"):
        for dr in (-1, 0, 1):
            for dc in (-1, 0, 1):
                if dr == dc == 0:
                    continue

                end_tup = r + 3 * dr, c + 3 * dc
                if not cand_is_in_bounds(*end_tup, grid):
                    continue

                s1 = grid[r + dr][c + dc]
                s2 = grid[r + 2 * dr][c + 2 * dc]
                s3 = grid[r + 3 * dr][c + 3 * dc]

                if s1 == "M" and s2 == "A" and s3 == "S":
                    res += 1
    return res


def part2(grid):
    return sum(("MMSS", "SSMM", "SMMS", "MSSM").count("".join([grid[r + dr][c + dc]for dr, dc in ((-1, -1), (-1, 1), (1, 1), (1, -1))if cand_is_in_bounds(r + dr, c + dc, grid)]))for r, c in get_letter_pos(grid, "A"))


def main():
    grid = [list(y) for x in open(0).readlines() if (y := x.strip())]
    print("Part1:", part1(grid))
    print("Part2:", part2(grid))
main()
