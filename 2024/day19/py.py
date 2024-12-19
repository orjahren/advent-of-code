import sys


def count_ways_to_construct(target, prefixes):
    dp = [0] * (len(target) + 1)
    dp[0] = 1
    for i in range(1, len(target) + 1):
        for prefix in prefixes:
            if i >= len(prefix):
                if target[i - len(prefix):i] == prefix:
                    dp[i] += dp[i - len(prefix)]
    return dp[len(target)]


towels = sys.stdin.readline().strip().replace(",", "").split()
patterns = [y for x in sys.stdin.readlines() if (y := x.strip())]
res = [count_ways_to_construct(pattern, towels) for pattern in patterns]
print("Part 1:", len([x for x in res if x > 0]))
print("Part 2:", sum(res))
