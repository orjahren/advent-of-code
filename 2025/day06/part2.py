import sys
from typing import List

filename = sys.argv[1]
with open(filename) as f:
    content = [x.strip("\n") for x in f.readlines()]

opr_line = content[-1]
opr_list = [x for x in opr_line.split() if x]
content = content[:-1]

matrix = [[] for _ in content]

for char_idx, char in enumerate(opr_line):
    if (not char.strip()):
        continue

    next_opr_idx = char_idx+1
    try:
        while not opr_line[next_opr_idx].strip():
            next_opr_idx += 1
    except Exception:
        next_opr_idx = len(opr_line) + 1

    for line_idx, line in enumerate(content):
        line = content[line_idx]
        sub = line[char_idx:next_opr_idx]
        matrix[line_idx].append(sub)
    old_char_idx = char_idx


def get_nums(values: List[str]) -> List[int]:
    stax = [[] for _ in values]
    for i in range(len(values)):
        val = values[i]
        for j in range(len(values)):
            try:
                x = val[j]
            except Exception:
                x = ""
            stax[i].append(x)

    comp = [[] for _ in stax]
    for i in range(len(stax)):
        for j in range(len(stax)):
            if i != j:
                pass
            comp[i].append(stax[j][i])

    stripped = []
    for l in comp:
        p = []
        for x in l:
            y = x.strip()
            if y:
                p.append(y)
        if len(p) > 0:
            stripped.append(p)
    parsed = [int("".join(x)) for x in stripped if x]

    return parsed


p2 = 0
for col_idx, _ in enumerate(matrix[0]):
    values = [row[col_idx] for row in matrix]
    opr = opr_list[col_idx]
    nums = get_nums(values)

    if opr == "+":
        p2 += sum(nums)
    elif opr == "*":
        prod = 1
        for num in nums:
            prod *= num
        p2 += prod

print("p2:", p2)
