import re

s = open(0).read()

mul_ex = r"mul\(\d{1,3},\d{1,3}\)"


def eval_hit(hit: str) -> int:
    l, r = hit[4:-1].split(",")
    return int(l) * int(r)


def part1():
    return sum(eval_hit(hit) for hit in re.findall(mul_ex, s))


def part2() -> int:
    f = 1
    ex = r"(do\(\))|(don't\(\))|(" + mul_ex + ")"
    return sum(((f := do and (not dont) or (mul and f)) and not do and eval_hit(mul) or 0)for do, dont, mul in re.findall(ex, s))


print("Part 1:", part1())
print("Part 2:", part2())
