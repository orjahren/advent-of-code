# with open("example2", "r") as f:
with open("input", "r") as f:
    lines = [l.strip() for l in f.readlines()]
nums = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]


def is_num(s):
    return s.isdigit() or s in nums


res = 0
for line in lines:
    found = False
    first_num = None
    for i in range(len(line)):
        if found:
            break
        if is_num(line[i]):
            first_num = line[i]
            found = True
            break
        for num in nums:
            candidate = line[i : i + len(num)]
            if is_num(candidate):
                first_num = str(nums.index(candidate) + 1)
                found = True
                break

    found = False
    last_num = None
    for i in range(len(line) - 1, -1, -1):
        if found:
            break
        if is_num(line[i]):
            last_num = line[i]
            found = True
            break
        for num in nums:
            candidate = line[i - len(num) + 1 : i + 1]
            if is_num(candidate):
                last_num = str(nums.index(candidate) + 1)
                found = True
                break

    res += int(first_num + last_num)
print(res)
