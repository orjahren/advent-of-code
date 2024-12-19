import sys


def print_trie(trie, indent=0):
    if type(trie) is not dict:
        # print('  ' * indent, trie)
        return
    for k, v in trie.items():
        print('  ' * indent, k)
        print_trie(v, indent + 1)


cache = {}


def patternCanBeMade(pattern, root_trie):
    if pattern in cache:
        return cache[pattern]
    cache[pattern] = ""
    print("**** checking pattern: ", pattern)
    node = root_trie
    print("pattern: ", pattern)
    for idx, c in enumerate(pattern):
        print("c: ", c)
        if c not in node:
            print("c not in node")
            cache[pattern] = False
            return False

        node = node[c]
        print("node: ", node)
        # check if prefix is a complete word
        if '$' in node:
            print("prefix is a complete word")
            if patternCanBeMade(pattern[idx + 1:], root_trie):
                cache[pattern] = True
                return True
            print("prefix is a complete word but rest of pattern cannot be made")

    cache[pattern] = "$" in node
    return cache[pattern]
    # return '$' in node


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
    count = 0
    for pattern in patterns:
        cache.clear()
        print("\tmain pattern: ", pattern)
        if patternCanBeMade(pattern, root_trie):
            count += 1
            print(pattern, "can be made")
        else:
            print(pattern, "cannot be made")

    print("Part 1:", count)


if __name__ == "__main__":
    main()
