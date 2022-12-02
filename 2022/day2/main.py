lines = [x.strip() for x in open("input", "r").readlines()]
# lines = [x.strip() for x in open("small", "r").readlines()]
pairs = []
for l in lines:
    s = l.split()
    x, y = s[0], s[1]
    pairs.append((x, y))
print(lines)
# print(pairs)


def would_win(foo, bar):
    if foo == bar:
        return False
    if foo == "rock" and bar == "scissors":
        return True
    elif foo == "scissors" and bar == "paper":
        return True
    elif foo == "paper" and bar == "rock":
        return True
    return False
    rules = {"rock": {"scissors": True}, "scissors": {"paper": True}, "paper": {"rock"}}
    print(rules)
    return rules.get(foo, False).get(bar, False)


def op_to_name(op):
    if op == "A" or op == "X":
        return "rock"
    elif op == "B" or op == "Y":
        return "paper"
    elif op == "C" or op == "Z":
        return "scissors"


shape_scores = {"rock": 1, "paper": 2, "scissors": 3}
result_scores = {"loss": 0, "draw": 3, "win": 6}

a_score = 0
b_score = 0

for a_op, b_op in pairs:
    # map to universal names
    a_formatted = op_to_name(a_op)
    b_formatted = op_to_name(b_op)
    print("formatted ops:", a_formatted, b_formatted)
    # static scores
    a_score += shape_scores[a_formatted]
    b_score += shape_scores[b_formatted]
    # draw
    if a_formatted == b_formatted:
        print("draw")
        a_score += result_scores["draw"]
        b_score += result_scores["draw"]
        continue

    if would_win(a_formatted, b_formatted):
        a_score += result_scores["win"]
        b_score += result_scores["loss"]

    elif would_win(b_formatted, a_formatted):
        b_score += result_scores["win"]
        a_score += result_scores["loss"]

print("Part 1:", b_score)
