with open("example2", "r") as f:
    lines = [l.strip() for l in f.readlines()]
nums = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]


def is_num(s):
    return s.isdigit() or s in nums


res = 0
for line in lines:
    found = False
    print(line)
    first_num = None
    for i in range(len(line)):
        if found:
            break
        if is_num(line[i]):
            print("\t FANT SINGLE CHAR")
            first_num = int(line[i])
            found = True
            break
        for num in nums:
            candidate = line[i : i + len(num)]
            if is_num(candidate):
                print("\t\t FANT TOKEN", candidate)
                first_num = nums.index(candidate) + 1
                found = True
                break

    print("First is:", first_num)

    found = False
    last_num = None
    for i in range(len(line) - 1, -1, -1):
        if found:
            break
        if is_num(line[i]):
            last_num = int(line[i])
            found = True
            break
        for num in nums:
            candidate = line[i - len(num) + 1 : i + 1]
            if is_num(candidate):
                last_num = nums.index(candidate) + 1
                found = True
                break
    print("Last is:", last_num)

    s = str(first_num) + str(last_num)
    print(s)
    res += int(s)


print(lines)
print(res)
