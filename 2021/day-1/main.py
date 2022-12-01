res = 0
prev = None
with open("input.txt", "r") as f:
    nums = [int(x) for x in f.readlines()]

for x in nums:
    if prev:
        if x > prev:
            res += 1
    prev = x
print("res:", res)