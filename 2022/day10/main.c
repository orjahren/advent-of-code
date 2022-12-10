#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp = NULL;
    // const char filename[] = "small";
    // const char filename[] = "medium";
    const char filename[] = "input";
    printf("Skal åpne filen %s \n", filename);

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Feil med åpning av fil \n");
        return 1;
    }

    char line[10];
    int res = 0;
    int currentCycle = 1;
    int reg = 1;
    int pendingOperation1 = __INT_MAX__;
    int pendingOperation2 = __INT_MAX__;
    int nopFlag = 0;
    int done = 0;
    int horIdx = 0;
    while (done == 0)
    {
        // printf("************* Starter cycle %d, reg er %d \n", currentCycle, reg);
        if (currentCycle == 20 || currentCycle == 60 || currentCycle == 100 || currentCycle == 140 || currentCycle == 180 || currentCycle == 220)
        {
            // printf("Current cycle er %d og reg_value er %d (som sammen utgjør %d) \n", currentCycle, reg, currentCycle * reg);
            res += currentCycle * reg;
        }
        //  TEGN HER
        // printf("SKal tegne reg %d", reg);
        if (reg - 1 <= horIdx && reg + 1 >= horIdx)
        {

            printf("#");
            // printf("#%d", currentCycle);
        }
        else
        {

            printf(".");
            // printf(".%d", currentCycle);
        }

        horIdx++;
        if (horIdx == 40)
        {
            printf("  NEWLINE. cuycCount: %d  ", currentCycle);
            printf("\n");
            horIdx = 0;
        }
        // Tegn slutt

        // printf("Flytter 2 til 1 \n");
        pendingOperation1 = pendingOperation2;
        // printf("Pend op 1 er %d \n", pendingOperation1);

        if (pendingOperation1 != __INT_MAX__)
        {
            // printf("Skal inkrementere reg med %d \n", pendingOperation1);
            reg += pendingOperation1;
        }
        else
        {
            // printf("LESER \n");
            fgets(line, 10, fp);
            // printf("Lests: %s", line);
        }
        pendingOperation2 = __INT_MAX__;

        if (line[0] == 'a')
        {
            int val;
            char devNull[10];
            sscanf(line, "%s %d", &devNull, &val);
            // printf("Setter pend op 2 til: %d \n", val);
            pendingOperation2 = val;
        }
        else if (line[0] == 'n')
        {
            nopFlag++;
        }

        if (!((nopFlag > 0) || (pendingOperation1 != __INT_MAX__) || (pendingOperation2 != __INT_MAX__)))
        {
            // printf("Avslutter. \n");
            done = 1; // Kan fjernes pga break
            break;
        }
        nopFlag = 0;
        // printf("---------------- Avslutter cycle %d, reg er %d \n \n", currentCycle, reg);
        currentCycle++;
        memset(line, 0, sizeof(char) * 10);
    }
    printf("//////////// \n");
    printf("Final reg_value er %d\n", reg);
    printf("Part 1: %d \n", res);
    printf("Final cycle_value er %d\n", currentCycle);

    printf("Part 2: Se over... \n");
    return 0;
}