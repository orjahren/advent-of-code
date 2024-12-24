lines = [x.strip() for x in open(0).readlines()]

spl_idx = lines.index("")

initial = lines[:spl_idx]
commands = lines[spl_idx+1:]

print(lines)

print(initial)
print(commands)
