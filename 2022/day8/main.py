ll = [[int(y) for y in list(x.strip())] for x in open("input").readlines()]
bitmap = [[0 for _ in x] for x in ll]
for y in range(len(ll)):
    for x in range(len(ll[1])):
        if y == 0 or x == 0 or y == len(ll) - 1 or x == len(ll) - 1:
            bitmap[y][x] = 1
for row in range(len(ll)):
    for col in range(len(ll)):
        for test in [
            [ll[x][col] for x in range(row)],
            [ll[x][col] for x in range(len(ll) - 1, row, -1)],
            [ll[row][y] for y in range(len(ll) - 1, col, -1)],
            [ll[row][y] for y in range(col)],
        ]:
            if max(test, default=99999) < ll[row][col]:
                bitmap[row][col] = 1
part1 = sum([1 for y in range(len(bitmap)) for x in range(len(bitmap[y])) if bitmap[y][x] == 1])
print("Part 1:", part1)
