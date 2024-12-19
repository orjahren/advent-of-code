import sys


def print_trie(trie, indent=0):
    if type(trie) is not dict:
        # print('  ' * indent, trie)
        return
    for k, v in trie.items():
        print('  ' * indent, k)
        print_trie(v, indent + 1)


seen = set()


def patternCanBeMade(pattern, trie):
    if pattern in seen:
        return False
    seen.add(pattern)
    print("**** checking pattern: ", pattern)
    node = trie
    print("pattern: ", pattern)
    for idx, c in enumerate(pattern):
        print("c: ", c)
        if c not in node:
            return patternCanBeMade(pattern[idx:], trie)
        # if canConsumeWithFinality(node, pattern[idx:]):
        if '$' in node[c]:
            print("node: ", node)
            node = node[c]
    return '$' in node


def main():
    towels = sys.stdin.readline().strip().replace(",", "").split()
    print(towels)
    print("--")
    patterns = [y for x in sys.stdin.readlines() if (y := x.strip())]
    print(patterns)

    trie = {}
    # create trie with exact prefixes
    for towel in towels:
        print("towel: ", towel)
        node = trie
        for c in towel:
            if c not in node:
                node[c] = {}
            node = node[c]
        node['$'] = True

    print("trie: ", trie)
    print_trie(trie)
    # return

    # count patterns that can be made from towels
    count = 0
    for pattern in patterns:
        seen.clear()
        print("\tmain pattern: ", pattern)
        if patternCanBeMade(pattern, trie):
            count += 1
            print(pattern, "can be made")
        else:
            print(pattern, "cannot be made")

    print("Part 1:", count)
# 377 too high


if __name__ == "__main__":
    main()
