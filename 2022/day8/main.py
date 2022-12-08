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
    # print(bitmap)
    print("Initted", def_trees, " def trees")

    for row in range(len(ll)):
        for col in range(len(ll)):
            # for i in range(len(ll)):
            # for j in range(len(ll[0])):
            # print(i, j)
            tree = ll[row][col]
            print("Sjekker om dette er synlig: (val, row, col)", tree, row, col)
            tests = [
                max([ll[row][y] for y in range(col)], default=99999),  # forward
                max([ll[row][y] for y in range(len(ll) - 1, col, -1)], default=9999),  # back
                max([ll[x][col] for x in range(row)], default=9999),  # down
                max([ll[x][col] for x in range(len(ll) - 1, row, -1)], default=9999),  # up
            ]

            assert len(tests) == 4, "Fucket opp fordeling av tester"

            for idx, test in enumerate(tests):
                if test < tree:
                    bitmap[row][col] = 1
                    print("Er synlig ved test", idx)
    print("**** Har laget bitmap ****")
    res = 0
    for y in range(len(bitmap)):
        for x in range(len(bitmap[y])):
            l = bitmap[y][x]
            if l == 1 or l == "X":
                res += 1
                # print("Fant noe synlig: (val, i, j)", ll[i][j], i, j)
    print("Part 1:", res)

    for y in range(len(bitmap)):
        for x in range(len(bitmap[y])):
            h = str(ll[y][x])
            bv = str(bitmap[y][x])
            print("|" + h + "" + bv + "", end="")
        print("")


if __name__ == "__main__":
    file_names = ["input", "small"]
    file_names = ["input"]
    file_names = ["input", "small"]
    for filename in file_names:
        # ll = [[int(y) for y in list(x.strip())] for x in open("small").readlines()]
        ll = [[int(y) for y in list(x.strip())] for x in open(filename).readlines()]
        main(ll)
