from typing import List


# with open("example") as f:
with open("input") as f:
    content = [x.strip("\n") for x in f.readlines()]
    print(content)

print(content)

matrix = [[] for _ in content]
print(matrix)

WINDOW_SIZE = 4
for line_idx, line in enumerate(content):
    print("Line:")
    print(line)
    for idx in range(0, len(line), WINDOW_SIZE):
        sub = line[idx:idx+WINDOW_SIZE]
        print(sub)
        matrix[line_idx].append(sub)
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
            stax[i].append(val[j])

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

    try:

        parsed = [int("".join(x)) for x in comp if x]
    except Exception:
        return [0]

    return parsed


p2 = 0

for col_idx, _ in enumerate(matrix[0]):
    values = [row[col_idx] for row in matrix]
    print("values", col_idx, values)

    opr = values[-1].strip()
    values = values[:-1]
    print("values uten op ", col_idx, values)

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
