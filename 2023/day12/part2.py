# Stolen from https://github.com/hyper-neutrino/advent-of-code/blob/main/2023/day12p1.py

from functools import cache
import numba


@cache
# @numba
def count(cfg, nums):
    if cfg == "":
        return 1 if nums == () else 0

    if nums == ():
        return 0 if "#" in cfg else 1

    result = 0

    if cfg[0] in ".?":
        result += count(cfg[1:], nums)

    if cfg[0] in "#?":
        if (
            nums[0] <= len(cfg)
            and "." not in cfg[: nums[0]]
            and (nums[0] == len(cfg) or cfg[nums[0]] != "#")
        ):
            result += count(cfg[nums[0] + 1 :], nums[1:])

    return result


part2 = 0
for line in open(0):
    cfg, nums = line.split()
    cfg = "?".join([cfg] * 5)
    nums = tuple(map(int, nums.split(",")))
    nums *= 5
    part2 += count(cfg, nums)
print("Part 2:", part2)
