#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("Hello world \n");
    // const char *filename = "small";
    const char *filename = "../input";
    FILE *fp = NULL;
    printf("Dette er filename:");
    printf(filename);
    printf("\n");

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Feil med lesing av fil :(");
        perror(filename);
        exit(EXIT_FAILURE);
    }

    int sum = 0;
    char line[50];

    int elfIndex = 0;
    const int n = 10000;
    int elves[n];

    memset(elves, 0, sizeof(int) * n);

    while (fgets(line, 50, fp))
    {

        printf("Leste dette: %s \n", line);
        printf("elfIdx: %d \n", elfIndex);
        // if (strcmp(line, "") == 0)
        // if (line[0] == '\0')
        if (line[0] == '\n')
        {
            printf("%s er en tom streng \n", line);
            elfIndex++;
        }
        else
        {
            printf("%s er IKKE en tom streng \n", line);
            elves[elfIndex] += atoi(line);
            printf("parset: %d \n", atoi(line));
        }
    }

    for (int i = 0; i < elfIndex + 1; i++)
    {
        for (int j = 0; j < elfIndex; j++)

        {
            printf("i: %d j: %d", i, j);
            if (elves[j] < elves[j + 1])
            {
                int tmp = elves[j];
                printf("tmp: %d", tmp);
                elves[j] = elves[j + 1];
                elves[j + 1] = tmp;
            }
        }
    }

    printf("Alle values i sortert array: \n");
    for (int i = 0; i <= elfIndex; i++)
    {
        printf("%d, ", elves[i]);
    }

    printf("\n");

    printf("Part 1: %d\n", elves[0]);

    int res = 0;
    for (int i = 0; i <= 2; i++)
    {
        res += elves[i];
    }

    printf("Part 2: %d \n", res);
};