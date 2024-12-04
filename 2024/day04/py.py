from typing import Iterator, List, Set, Tuple

type Path = List[Tuple[int, int]]
TARGET_STR = "XMAS"

global_paths: List[Path] = []
global_grid = [list(y) for x in open(0).readlines() if (y := x.strip())]
print("Dimensjoner:", len(global_grid), len(global_grid[0]))

x_positions = [(x, y) for x, l in enumerate(global_grid)
               for y, sl in enumerate(l) if sl == "X"]


def cand_is_in_bounds(x: int, y: int) -> bool:
    return x >= 0 and x < len(global_grid) and y >= 0 and y < len(global_grid[0])


def get_neighbors(x: int, y: int) -> Iterator[Tuple[int, int]]:
    print("Naboer for", x, y)
    for xp in [-1, 0, 1]:
        for yp in [-1, 0, 1]:
            # Vil ikke ha seg selv
            if xp == yp == 0:
                continue
            cand = x + xp, y + yp
            if cand_is_in_bounds(*cand):
                yield cand


def print_grid(grid: List[List[str]], flattened_paths: Path = []) -> None:
    for i, row in enumerate(grid):
        for j, c in enumerate(row):
            if len(flattened_paths):
                print(c if (i, j) in flattened_paths and len(
                    flattened_paths) else ".", end="")
            else:
                print(c, end="")
        print("")


def path_to_str(path: List[Tuple[int, int]]) -> str:
    return "".join([global_grid[x][y] for x, y in path])


def path_is_found(path: Path) -> bool:
    return path in global_paths


def recurse(tup: Tuple[int, int], path: Path, visited_set: Set[str], target: List[Path]) -> None:
    for nei in get_neighbors(*tup):
        print("Sjekker nei:", nei)
        print("Path:", path)
        print(path_to_str(path))
        x, y = nei
        ch = global_grid[x][y]
        is_finished = path_to_str(path) == TARGET_STR
        if nei in visited_set or is_finished:
            if is_finished and not path_is_found(path):
                global_paths.append(path)
                target.append(path)
            continue
        visited_set.add(nei)
        exp_ch = TARGET_STR[len(path)]
        if ch == exp_ch:
            print("LEGGER I PATH:", nei)
            path.append(nei)
            recurse(nei, list(path), set(visited_set), target)


def do_search(start_pos: Tuple[int, int]) -> List[List[Tuple[int, int]]]:
    print("\t\t\t*** Skal søke fra", start_pos)
    res = []
    recurse(start_pos, [start_pos], set(start_pos), res)
    print("Res:", res)
    return res


print(global_grid)
print_grid(global_grid)

print(x_positions)

for x, y in x_positions:
    print(x, y, "=", end=" ")
    print(global_grid[x][y])
    nb = list(get_neighbors(x, y))
    print(nb)
    res = do_search((x, y))
    print("Res:")
    print(res)
    # print(path_to_str(res))


def paths_are_same(p1: Path, p2: Path) -> bool:
    return len(p1) == len(p2) and all(p1[x] == p2[x] for x in range(p1))


print("Global matches:")
print(global_paths)
print(len(global_paths))

flat_paths = [x for xs in global_paths for x in xs]
flat_paths = list(set(flat_paths))
print_grid(global_grid, flat_paths)
