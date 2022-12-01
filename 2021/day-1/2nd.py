res = 0
prev = None
with open("input.txt", "r") as f:
    nums = [int(x) for x in f.readlines()]

for i in range(0, len(nums) - 2, 1):
    x = sum([nums[i], nums[i + 1], nums[i + 2]])
    if prev:
        if x > prev:
            res += 1
    prev = x

print("res:", res)