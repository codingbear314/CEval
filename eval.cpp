/**
 * Eval.h & Eval.cpp
 * 
 * Continued project from CEval.h v 3.0
 * The goal is to make the code as simple as possible, since the last version was over-complicated
 * 
 * This library would NOT support string maniplications; use the CEval.h v3.0 to do string maniplications
 * 
 * Code written by Jaewook Jung, 2023
 * 
 * visit by blog! bit.ly/codingbear314
 * 
 * @version 1.0
 * @author Jaewook Jung
 * @date 2023/08/14
*/

#include "Eval.h"

//constructers

/**
 * @brief constructer that reset everything.
*/
Eval::Eval (void)    {} 

/**
 * @brief A constructer that copies the variable list.
 * @param variables the list of variables in a map
*/
Eval::Eval (map<string, double> variables) : 
Variables (variables)   {}

/**
 * @brief Add a variable to the object.
 * @param name A name of the variable
 * @param value The value of the variable
 * @return void
*/
void Eval::AddVariable (string name, double value)
{
    this -> Variables.emplace(name, value);
    return;
}

/**
 * @brief A function that returns the whole variable list.
 * @return The whole list of variables
*/
const map<string, double>& Eval::GetVariableList (void)
{
    return this -> Variables;
}

/**
 * @brief Access the variable with the name.
 * @param VariableName The name of the variable
 * @return A reference of the variable so you could modify it
*/
double& Eval::operator[] (string VariableName)
{
    return this -> Variables[VariableName];
}

/**
 * @brief Runs the evaluation with the string Expression
 * @details This operator runs by just running the Eval::Evaluate internally.
 * So for more details, look at the Eval::Evaluate function.
 * @param Expression A string that would be evaluated
 * @return The result of the evaluation
*/
double Eval::operator() (string Expression)
{
    return this -> Evaluate(Expression);
}

/**
 * @brief Runs the evaluation with the string Expression
 * @details The code first split the expression by the operators.
 * It does this by iterating the expression character by character
 * Then, It calculates * or / from the front, and store the result in a deque.
 * Then, the code will iterate through the deque and add/subtract the numbers and store them back at the front of the deque, untill there is only one left.
 * Finally the code will return the left number.
 * @param Expression A string that would be evaluated
 * @return The result of the evaluation
*/
double Eval::Evaluate (string Expression)
{
    deque<double>   operands;
    deque<char>     operators;
    string now = "";
    char type = 'N'; //N:Number V:Variable B:Brackets
    int openedbrackets = 0;
    for (int i = 0;i < Expression.length();i++)
    {
        char chnow = Expression[i];

        if (chnow == ' ')  //So the code could handle 1 + 1
        continue;

        if (openedbrackets == 0)
        switch (chnow)
        {
            // switch without break is used just to know if chnow is an operator
            case '+':
            case '-':
            case '*':
            case '/':
                //if chnow is an operator
                switch (type)
                {
                    case 'N':
                        operands.push_back(std::stod(now));
                        break;
                    case 'V':
                        operands.push_back(this -> Variables[now]);
                        break;
                    case 'B':
                        //There is a bracket, so it re-call itself to compute inside the bracket.
                        operands.push_back(this -> Evaluate( now.substr(1, now.length() - 2) ));
                        break;
                }
                operators.push_back(chnow);

                now = "";
                type = 'N';
                continue;
        }

        now.push_back(chnow);
        
        if ( ( ('A' <= chnow && chnow <= 'Z') || ('a' <= chnow && chnow <= 'z') ) && type != 'B' )
            type='N';
        else if ( chnow == '(' || chnow == ')' )
            type='B'; 
        if (chnow == '(')
            openedbrackets++;
        else if (chnow == ')')
            openedbrackets--;
    }
    switch (type)
    {
        case 'N':
            operands.push_back(std::stod(now));
            break;
        case 'V':
            operands.push_back(this -> Variables[now]);
            break;
        case 'B':
            operands.push_back(this -> Evaluate( now.substr(1, now.length() - 2) ));
            break;
    }

    //Now calculate the * and /
    char lastoperator = operators.front();
    deque<double>   operands2;
    deque<char>     operators2;
    operands2.push_back(operands.front());
    if (lastoperator == '+' || lastoperator == '-')
    operators2.push_back(lastoperator);
    for (int i = 1;i < operands.size();i++)
    {
        double n = operands[i];
        switch (lastoperator)
        {
        case '+':
        case '-':
            operands2.push_back(n);
            break;
        case '*':
            operands2.back() *= n;
            break;
        case '/':
            operands2.back() /= n;
            break;
        }

        if (i == operands.size()-1)
        break;

        char noper = operators[i];
        if(noper == '+' || noper == '-')
        operators2.push_back(noper);
        lastoperator = noper;
    }

    //Finally calculate + and -
    while(operands2.size() > 1)
    {
        double operand1 = operands2.front();
        operands2.pop_front();
        double operand2 = operands2.front();
        operands2.pop_front();
        char operator1  = operators2.front();
        operators2.pop_front();
        operands2.push_front(operator1 == '+' ? operand1+operand2 : operand1-operand2);
    }

    return operands2[0];
}