#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int allValuesUnique(int **arr[])
{
    for (int i = 0; i < arr.length; i++)
    {
        return 0;
    }
    return 1;
}

int main()
{
    printf("Salut le monde :) \n");

    const char fileName[] = "small";
    FILE *fp = NULL;

    if ((fp = fopen(fileName, "r")) == NULL)
    {
        printf("Feil med lesing av fil :( \n");
        exit(EXIT_FAILURE);
    }

    printf("Fikk åpnet filen helt fint... \n");

    char line[50];
    fgets(line, 50, fp);
    printf("Linjen er: %s \n", line);

    int seen[26];
    memset(seen, 0, sizeof(int) * 26);

    char forrige[4];
    for (int i = 0; i < 4; i++)
    {
        forrige[i] = line[i];
    }

    for (int i = 3; i < strlen(line); i++)
    {

        for (int j = 3; j > 0; j--)
        {
            char cmp = forrige[i + j];
            printf("%c har charcode %d \n   ", cmp, (int)cmp - 0);
            seen[cmp]++;
        }
        memset(seen, 0, sizeof(int) * 26);
        char c = line[i];
        printf("Skal deale med denne charen: %c \n", c);
    }
}