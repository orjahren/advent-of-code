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
    seen = set()
    for node, edges in graph.items():
        if node in seen:
            continue
        seen.add(node)
        print(node, edges)
        edge_set = set(edges)
        for x in edges:

            if x in seen:
                continue
            seen.add(x)
            neighbor_edges = graph[x]
            neighbor_edge_set = set(neighbor_edges)

            for y in neighbor_edges:
                if y not in seen:
                    continue
                seen.add(y)

                if y in edge_set:
                    res += 1

    return res


def main():
    adjecency_list = [x.split("-") for x in open(0).read().splitlines() if x]
    print(adjecency_list)

    print("Part 1:", p1(adjecency_list))
    # 2490 too high


if __name__ == "__main__":
    main()
