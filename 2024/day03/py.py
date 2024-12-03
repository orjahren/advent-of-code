import re

s = open(0).read()
print(s)


def eval_hit(hit: str) -> int:
    print("HIT:", hit)
    l, r = hit.split(",")
    l = int(l[4:])
    r = int(r[:-1])
    print(l, r)
    return r * l


ex = r"mul\(\d{1,3},\d{1,3}\)"
hits = re.findall(ex, s)


res = sum(eval_hit(hit) for hit in hits)

print(res)
