from collections import defaultdict


def get_path(path):
    return "/" + "/".join(path[1:])


files = []
ll = []
with open("small", "r") as f:
    ll = [x.strip() for x in f.readlines()]
# print(ll)

dd = defaultdict(lambda: 0)

fs = {}

path = []
for l in ll:

    # print("Leste dette:", l)
    # print("Current path er:", get_path(path))

    spl = l.split()
    if spl[0] == "$":
        cmd = spl[1]
        if cmd == "cd":
            if spl[2] != "..":
                path.append(spl[2])
            else:
                path.pop()
        pass
    else:

        if spl[0] == "dir":
            # print("Skal fikse fs for", path, ", som oversettes til", get_path(path))
            print("Skal legge", spl[1], "inn i fs under mappe", get_path(path), ". Path er:", path)
            # for p in get_path(lie)

            prev = fs
            for p in path:
                print("Sjekker ut", p)
                parent = prev.get(p, None)
                if parent is None:
                    print(p, "finnes ikke")
                    print("i prev:", prev)
                    prev[p] = {}
                    prev[p][spl[1]] = {}
                else:
                    print(p, "finnes")
                    prev = prev[p]
                    if p == path[-1]:
                        print(p, "er", path[-1])
                        print("prevv er:", prev)
                        prev[spl[1]] = {}

        else:
            # ls
            print("Skal lager størrelsen av", spl[1], "til", path)
            print("Den str er", spl[0])
            parsedNumber = int(spl[0])
            # dd[get_path(path)] += parsedNumber
            d = fs["/"]
            for p in path[1:]:
                d = d[p]
            print("d er:", d)
            if not d.get("files", False):
                print(d, "er ikke ei liste")
                d["files"] = []

            d["files"].append({spl[1]: parsedNumber})
            # d[spl[1]] = parsedNumber  # <<<- save file name with file size at proper place
            # d[parsedNumber] = False  # <<<<- hack the world
            if not d.get("META"):
                d["META"] = 0

            d["META"] += parsedNumber


print("Ferdig fs:")
print(fs)


k = "/"
q = list(fs[k].keys())
prev = fs
# for k, v in fs.items():
while len(q) > 0:
    # print("Setter x til k av y", prev, k)
    x = prev[k]
    print("Sjekker ut:", x)
    # if type(x) == dict:
    if list(x.values())[0] != False:
        print("Legger dette i q:", x.keys())
        q.extend(x.keys())
    else:
        print(x, "er ikke en dict ;)")

    prev = x
    k = q.pop()

"""
res = 0
for k, v in fs.items():
    print("Sjekker:", k, v)
    if v < 100000:
        res += v
print("Part 1:", res)
"""
