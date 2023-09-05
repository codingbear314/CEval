/**
 * This is a simple example program of EvalString.h
 */
#include "EvalString.h"
#include <cmath>
#include <string.h>

using namespace expreval;
using namespace std;

// Example functions
double powerE(vector<DataType> lt)
{
    return pow(std::get<double>(lt[0]), std::get<double>(lt[1]));
}
double sqrtE(vector<DataType> lt) { return sqrt(std::get<double>(lt[0])); }

int main()
{
    Eval eval;
    eval.AddFunction("pow", powerE, 2);
    eval.AddFunction("sqrt", sqrtE, 1);

    while (true)
    {
        // I'm so sorry that I didn't implemented the example for adding
        // variables. But it is so hard to do, since I have to know what is the
        // type of the input. I will add it someday,
        // if I find how to do it somehow
        char cmd[10] = {0};
        scanf("%s", cmd);
        printf("Answer: ");
        print(eval(cmd));
        printf("\n");
    }
    return 0;
}