import re

s = open(0).read()


def eval_hit(hit: str) -> int:
    l, r = hit[4:-1].split(",")
    return int(l) * int(r)


def part1():
    ex = r"mul\(\d{1,3},\d{1,3}\)"
    hits = re.findall(ex, s)

    return sum(eval_hit(hit) for hit in hits)


def part2():
    ex = r"(do\(\))|(don't\(\))|(do_not\(\))|(mul\(\d{1,3},\d{1,3}\))"
    hits = re.findall(ex, s)

    res = 0
    should_mul = True

    for hit in hits:
        if hit[1] or hit[2]:
            should_mul = False
        elif hit[0]:
            should_mul = True
            continue

        if should_mul:
            res += eval_hit(hit[3])

    return res


print("Part 1:", part1())
print("Part 2:", part2())
