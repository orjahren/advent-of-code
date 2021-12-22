class Pawn:
    def __init__(self, start, name) -> None:
        self.score = 0
        self.pos = start
        self.name = name
    
    def __str__(self) -> str:
        return self.name
    
    def move(self, n_pos):
        for _ in range(n_pos):
            if self.pos >= 10:
                self.pos = 0
            self.pos += 1
        self.score += self.pos
    
class Die:
    def __init__(self) -> None:
        self.val = 0   
        self.total_rolls = 0

    def roll(self):        
        self.total_rolls += 1
        if self.val >= 100:
            self.val = 0
        self.val += 1
        return self.val

"""
p1 = Pawn(6, "Player 1")
p2 = Pawn(1, "Player 2")
"""    
p1 = Pawn(4, "Player 1")
p2 = Pawn(8, "Player 2")
d = Die()
pls = [p1, p2]

while max([x.score for x in pls]) < 1000:
    for p in pls:
        n_moves = sum([d.roll() for _ in range(3)])
        p.move(n_moves)
        if p.score >= 1000:
            winner = p1 if p1.score > p2.score else p2
            print("winner:", winner)
            print("winner score:", winner.score)
            print("p:", p)
            print("\n\n")
                    
            loser = p1 if p1.score < p2.score else p2
            print("loser:", loser)
            print("loser.score:", loser.score)
            print("\n\n")

            print("d.total_rolls:", d.total_rolls)
            print("d.val:", d.val)
            print("res:", loser.score * d.total_rolls)
            exit()