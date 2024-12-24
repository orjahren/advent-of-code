lines = [x.strip() for x in open(0).readlines()]

spl_idx = lines.index("")

initial = lines[:spl_idx]
commands = lines[spl_idx+1:]

print(lines)

print(initial)
print(commands)

values = {}
for x in initial:
    key, val = x.split(": ")
    values[key] = int(val)
    print(key, val)


todo = commands.copy()

next_iteration = []

while todo:
    print("todo len", len(todo))
    next_iteration = []
    for command in todo:
        arg1, op, arg2, _, target = command.split(" ")
        # print(arg1, op, arg2, target)

        try:
            x, y = values[arg1], values[arg2]
        except KeyError:
            next_iteration.append(command)
            continue

        match(op):
            case "OR":
                values[target] = x | y
            case "AND":
                values[target] = x & y
            case "XOR":
                values[target] = x ^ y
    todo = next_iteration.copy()
    # print(values)

usable_values = {k: v for k, v in values.items() if k[0] == "z"}
print(usable_values)
sorted_values = sorted(usable_values.items(), key=lambda x: x[0], reverse=True)
print(sorted_values)

p1 = int("".join([str(x[1]) for x in sorted_values]), 2)
print(p1)
