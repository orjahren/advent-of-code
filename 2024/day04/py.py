from typing import List, Set, Tuple


def get_letter_pos(grid, letter):
    return [(y, x) for y, l in enumerate(grid) for x, sl in enumerate(l) if sl == letter]


def part1(grid):

    def cand_is_in_bounds(x: int, y: int) -> bool:
        return x >= 0 and x < len(grid) and y >= 0 and y < len(grid[0])

    res = 0
    for tup in get_letter_pos(grid, "X"):
        for dr in (-1, 0, 1):
            for dc in (-1, 0, 1):
                if dr == dc == 0:
                    continue
                print(dr, dc)
                r, c = tup

                end_tup = r + 3 * dr, c + 3 * dc
                if not cand_is_in_bounds(*end_tup):
                    continue

                s1 = grid[r + dr][c + dc]
                s2 = grid[r + 2 * dr][c + 2 * dc]
                s3 = grid[r + 3 * dr][c + 3 * dc]

                print(s1, s2, s3)

                if s1 == "M" and s2 == "A" and s3 == "S":
                    res += 1
    return res


def part2(grid):
    TARGET_STR = "MAS"

    def recurse(
        tup: Tuple[int, int],
        path: Path,
        visited_set: Set[Tuple[int, int]],
        target: List[Path],
        direction: Tuple[int, int],
    ) -> None:
        is_finished = len(path) == len(TARGET_STR)
        nei = get_neighbor(*tup, direction, grid)
        if is_finished:
            target.append(path)
        if not nei or is_finished:
            return
        x, y = nei
        ch = grid[x][y]
        visited_set.add(nei)
        exp_ch = TARGET_STR[len(path)]
        if ch == exp_ch:
            path.append(nei)
            recurse(nei, list(path), set(visited_set), target, direction)

    def do_search(start_pos: Tuple[int, int]) -> List[List[Tuple[int, int]]]:
        res = []
        # Up, Down, Left, Right, and Diagonals
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1),
                      (-1, -1), (-1, 1), (1, -1), (1, 1)]
        for direction in directions:
            recurse(start_pos, [start_pos], set([start_pos]), res, direction)
        return res

    def get_distance(p1: Tuple[int, int], p2: Tuple[int, int]) -> int:
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])
    m_positions = get_letter_pos(grid, "M")
    flat = ([x for xs in filter(lambda x: len(x) > 0, [do_search((x, y))
            for x, y in m_positions]) for x in xs])
    print(flat)
    print(len(flat))

    res = 0
    used_as = set()
    d = {}
    for m, a, s in flat:
        d[a] += d.get(a, 0) + 1
        used_as.add(a)
    for k, v in d.items():
        if v >= 2:
            res += 1

    return res


def main():
    grid = [list(y) for x in open(0).readlines() if (y := x.strip())]
    print("Part1:", part1(grid))
    # print("Part2:", part2(grid))


main()
