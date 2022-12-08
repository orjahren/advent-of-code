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

    for y in range(1, len(ll) - 1):
        for x in range(1, len(ll[0]) - 1):
            # for i in range(len(ll)):
            # for j in range(len(ll[0])):
            # print(i, j)
            tree = ll[y][x]
            print("Sjekker om dette er synlig: (val, i, j)", tree, y, x)
            tests = []

            # fra x og opp til toppen
            if x == 1:
                print("0, 0")
                tests.append(ll[0][y] < tree)
            else:
                print("0, 1")
                print("Bruker denne rangen:")
                print([ll[a][y] for a in range(0, x)])
                tests.append(max([ll[a][y] for a in range(0, x)], default=999999) < tree)

            # fra venstre kant mot x
            if y == 1:
                print("1, 0")
                tests.append(ll[x][0] < tree)
            else:
                print("1, 1")
                r = [ll[x][a] for a in range(0, y)]
                print("r 1:", r)
                tests.append(max(r, default=9999999) < tree)

            # nedover til bunnen fra x
            """
            if y + 1 == len(ll) - 1:
                print("2, 0")
                print("-------- BRUKER j == len(ll)-testene")
                tests.append(ll[y][-1] < tree)
                print(tests[-1])
            else:
            """
            if True:
                print("2, 1")
                # print("j + 1", x + 1, "er ikke", len(ll) - 1)
                r = [ll[x][a] for a in range(y, len(ll))]
                print("r 2:", r)
                tests.append(max(r, default=999999) < tree)

            # fra x mot høyre kant
            if y + 1 == len(ll) - 1:
                print("3, 0")
                print("-------- BRUKER i == len(ll)-testene")
                tests.append(ll[y + 1][x] < tree)
            else:
                print("3, 1")
                tests.append(
                    max([ll[a][x] for a in range(y, len(ll))], default=999999) < tree,
                )

            assert len(tests) == 4, "Fucket opp fordeling av tester"

            for idx, test in enumerate(tests):
                if test:
                    bitmap[y][x] = 1
                    print("Er synlig ved test", idx)
    print("**** Har laget bitmap ****")
    res = 0
    for y in range(len(bitmap)):
        # for bl in bitmap:
        # for l in bl:
        for x in range(len(bitmap[y])):
            l = bitmap[y][x]
            if l == 1 or l == "X":
                res += 1
                # print("Fant noe synlig: (val, i, j)", ll[i][j], i, j)
    """
    for i in range(len(bitmap)):
        for j in range(len(bitmap[i])):
            l = bitmap[i][j]
            print(l, end="")
        print("")
    """
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
