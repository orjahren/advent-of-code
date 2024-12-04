from typing import Dict, List, Set, Tuple

Path = List[Tuple[int, int]]
TARGET_STR = "XMAS"

global_grid = [list(y) for x in open(0).readlines() if (y := x.strip())]
print("Dimensjoner:", len(global_grid), len(global_grid[0]))

x_positions = [(y, x) for y, l in enumerate(global_grid)
               for x, sl in enumerate(l) if sl == "X"]


def cand_is_in_bounds(x: int, y: int) -> bool:
    return x >= 0 and x < len(global_grid) and y >= 0 and y < len(global_grid[0])


def get_neighbor(x: int, y: int, direction: Tuple[int, int]) -> Tuple[int, int]:
    xp, yp = direction
    cand = x + xp, y + yp
    if cand_is_in_bounds(*cand):
        return cand
    return None


def print_grid(grid: List[List[str]], flattened_paths: Path = None) -> None:
    for i, row in enumerate(grid):
        for j, c in enumerate(row):
            """
            if (i, j) == (0, 2):
                print("O", end="")
                continue
            """
            if flattened_paths is not None:
                print(c if (i, j) in flattened_paths else ".", end="")
            else:
                print(c, end="")
        print("")


def path_to_str(path: List[Tuple[int, int]]) -> str:
    return "".join([global_grid[x][y] for x, y in path])


def recurse(
    tup: Tuple[int, int],
    path: Path,
    visited_set: Set[Tuple[int, int]],
    target: List[Path],
    direction: Tuple[int, int],
) -> None:
    is_finished = len(path) == len(TARGET_STR)
    nei = get_neighbor(*tup, direction)
    if (nei in visited_set) or is_finished:
        if is_finished and path_to_str(path) == TARGET_STR:
            print("FUNNET EN VEI:", path)
            target.append(path)
        return
    if not nei:
        return
    x, y = nei
    ch = global_grid[x][y]
    print("Sjekker nei:", nei, ch)
    print("Path:", path)
    print(path_to_str(path))
    visited_set.add(nei)
    print("Skal sjekke exp char med path:", path)
    print(path_to_str(path))
    print(len(path))
    exp_ch = TARGET_STR[len(path)]
    print("Exp char:", exp_ch, "ch:", ch)
    if ch == exp_ch:
        print("LEGGER I PATH:", nei)
        path.append(nei)
        recurse(nei, list(path), set(visited_set), target, direction)


def do_search(start_pos: Tuple[int, int]) -> List[List[Tuple[int, int]]]:
    print("\t\t\t*** Skal søke fra", start_pos)
    res = []
    # Up, Down, Left, Right, and Diagonals
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1),
                  (-1, -1), (-1, 1), (1, -1), (1, 1)]
    for direction in directions:
        print("\t*** Sjekker retning:", direction)
        recurse(start_pos, [start_pos], set([start_pos]), res, direction)
    print("do serach res:", res)
    return res


print(global_grid)
print_grid(global_grid)


def main():

    global_paths = []
    rd: Dict[Tuple[int, int], Path] = {}
    for x, y in x_positions:
        if x < 9 or y != 3:
            pass
        print(x, y, "=", end=" ")
        print(global_grid[x][y])
        res = do_search((x, y))
        print("Main res:")
        print(res)

        if len(res) > 0:
            rd[x, y] = res
            for p in res:
                if p not in global_paths:
                    global_paths.append(p)

    def paths_are_same(p1: Path, p2: Path) -> bool:
        return len(p1) == len(p2) and all(p1[x] == p2[x] for x in range(len(p1)))

    print("Global paths:")
    print(global_paths)
    print(len(global_paths))

    flat_paths = [tup for xs in global_paths for tup in xs]
    flat_paths = list(set(flat_paths))

    print(rd)

    print("Flat paths:")
    print(flat_paths)
    print(len(flat_paths))
    print_grid(global_grid)
    print("\n\t-----\n")
    print_grid(global_grid, flat_paths)

    print("Res:", len(global_paths))


main()
