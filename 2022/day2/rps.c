#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DRAW_SCORE 3
#define LOSS_SCORE 0
#define WIN_SCORE 6

int main()
{
    printf("AoC 2022 dag 2 C \n");

    // const char filename[] = "small";
    const char filename[] = "input";
    FILE *fp = NULL;
    printf("Dette er filename: %s \n", filename);

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Feil med lesing av fil :(");
        exit(EXIT_FAILURE);
    }

    int score = 0;
    char line[50];

    while (fgets(line, 50, fp))
    {
        char a = line[0];
        char b = line[2];
        // printf("Leste dette: %c %c \n", a, b);

        if (b == 'X')
        { // rock
            score += 1;
            if (a == 'A')
            {
                score += DRAW_SCORE;
            }
            else if (a == 'B')
            {
                score += LOSS_SCORE; // will be 0, pointless :shrug:
            }
            else
            { // else must be c aka saks
                score += WIN_SCORE;
            }
        }
        else if (b == 'Y')
        { // paper
            score += 2;
            if (a == 'A')
            {
                score += WIN_SCORE;
            }
            else if (a == 'B')
            {
                score += DRAW_SCORE;
            }
            else
            { // else must be c aka saks
                score += LOSS_SCORE;
            }
        }
        else if (b == 'Z')
        { // saks
            score += 3;
            if (a == 'A')
            {
                score += LOSS_SCORE;
            }
            else if (a == 'B')
            {
                score += WIN_SCORE;
            }
            else
            { // else must be c aka saks
                score += DRAW_SCORE;
            }
        }
    }

    printf("Part 1: %d\n", score);

    // printf("Part 2: %d \n", res);
    return 0;
};