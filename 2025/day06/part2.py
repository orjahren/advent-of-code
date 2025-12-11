import sys
from typing import List

filename = sys.argv[1]
with open(filename) as f:
    content = [x.strip("\n") for x in f.readlines()]
    print(content)

print(content)

opr_line = content[-1]
opr_list = [x for x in opr_line.split() if x]
content = content[:-1]
print("opr line:", opr_line)
print("content uten ops:", content)

matrix = [[] for _ in content]
print(matrix)

# for line_idx, line in enumerate(content):
for char_idx, char in enumerate(opr_line):
    print("opr char", char, "for idx", char_idx)
    if (not char.strip()):
        print("**continuer")
        continue

    next_opr_idx = char_idx+1
    try:
        while not opr_line[next_opr_idx].strip():
            next_opr_idx += 1
    except Exception:
        next_opr_idx = len(opr_line) + 1

    for line_idx, line in enumerate(content):
        line = content[line_idx]
        print("Line:")
        print(line)
        # for idx in range(char_idx, next_opr_idx):
        # for idx in range(0, len(line), WINDOW_SIZE):
        sub = line[char_idx:next_opr_idx]
        print("sub:", sub)
        matrix[line_idx].append(sub)
    old_char_idx = char_idx
print(matrix)

for row_idx, row in enumerate(matrix):
    # print("row", row_idx, row)

    for col_idx, col in enumerate(row):
        # print("\tcol", col_idx, col)
        pass


def get_nums(values: List[str]) -> List[int]:
    print("Finne nums fra values:", values)
    stax = [[] for _ in values]
    # for i in range(WINDOW_SIZE - 1):
    for i in range(len(values)):
        val = values[i]
        print(val)
        for j in range(len(values)):
            try:
                x = val[j]
            except Exception:
                x = ""
            stax[i].append(x)

    print("stax:")
    print(stax)

    comp = [[] for _ in stax]
    for i in range(len(stax)):
        for j in range(len(stax)):
            if i != j:
                # continue
                pass
            comp[i].append(stax[j][i])

    print("comp:")
    print(comp)

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
    print("values", col_idx, values)

    # opr = values[-1].strip()
    opr = opr_list[col_idx]
    # values = values[:-1]
    # print("values uten op ", col_idx, values)

    print("op:", opr)

    nums = get_nums(values)

    if opr == "+":
        p2 += sum(nums)
    elif opr == "*":
        prod = 1
        for num in nums:
            prod *= num
        p2 += prod
    else:
        print("Ukjent op woah hvordan kunne dette skje :o")
        exit(1)

print("p2:", p2)
