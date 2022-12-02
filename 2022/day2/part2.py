def op_to_name(op):
    if op == "A" or op == "X":
        return "rock"
    elif op == "B" or op == "Y":
        return "paper"
    elif op == "C" or op == "Z":
        return "scissors"


shape_scores = {"rock": 1, "paper": 2, "scissors": 3}
result_scores = {"loss": 0, "draw": 3, "win": 6}

rules = {"rock": {"scissors": True}, "scissors": {"paper": True}, "paper": {"rock": True}}


def main(filename):

    pairs = [(s[0], s[1]) for s in [x.strip().split() for x in open(filename, "r").readlines()]]
    b_score = 0

    for a_op, b_op in pairs:
        # map to universal names
        a_formatted = op_to_name(a_op)
        # static scores

        # Player skal tape
        if b_op == "X":
            b_score += result_scores["loss"]
            selected_b = list(rules[a_formatted].keys())[0]
            b_score += shape_scores[selected_b]

        # player skal vinne
        elif b_op == "Z":
            b_score += result_scores["win"]
            selected_b = None
            bad_choice = list(rules[a_formatted].items())[0][0]
            for k, v in rules.items():
                if k != bad_choice and k != a_formatted:
                    selected_b = k
                    break
            b_score += shape_scores[selected_b]

        # draw
        elif b_op == "Y":
            b_score += result_scores["draw"]
            b_score += shape_scores[a_formatted]

    print("Part 2:", b_score)


if __name__ == "__main__":
    for fn in ["input", "small"]:
        print("\n*****", fn, "******")
        main(fn)
