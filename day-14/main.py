from collections import defaultdict
ls = []
s = None
dd = defaultdict(lambda x: False)
with open("input.txt", "r") as f:
    s = f.readline().strip()
    f.readline()
    ls = [x.strip() for x in f.readlines()]
    ls = [tuple(x.split(" -> ")) for x in ls]
    for a, b in ls:
        dd[a] = b

print(ls)
print("s:", s)
print(dd)

ny = list(s)

for i, c in enumerate(s):
    j = i + 1
    if j < len(s):
        a, b = s[i], s[j]
        if dd[a + b]:
            ny.insert(i, dd[a + b])
print("".join(ny))