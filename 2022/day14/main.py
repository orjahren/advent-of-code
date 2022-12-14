with open("small") as f:
    ll = f.readlines()
    pairs = [[list(map(int, y.split(","))) for y in x.split("->")] for x in ll]


def print_grid(grid):
    for r in grid:
        for c in r:
            print(c, end="")
        print("")


print(pairs)

n = 20
width, height = 1000, 200
grid = [["." for _ in range(height)] for _ in range(width)]
print_grid(grid)
print("///////")
for path in pairs:
    for pos, length in path:
        print(pos, length)
# _ print(ml)
