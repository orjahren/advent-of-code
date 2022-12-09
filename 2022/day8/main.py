ll = [[int(y) for y in list(x.strip())] for x in open("input").readlines()]


def part_1():
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
    return sum([1 for y in range(len(bitmap)) for x in range(len(bitmap[y])) if bitmap[y][x] == 1])


def part_2():
    m = 0
    for row in range(len(ll)):
        for col in range(len(ll)):
            cand = 1
            for test in [
                [ll[row][y] for y in range(col - 1, -1, -1)],
                [ll[row][y] for y in range(col + 1, len(ll))],
                [ll[x][col] for x in range(row - 1, -1, -1)],
                [ll[x][col] for x in range(row + 1, len(ll))],
            ]:
                curr_score = 0
                for val in test:
                    curr_score += 1
                    if val >= ll[row][col]:
                        break
                cand *= curr_score
            if m < cand:
                m = cand
    return m


print("Part 1:", part_1())
print("Part 2:", part_2())
