from functools import cmp_to_key, reduce


def is_in_order(a, b):
    for i in range(min(len(a), len(b))):
        isListLeft = isinstance(a[i], list)
        isListRight = isinstance(b[i], list)
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


ll = [eval(z) for l in open("input", "r").readlines() if (z := l.rstrip())]
part1 = 0
for i, (x, y) in enumerate(zip(ll[::2], ll[1::2])):
    if is_in_order(x, y) == -1:
        part1 += i + 1
print("Part 1:", part1)
ll = sorted(ll + [[[6]], [[2]]], key=cmp_to_key(is_in_order))
l = []
for i, x in enumerate(ll):
    for y in [[[6]], [[2]]]:
        if is_in_order(x, y) == 0:
            l.append(i)
print("Part 2:", reduce(lambda x, y: (1 + x) * (1 + y), l))
