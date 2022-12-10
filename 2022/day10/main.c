#include <stdio.h>
#include <string.h>

void doPart1(int *pCurrentCycle, int *pPart1Res, int *pReg)
{
    int currentCycle = *pCurrentCycle;
    if (currentCycle == 20 || currentCycle == 60 || currentCycle == 100 || currentCycle == 140 || currentCycle == 180 || currentCycle == 220)
    {
        *pPart1Res += *pCurrentCycle * *pReg;
    }
}

void drawCRT(int *pHorIdx, int *pReg)
{
    int horIdx = *pHorIdx;
    int reg = *pReg;
    if (reg - 1 <= horIdx && reg + 1 >= horIdx)
    {
        printf("#");
    }
    else
    {
        printf(".");
    }
    *pHorIdx = *pHorIdx + 1;
    if (*pHorIdx == 40)
    {
        printf("\n");
        *pHorIdx = 0;
    }
}

int main()
{
    FILE *fp = fopen("input", "r");
    char line[10];
    int part1Res = 0;
    int currentCycle = 0;
    int reg = 1;
    int pendingOperation1 = __INT_MAX__;
    int pendingOperation2 = __INT_MAX__;
    int horIdx = 0;
    int parsedReadValue;
    printf("Part 2:\n");
    while (1)
    {
        currentCycle++;
        doPart1(&currentCycle, &part1Res, &reg);
        drawCRT(&horIdx, &reg);

        pendingOperation1 = pendingOperation2;
        pendingOperation2 = __INT_MAX__;

        if (pendingOperation1 != __INT_MAX__)
        {
            reg += pendingOperation1;
        }
        else
        {
            fgets(line, 10, fp);
        }

        if (line[0] == 'a')
        {
            sscanf(line, "%*s %d", &parsedReadValue);
            pendingOperation2 = parsedReadValue;
        }
        else if (!((line[0] == 'n') || (pendingOperation1 != __INT_MAX__) || (pendingOperation2 != __INT_MAX__)))
        {
            break;
        }
        memset(line, 0, sizeof(char) * 10);
    }
    fclose(fp);
    printf("Part 1: %d \n", part1Res);
}