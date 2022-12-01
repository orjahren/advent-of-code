from typing import Any, Union
from collections import defaultdict
def sim(ls, nr):
    nl = list(str(nr))[::-1]
    dd = defaultdict(lambda: False)
    """
    minne:Union[str, int] = {
        "w": 0,
        "x": 0,
        "y": 0,
        "z": 0
    }
    """
    dd["w"] = 0
    dd["x"] = 0
    dd["y"] = 0
    dd["z"] = 0

    for l in ls:
    
        s = l.split()
        #print("s:", s)
    
        cmd = s[0]
        a = s[1]
    
        if cmd == "inp":
            dd[a] =  int(nl.pop())
            
        elif cmd == "add":
            b = s[2]
            #print("b:", b)
            #print("dd[b]:", dd[b])
            if dd[b] is False:
                dd[a] = dd[a] + int(b)
            else:
                #print("dd[b]:", dd[b])
                #print("dd[a]:", dd[a])
                dd[a] = dd[a] + dd[b]

            
        elif cmd == "mul":
            b = s[2]

            if dd[b] is False:
                dd[a] = dd[a] * int(b)
            else:
                dd[a] = dd[a] * dd[b]
                
            
        elif cmd == "div":
            b = s[2]

            if dd[b] is False:
                dd[a] = dd[a] // int(b)
            else:
                dd[a] = dd[a] // dd[b]
            
        elif cmd == "mod":
            b = s[2]

            if dd[b] is False:
                dd[a] = dd[a] % int(b)
            else:
                dd[a] = dd[a] % dd[b]
            
        elif cmd == "eql":
            b = s[2]

            if dd[b] is False:
                dd[a] = 1 if dd[a] == int(b) else 0
            else:
                dd[a] = 1 if dd[a] == dd[b] else 0
            
    return dd["z"]

def is_valid(ls, n):
    return sim(ls, n) == 1

dat = []
with open("input.txt") as f:
    for line in f:
        dat.append(line.strip())

print(dat)

n = int("1" * 14)
#n = 10000000000000
print("n:", n)
print("Begynner å simulere")
while not is_valid(dat, n):
    try:
        #print(n)
        n += 1
    except KeyboardInterrupt:
        print(n)
        break
print("Res:", n)

