# ll = [x.strip() for x in open("small").readlines()]
ll = [x.strip() for x in open("input").readlines()]


def get_score(val):
    if val < 97:
        return val - 64 + 26
    else:
        return val - 96


res = 0
for i in range(0, len(ll), 3):
    a, b, c = ll[i], ll[i + 1], ll[i + 2]
    common = set(a).intersection(set(b)).intersection(set(c))
    score = get_score(ord(list(common)[0]))
    res += score

print("Part 2:", res)
