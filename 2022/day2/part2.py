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

    lines = [x.strip() for x in open(filename, "r").readlines()]
    pairs = []
    for l in lines:
        s = l.split()
        x, y = s[0], s[1]
        pairs.append((x, y))

    a_score = 0
    b_score = 0

    for a_op, b_op in pairs:
        # map to universal names
        a_formatted = op_to_name(a_op)
        print("formatted ops:", a_formatted, b_op)
        # static scores

        # Player skal tape
        if b_op == "X":
            a_score += result_scores["win"]
            b_score += result_scores["loss"]
            a_score += shape_scores[a_formatted]
            s = rules[a_formatted]
            print(s)
            print(s.keys())
            selected_b = list(s.keys())[0]
            print("selected b:", selected_b)
            b_score += shape_scores[selected_b]

        # player skal vinne
        elif b_op == "Z":
            a_score += result_scores["loss"]
            b_score += result_scores["win"]
            a_score += shape_scores[a_formatted]
            selected_b = None
            bad_choice = list(rules[a_formatted].items())[0][0]
            for k, v in rules.items():
                print("k v")
                print(k, v)
                if k != bad_choice and k != a_formatted:
                    print("k er ikke ", k, bad_choice)
                    selected_b = k  # list(v.keys())[0]
                    break

            """
            for k, v in rules.items():
                print("k v")
                print(k, v)
                if k == a_formatted:
                    for p, q in rules.items():
                        print("p q")
                        print(p, q)
                        if list(q.keys())[0] != list(v.keys())[0]:
                            print("CHOOSER")
                            selected_b = p  # list(q.keys())[0]

                            # selected_b = list(q.keys())[0]
                            break
            """
            print("selected b:", selected_b)
            b_score += shape_scores[selected_b]
        # draw
        elif b_op == "Y":
            print("draw")
            a_score += result_scores["draw"]
            b_score += result_scores["draw"]
            a_score += shape_scores[a_formatted]
            b_score += shape_scores[a_formatted]
        # print(pairs)

    print("Part 2:", b_score)


if __name__ == "__main__":
    for fn in ["input", "small"]:
        print("\n*****", fn, "******")
        main(fn)
