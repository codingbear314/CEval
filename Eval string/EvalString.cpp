/**
 * EvalString.h & EvalString.cpp
 *
 * A simple way of evaluating functions
 * This library supports functions
 * This is a version that supports strings
 *
 * Code written by Jaewook Jung, 2023
 *
 * visit by blog! bit.ly/codingbear314
 *
 * @version 1.5
 * @author Jaewook Jung
 * @date 2023/09/04
 */

#include "EvalString.h"

namespace expreval
{
// constructers

/**
 * @brief constructer that reset everything.
 */
Eval::Eval(void) {}

/**
 * @brief A constructer that copies the variable list.
 * @param variables the list of variables in a map
 */
Eval::Eval(std::map<std::string, DataType> variables) : Variables(variables) {}

/**
 * @brief A constructer that copies the Function list.
 * @param functions the list of functions in a map
 */
Eval::Eval(
    std::map<
        std::string,
        std::pair<std::function<DataType(const std::vector<DataType> &)>, int>>
        functions)
    : Functions(functions)
{
}

/**
 * @brief A constructer that copies the Variable & Function list.
 * @param variables the list of variables in a map
 * @param functions the list of functions in a map
 */
Eval::Eval(
    std::map<std::string, DataType> variables,
    std::map<
        std::string,
        std::pair<std::function<DataType(const std::vector<DataType> &)>, int>>
        functions)
    : Variables(variables), Functions(functions)
{
}

/**
 * @brief A copy constructer
 * @param original Original object
 */
Eval::Eval(const Eval &original)
{
    this->Functions = original.Functions;
    this->Variables = original.Variables;
}

/**
 * @brief Add a variable to the object.
 * @param name A name of the variable
 * @param value The value of the variable
 * @return void
 */
void Eval::AddVariable(std::string name, DataType value)
{
    this->Variables.emplace(name, value);
    return;
}

/**
 * @brief Add a function to the object.
 * @param name A name of the function
 * @param function The function itself. must return DataType, and have only one
 * vector<DataType> as a input.
 * @param parameters The number of parameters. Set to -1 in default, which will
 * ignore checking the number of parameters.
 * @return void
 */
void Eval::AddFunction(
    std::string name,
    std::function<DataType(const std::vector<DataType> &)> function,
    int parameters = -1)
{
    this->Functions.emplace(name, make_pair(function, parameters));
    return;
}

/**
 * @brief A function that returns the whole variable list.
 * @return The whole list of variables
 */
const std::map<std::string, DataType> &Eval::GetVariableList(void) const
{
    return this->Variables;
}

/**
 * @brief Access the variable with the name.
 * @param VariableName The name of the variable
 * @return A reference of the variable so you could modify it
 */
DataType &Eval::operator[](std::string VariableName)
{
    return this->Variables[VariableName];
}

/**
 * @brief Runs the evaluation with the string Expression
 * @details This operator runs by just running the Eval::Evaluate internally.
 * So for more details, look at the Eval::Evaluate function.
 * @param Expression A string that would be evaluated
 * @return The result of the evaluation
 */
DataType Eval::operator()(std::string Expression) const
{
    return this->Evaluate(Expression);
}

/**
 * @brief Runs the evaluation with the string Expression
 * @details The code first split the expression by the operators.
 * It does this by iterating the expression character by character
 * Then, It calculates * or / from the front, and store the result in a deque.
 * Then, the code will iterate through the deque and add/subtract the numbers
 * and store them back at the front of the deque, untill there is only one left.
 * Finally the code will return the left number.
 *
 * Those steps are done by several helper functions;
 * Eval::Tokenize
 * Eval::CalculatePriority
 * Eval::CalculatePlusMinus
 *
 * So, if you want to look how the code works, look at those functions.
 *
 * @param Expression A string that would be evaluated
 * @return The result of the evaluation
 */
DataType Eval::Evaluate(std::string Expression) const
{
    std::deque<DataType> operands;
    std::deque<char> operators;

    this->Tokenize(Expression, operands, operators);

    // Now calculate the * and /
    std::deque<DataType> operands2;
    std::deque<char> operators2;

    this->CalculatePriority(operands, operators, operands2, operators2);

    // Finally calculate + and -
    return this->CalculatePlusMinus(operands2, operators2);
}

/**
 * @brief A helper function for Eval::Evaluate
 * @details The code will split the Expression by operators
 * If the Expression includes brackets, it will call Eval::Evaluate to calculate
 * inside the bracket. This function supports variables.
 *
 * @param Expression A string that would be evaluated
 * @param operands A reference to store tokenized operands
 * @param operators A reference to store tokenized operators
 * @return void; since all the values are stored by reference
 */
void Eval::Tokenize(const std::string &Expression,
                    std::deque<DataType> &operands,
                    std::deque<char> &operators) const
{
    std::string buffer = "";
    std::string bracketBuffer = "";
    char type = 'N'; // N:Number V:Variable B:Brackets S:String
    int openedbrackets = 0;
    bool InsideString = false;
    for (int i = 0; i < Expression.length(); i++)
    {
        char chnow = Expression[i];

        if (chnow == ' ' && !InsideString) // So the code could handle 1 + 1
            continue;

        if (openedbrackets == 0 && !InsideString)
        {
            switch (chnow)
            {
            // switch without break is used just to know if chnow is an operator
            case '+':
            case '-':
            case '*':
            case '/':
                // if chnow is an operator
                switch (type)
                {
                case 'N':
                    operands.push_back(std::stod(buffer));
                    break;
                case 'V':
                {
                    auto finder = Variables.find(buffer);
                    if (finder == Variables.end())
                        throw std::invalid_argument("Variable \'" + buffer +
                                                    "\' not found");
                    operands.push_back(finder->second);
                    break;
                }
                case 'B':
                    if (buffer.empty())
                    {
                        // There is a bracket, so it re-call itself to compute
                        // inside the bracket.
                        operands.push_back(Evaluate(bracketBuffer.substr(
                            1, bracketBuffer.length() - 2)));
                    }
                    else
                    {
                        // This is a function
                        operands.push_back(this->RunFunction(
                            buffer, bracketBuffer.substr(
                                        1, bracketBuffer.length() - 2)));
                    }
                    break;
                case 'S':
                    operands.push_back(buffer.substr(1, buffer.length() - 2));
                    break;
                }
                operators.push_back(chnow);

                buffer.clear();
                bracketBuffer.clear();
                type = 'N';
                continue;
            }
        }

        if ((('A' <= chnow && chnow <= 'Z') ||
             ('a' <= chnow && chnow <= 'z')) &&
            type != 'B' && type != 'S')
            type = 'V';
        else if ((chnow == '(' || chnow == ')') && type != 'S')
            type = 'B';
        else if (chnow == '\"' && type != 'B')
        {
            type = 'S';
            InsideString = !InsideString;
        }
        if (chnow == '(' && !InsideString)
            openedbrackets++;
        else if (chnow == ')' && !InsideString)
            openedbrackets--;

        if (type == 'B')
            bracketBuffer.push_back(chnow);
        else
            buffer.push_back(chnow);
    }
    switch (type)
    {
    case 'N':
        operands.push_back(std::stod(buffer));
        break;
    case 'V':
    {
        auto finder = Variables.find(buffer);
        if (finder == Variables.end())
            throw std::invalid_argument("Variable \'" + buffer +
                                        "\' not found");
        operands.push_back(finder->second);
        break;
    }
    case 'B':
        if (buffer.empty())
        {
            // There is a bracket, so it re-call itself to compute
            // inside the bracket.
            operands.push_back(
                Evaluate(bracketBuffer.substr(1, bracketBuffer.length() - 2)));
        }
        else
        {
            // This is a function
            operands.push_back(this->RunFunction(
                buffer, bracketBuffer.substr(1, bracketBuffer.length() - 2)));
        }
        break;
    case 'S':
        operands.push_back(buffer.substr(1, buffer.length() - 2));
        break;
    }
    return;
}

/**
 * @brief A helper function for Eval::Evaluate
 * @details The code will get a splited deque of operands, operators, and
 * calculate * and /. And finally, The code will store the results in operands2
 * and operators2
 *
 * @param operands Tokenized operands
 * @param operators Tokenized operators
 * @param operands2 A reference to store calculated operands
 * @param operators2 A reference to store calculated operators
 * @return void; since all the values are stored by reference
 */
void Eval::CalculatePriority(std::deque<DataType> &operands,
                             std::deque<char> &operators,
                             std::deque<DataType> &operands2,
                             std::deque<char> &operators2) const
{
    char lastoperator = operators.front();
    operands2.push_back(operands.front());
    if (lastoperator == '+' || lastoperator == '-')
        operators2.push_back(lastoperator);
    for (int i = 1; i < operands.size(); i++)
    {
        DataType n = operands[i];
        switch (lastoperator)
        {
        case '+':
        case '-':
            operands2.push_back(n);
            break;
        case '*':
            operands2.back() = operands2.back() * n;
            break;
        case '/':
            operands2.back() = operands2.back() / n;
            break;
        }

        if (i == operands.size() - 1)
            break;

        char noper = operators[i];
        if (noper == '+' || noper == '-')
            operators2.push_back(noper);
        lastoperator = noper;
    }
    return;
}

/**
 * @brief A helper function for Eval::Evaluate
 * @details The code will get a splited deque of operands, operators, and
 * calculate + and -. And finally, The code will return the calculated results.
 *
 * @param operands Tokenized operands
 * @param operators Tokenized operators
 * @return The calculated answer in DataType
 */
DataType Eval::CalculatePlusMinus(std::deque<DataType> &operands,
                                  std::deque<char> &operators) const
{
    while (operands.size() > 1)
    {
        DataType operand1 = operands.front();
        operands.pop_front();
        DataType operand2 = operands.front();
        operands.pop_front();
        char operator1 = operators.front();
        operators.pop_front();
        operands.push_front(operator1 == '+' ? operand1 + operand2
                                             : operand1 - operand2);
    }

    return operands[0];
}

// Custom functions; made at 2023 09 03

/**
 * @brief This is a main function, that will tokenize the args and call a
 * function
 * @param name The name of the function
 * @param args The args of a function in a form of "number, number, ..."
 * @return The return value of the called function
 */
DataType Eval::RunFunction(std::string name, std::string args) const
{
    std::vector<DataType> Tokenized;
    this->TokenizeArgs(args, Tokenized);
    return this->TestAndRunFunction(name, Tokenized);
}

/**
 * @brief This is a helper function for RunFunction; It will make a string in a
 * form of "number, number" to a vector
 * @param Expression The expression in a form of "number, number"
 * @param args The return vector
 */
void Eval::TokenizeArgs(std::string Expression,
                        std::vector<DataType> &args) const
{
    int brackets = 0;
    std::string buffer = "";
    for (int i = 0; i < Expression.length(); i++)
    {
        char point = Expression[i];
        if (point == ' ' || point == '\t')
            continue;

        if (point == ',' && brackets == 0)
        {
            if (buffer.empty())
                throw std::invalid_argument(
                    "No args after \',\' or no args at all");
            args.push_back(this->Evaluate(buffer));
            buffer.clear();
            continue;
        }

        buffer.push_back(point);

        if (point == '(')
        {
            brackets++;
            continue;
        }
        else if (point == ')')
        {
            brackets--;
            if (brackets < 0)
                throw std::invalid_argument("Invalid use of brackets");
            continue;
        }
    }
    if (buffer.empty())
        throw std::invalid_argument("No args after \',\' or no args at all");
    args.push_back(this->Evaluate(buffer));
    return;
}

/**
 * @brief This is a helper function for RunFunction; It will check that
 * everything is ok and call the function
 * @param name The name of the function
 * @param args The vector with args
 */
DataType Eval::TestAndRunFunction(std::string name,
                                  const std::vector<DataType> &args) const
{
    auto finder = Functions.find(name);
    if (finder == Functions.end())
        throw std::invalid_argument("The function \'" + name +
                                    "\' does not exist");
    if (args.size() != (finder->second).second)
        throw std::invalid_argument(
            "The numbers of the arguments do not match");
    return (finder->second).first(args);
}
} // namespace expreval