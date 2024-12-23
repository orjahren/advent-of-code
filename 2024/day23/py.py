def p1(graph):
    used_sets = set()
    results = []
    for node, edges in graph.items():
        for x in edges:
            for y in graph[x]:
                if y in edges:
                    s = "".join(sorted([node, x, y]))
                    if "t" in [v[0] for v in [node, x, y]] and s not in used_sets:
                        results.append((sorted([node, x, y])))
                        used_sets.add(s)
    return len(results)


def p2(graph):
    res = set()

    def rec(node, required):
        if (k := tuple(sorted(required))) in res:
            return
        res.add(k)
        for x in graph[node]:
            if x in required or not all(y in graph[x] for y in required):
                continue
            rec(x, required | {x})
    for node in graph:
        rec(node,  {node})
    return ",".join(sorted(max(res, key=len)))


graph = {}
for a, b in [x.split("-") for x in open(0).read().splitlines() if x]:
    if a not in graph:
        graph[a] = []
    if b not in graph:
        graph[b] = []
    graph[a].append(b)
    graph[b].append(a)

print("Part 1:", p1(graph))
print("Part 2:", p2(graph))
