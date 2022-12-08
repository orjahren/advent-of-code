ll = [[int(y) for y in list(x.strip())] for x in open("input").readlines()]
# ll = [[int(y) for y in list(x.strip())] for x in open("small").readlines()]


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
    scenic_scores = []
    for row in range(len(ll)):
        for col in range(len(ll)):
            scenic_scores.append(1)
            tree = ll[row][col]
            for test in [
                [ll[row][y] for y in range(col - 1, -1, -1)],  # left
                [ll[row][y] for y in range(col + 1, len(ll))],  # right
                [ll[x][col] for x in range(row - 1, -1, -1)],  # up
                [ll[x][col] for x in range(row + 1, len(ll))],  # down
            ]:
                curr_score = 0
                print("Tester på", ll[row][col], row, col)
                print(test)
                for val in test:
                    print("Sjekker om", val, "er lavere enn", val)
                    curr_score += 1
                    if val >= tree:
                        break
                print("En score er:", curr_score)
                scenic_scores[-1] *= curr_score
    print("Alle scores:")
    print(scenic_scores)
    return max(scenic_scores)


print("Part 1:", part_1())
print("Part 2:", part_2())
