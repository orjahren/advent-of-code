# adjecency list is of the format [node node], where node is a string and there is an undirected edge between the two nodes


def p1(adjecency_list):
    graph = {}
    for a, b in adjecency_list:
        if a not in graph:
            graph[a] = []
        if b not in graph:
            graph[b] = []
        graph[a].append(b)
        graph[b].append(a)
    print(graph)

    res = 0
    used_sets = set()
    results = []
    for node, edges in graph.items():
        print(node, edges)
        for x in edges:
            for y in graph[x]:
                if y in edges:
                    s = "".join(sorted([node, x, y]))
                    print("Vurderer", node, x, y, s)
                    if "t" in [v[0] for v in [node, x, y]]:
                        if s not in used_sets:
                            print("found", node, x, y)
                            res += 1
                            results.append((sorted([node, x, y])))
                        used_sets.add(s)

    print(used_sets)
    print(results)
    for x in sorted(results):
        print(x)
    return res


def main():
    adjecency_list = [x.split("-") for x in open(0).read().splitlines() if x]
    print(adjecency_list)

    print("Part 1:", p1(adjecency_list))
    # 2490 too high
    # 2298 too high


if __name__ == "__main__":
    main()
