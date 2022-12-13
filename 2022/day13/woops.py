ll = [z for l in open("small", "r").readlines() if (z := l.rstrip())]
ll = [(eval(x), eval(y)) for x, y in zip(ll[::2], ll[1::2])]


def is_in_order(a, b):
    if type(a) == int and type(b) == int:
        return a < b
    elif type(a) == list and type(b) == list:
        cand = True
        idx1, idx2 = 0, 0
        while cand:
            if idx1 >= len(a):
                return True
            elif idx2 >= len(b):
                return False
            x, y = a[idx1], b[idx2]
            check = is_in_order(x, y)
            if check:
                idx1 += 1
                idx2 += 1
            else:
                return False

    elif type(a) == int:  # hvis denne blir true kan ikke b også være et number
        return is_in_order([a], b)
    else:
        return is_in_order(a, [b])


print(ll)
res = 0
for i, (x, y) in enumerate(ll):
    print("Skal se om er like:", x, y)
    val = is_in_order(x, y)
    if val:
        print("Fant en match på idx", i)
        res += i
print("Part 1:", res)
# for
