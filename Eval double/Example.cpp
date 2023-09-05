/**
 * This is a simple example program of Eval.h
 */
#include "Eval.h"
#include <cmath>
#include <string.h>

using namespace std;

// Example functions
double powerE(vector<double> lt) { return pow(lt[0], lt[1]); }
double sqrtE(vector<double> lt) { return sqrt(lt[0]); }

int main()
{
    Eval eval;
    eval.AddFunction("pow", powerE, 2);
    eval.AddFunction("sqrt", sqrtE, 1);

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
        else
        {
            printf("Answer: %g\n", eval(cmd));
        }
    }
    return 0;
}