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
    f = 1
    ex = r"(do\(\))|(don't\(\))|(do_not\(\))|(mul\(\d{1,3},\d{1,3}\))"
    return sum(((f := do and (not (dont or donot)) or (mul and f))
                and not do and eval_hit(mul) or 0)
               for do, dont, donot, mul in re.findall(ex, s))


print("Part 1:", part1())
print("Part 2:", part2())
