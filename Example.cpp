/**
 * This is a simple example program of Eval.h
 */
#include "Eval.h"
#include <string.h>
int main()
{
    Eval eval;
    while (true)
    {
        char cmd[10] = {0};
        scanf("%s", cmd);
        if (strcmp(cmd, "make") == 0)
        {
            char VariableName[100] = {0};
            double value;
            scanf("%s %lf", VariableName, &value);
            eval.AddVariable(VariableName, value);
            printf("Made Variable %s as %g\n", VariableName, value);
        }
        else if (strcmp(cmd, "set") == 0)
        {
            char VariableName[100] = {0};
            double value;
            scanf("%s %lf", VariableName, &value);
            eval[VariableName] = value;
            printf("Setted Variable %s as %g\n", VariableName, value);
        }
        else if (strcmp(cmd, "exit") == 0)
        {
            break;
        }
        else if (strcmp(cmd, "calculate") == 0)
        {
            char Expression[100] = {0};
            scanf("%s", Expression);
            printf("Answer: %g\n", eval(Expression));
        }
        else
        {
            printf("%s is not a valid command. Please try again.\n", cmd);
        }
    }
    return 0;
}