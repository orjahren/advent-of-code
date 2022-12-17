ll = [z for l in open("input", "r").readlines() if (z := l.rstrip())]
ll = [(eval(x), eval(y)) for x, y in zip(ll[::2], ll[1::2])]


def is_in_order(a, b):
    print("Kalles med:", a, b)

    for i in range(min(len(a) if isinstance(a, list) else a, len(b) if isinstance(b, list) else b)):
        isListLeft = False if isinstance(a, int) else isinstance(a[i], list)
        isListRight = False if isinstance(b, int) else isinstance(b[i], list)

        if isListLeft and isListRight:
            result = is_in_order(a[i], b[i])
        elif isListLeft:
            result = is_in_order(a[i], [b[i]])
        elif isListRight:
            result = is_in_order([a[i]], b[i])
        else:
            if a[i] > b[i]:
                result = 1
            elif a[i] == b[i]:
                result = 0
            else:
                result = -1

        if result:
            return result
    if len(a) > len(b):
        return 1
    elif len(a) == len(b):
        return 0
    else:
        return -1


print(ll)
res = 0
for i, (x, y) in enumerate(ll):
    print("Skal se om er like:", x, y)
    val = is_in_order(x, y)
    if val == -1:
        print("Fant en match på idx", i)
        res += i + 1
print("Part 1:", res)
