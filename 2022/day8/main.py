def main(ll):
    # print(ll)

    bitmap = [[0 for _ in x] for x in ll]
    def_trees = 0
    for y in range(len(ll)):
        for x in range(len(ll[1])):
            # print(i, j)
            if y == 0 or x == 0 or y == len(ll) - 1 or x == len(ll) - 1:
                bitmap[y][x] = "X"
                def_trees += 1
    print("Initted", def_trees, " def trees")

    for row in range(len(ll)):
        for col in range(len(ll)):
            tests = [
                [ll[x][col] for x in range(row)],  # down
                [ll[x][col] for x in range(len(ll) - 1, row, -1)],  # up
                [ll[row][y] for y in range(len(ll) - 1, col, -1)],  # back
                [ll[row][y] for y in range(col)],  # forward
            ]

            for idx, test in enumerate(tests):
                if max(test, default=99999) < ll[row][col]:
                    bitmap[row][col] = 1
    # res = len(ll) * 2
    res = 0
    for y in range(len(bitmap)):
        for x in range(len(bitmap[y])):
            l = bitmap[y][x]
            if l == 1 or l == "X":
                res += 1
    print("Part 1:", res)


if __name__ == "__main__":
    file_names = ["input", "small"]
    for filename in file_names:
        ll = [[int(y) for y in list(x.strip())] for x in open(filename).readlines()]
        main(ll)
