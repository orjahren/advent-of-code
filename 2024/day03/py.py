import re

s = open(0).read()
print(s)


def eval_hit(hit: str) -> int:
    print("HIT:", hit)
    l, r = hit.split(",")
    l = int(l[4:])
    r = int(r[:-1])
    print(l, r)
    return r * l


def part1():
    ex = r"mul\(\d{1,3},\d{1,3}\)"
    hits = re.findall(ex, s)

    return sum(eval_hit(hit) for hit in hits)


def part2():
    # ex = r"(do\(\))|(don't\(\))|(mul\(\d{1,3},\d{1,3}\))"
    ex = r"(do\(\))|(don't\(\))|(do_not\(\))|(mul\(\d{1,3},\d{1,3}\))"
    hits = re.findall(ex, s)

    # print(hits)

    res = 0
    should_mul = True

    for hit in hits:
        print(hit)
        if hit[1] or hit[2]:
            should_mul = False
            print("SKRUR AV MUL")
        elif hit[0]:
            should_mul = True
            print("SKRUR på MUL")
            continue

        if should_mul:
            res += eval_hit(hit[3])

    return res


# print("Part 1:", part1())
print("Part 2:", part2())
