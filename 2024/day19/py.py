import sys


def print_trie(trie, indent=0):
    if type(trie) is not dict:
        # print('  ' * indent, trie)
        return
    for k, v in trie.items():
        print('  ' * indent, k)
        print_trie(v, indent + 1)


cache = {}


def count_ways_to_construct(target, prefixes):
    # Initialize a DP table where dp[i] is the number of ways to construct target[:i]
    dp = [0] * (len(target) + 1)
    # Base case: one way to construct the empty string (by using no prefixes)
    dp[0] = 1

    # Iterate over each position in the target
    for i in range(1, len(target) + 1):
        # Check each prefix
        for prefix in prefixes:
            if i >= len(prefix):
                # If the substring ending at position i matches the prefix
                if target[i - len(prefix):i] == prefix:
                    dp[i] += dp[i - len(prefix)]

    return dp[len(target)]


def countWaysToMakePattern(pattern, root_trie):
    print(f"countWaysToMakePattern called with pattern: {pattern}")
    if pattern in cache:
        print(f"Cache hit for pattern: {pattern}, returning: {cache[pattern]}")
        return cache[pattern]
    if not pattern:
        print(f"Pattern is empty, returning 1")
        return 1

    node = root_trie
    total_ways = 0
    for idx, c in enumerate(pattern):
        if c not in node:
            print(f"Character {c} not found in trie at index {idx}, returning 0")
            cache[pattern] = 0
            return 0

        node = node[c]
        if '$' in node:
            print(f"End of towel found in trie at index {idx}, checking remaining pattern: {pattern[idx + 1:]}")
            total_ways += countWaysToMakePattern(pattern[idx + 1:], root_trie)

    cache[pattern] = total_ways
    print(f"Pattern: {pattern}, total ways: {total_ways}")
    return total_ways


def main():
    towels = sys.stdin.readline().strip().replace(",", "").split()
    print(towels)
    print("--")
    patterns = [y for x in sys.stdin.readlines() if (y := x.strip())]
    print(patterns)

    root_trie = {}
    # create trie with exact prefixes
    for towel in towels:
        print("towel: ", towel)
        node = root_trie
        for c in towel:
            if c not in node:
                node[c] = {}
            node = node[c]
        node['$'] = True

    print("trie: ", root_trie)
    print_trie(root_trie)
    # return

    # count patterns that can be made from towels
    p1 = 0
    p2 = 0
    for pattern in patterns:
        cache.clear()
        print("\tmain pattern: ", pattern)
        n_ways = count_ways_to_construct(pattern, towels)
        if n_ways > 0:
            p1 += 1
            print(pattern, "can be made")
        else:
            print(pattern, "cannot be made")
        p2 += n_ways

        # dp_count += can_construct(pattern, towels)

    print("Part 1:", p1)
    print("Part 2:", p2)


if __name__ == "__main__":
    main()
