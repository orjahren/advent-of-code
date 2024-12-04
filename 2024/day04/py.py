from typing import Dict, List, Set, Tuple

Path = List[Tuple[int, int]]
TARGET_STR = "XMAS"

global_grid = [list(y) for x in open(0).readlines() if (y := x.strip())]

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
            target.append(path)
        return
    if not nei:
        return
    x, y = nei
    ch = global_grid[x][y]
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


def main():

    global_paths = []
    rd: Dict[Tuple[int, int], Path] = {}
    for x, y in x_positions:
        res = do_search((x, y))
        if len(res) > 0:
            rd[x, y] = res
            for p in res:
                if p not in global_paths:
                    global_paths.append(p)

    flat_paths = [tup for xs in global_paths for tup in xs]
    flat_paths = list(set(flat_paths))

    print("Res:", len(global_paths))


main()
