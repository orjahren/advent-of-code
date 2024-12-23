# adjecency list is of the format [node node], where node is a string and there is an undirected edge between the two nodes
def p1(graph):
    used_sets = set()
    results = []
    for node, edges in graph.items():
        for x in edges:
            for y in graph[x]:
                if y in edges:
                    s = "".join(sorted([node, x, y]))
                    if "t" in [v[0] for v in [node, x, y]]:
                        if s not in used_sets:
                            results.append((sorted([node, x, y])))
                        used_sets.add(s)
    return len(results)


def p2(graph):
    pass


def main():
    adjecency_list = [x.split("-") for x in open(0).read().splitlines() if x]
    print(adjecency_list)

    graph = {}
    for a, b in adjecency_list:
        if a not in graph:
            graph[a] = []
        if b not in graph:
            graph[b] = []
        graph[a].append(b)
        graph[b].append(a)
    print(graph)

    part1 = p1(graph)
    print("Part 1:", part1)

    part2 = p2(graph)
    print("Part 2:", part2)


if __name__ == "__main__":
    main()
