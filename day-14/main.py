from collections import defaultdict
from collections import Counter
from itertools import pairwise

ls = []
s = None
dd = defaultdict(lambda x: False)
cnt = defaultdict(int)
with open("input.txt", "r") as f:
    s = f.readline().rstrip()
    f.readline()
    ls = [x.strip() for x in f.readlines()]
    ls = [tuple(x.split(" -> ", maxsplit=1)) for x in ls]
    for a, b in ls:
        dd[a] = b

res = []
co = 10
bis = defaultdict(int)

for c in s:
    cnt[c] += 1

for a, b in pairwise(s):    
    bis[a + b] += 1

for _ in range(10):
    l = []
    for k, v in ls:
        if bis[k] != 0:
            l.append((k, v, bis[k]))
            del bis[k]
    
    for k, v, c in l:
        cnt[v] += c
        bis[k[0] + v] += c
        bis[v + k[1]] += c
ll = Counter(cnt).most_common()
print("res:", ll[0][1] - ll[-1][1])