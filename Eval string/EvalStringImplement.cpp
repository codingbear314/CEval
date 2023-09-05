#include "EvalString.h"
namespace expreval
{
/**
 * @brief returns if k is a integer value
 * @param k A double value to be checked
 * @return Whether k is a integer value
 */
bool isint(double k) { return k - (double)((int)k) < FLT_EPSILON; }

/**
 * @brief multiply a string with a int; repeats the string
 * @param a The string that would be repeated
 * @param b The number of times a would be repeated
 * @return The result of repeatation
 */
std::string operator*(std::string a, int b)
{
    std::string output = "";
    while (b--)
        output += a;
    return output;
}

/**
 * @brief formats a string value to a string, with no 0 at the end
 * @param d A double value that would be formated
 * @return The result
 */
std::string double_to_string(double d)
{
    if (d - (double)((int)d) < FLT_EPSILON)
        return std::to_string((int)d);
    else
    {
        std::string s = std::to_string(d);
        int i = s.find_last_not_of('0');
        if (i != s.length() - 1)
            s.erase(i + 1, s.length());
        return s;
    }
}

/**
 * @brief Addition of two DataTypes
 * @param a The first operand
 * @param b The second operand
 * @return The result of the addition
 */
DataType operator+(DataType a, DataType b)
{
    int code = a.index() * 3 + b.index();
    switch (code)
    {
    case 3 * 0 + 0:
        return std::get<double>(a) + std::get<double>(b);
    case 3 * 0 + 1:
        return double_to_string(std::get<double>(a)) + std::get<std::string>(b);
    case 3 * 0 + 2:
        return std::get<double>(a) + std::get<bool>(b);
    case 3 * 1 + 0:
        return std::get<std::string>(a) + double_to_string(std::get<double>(b));
    case 3 * 1 + 1:
        return std::get<std::string>(a) + std::get<std::string>(b);
    case 3 * 1 + 2:
        return std::get<std::string>(a) + (std::get<bool>(b) ? "1" : "0");
    case 3 * 2 + 0:
        return std::get<bool>(a) + std::get<double>(b);
    case 3 * 2 + 1:
        return (std::get<bool>(a) ? "1" : "0") + std::get<std::string>(b);
    case 3 * 2 + 2:
        return (double)std::get<bool>(a) + (double)std::get<bool>(b);
    default:
        throw std::logic_error(
            "If this message is displayed, re-install the library.");
    }
}

/**
 * @brief Subtraction of two DataTypes
 * @param a The first operand
 * @param b The second operand
 * @return The result of the Subtraction
 */
DataType operator-(DataType a, DataType b)
{
    int code = a.index() * 3 + b.index();
    switch (code)
    {
    case 3 * 0 + 0:
        return std::get<double>(a) - std::get<double>(b);
    case 3 * 0 + 2:
        return std::get<double>(a) - (double)std::get<bool>(b);
    case 3 * 2 + 0:
        return (double)std::get<bool>(a) - std::get<double>(b);
    case 3 * 2 + 2:
        return (double)std::get<bool>(a) - (double)std::get<bool>(b);
    default:
        throw std::logic_error("Can't subtract strings");
    }
}

/**
 * @brief Multiplication of two DataTypes
 * @param a The first operand
 * @param b The second operand
 * @return The result of the Multiplication
 */
DataType operator*(DataType a, DataType b)
{
    int code = a.index() * 3 + b.index();
    switch (code)
    {
    case 3 * 0 + 0:
        return std::get<double>(a) * std::get<double>(b);
    case 3 * 0 + 2:
        return std::get<double>(a) * (double)std::get<bool>(b);
    case 3 * 1 + 0:
        if (isint(std::get<double>(b)))
            return std::get<std::string>(a) * (int)std::get<double>(b);
        else
            throw std::logic_error("Can\'t multiply a string to a double");
    case 3 * 0 + 1:
        if (isint(std::get<double>(a)))
            return std::get<std::string>(b) * (int)std::get<double>(a);
        else
            throw std::logic_error("Can\'t multiply a string to a double");
    case 3 * 1 + 2:
        return std::get<bool>(b) ? std::get<std::string>(a) : "";
    case 3 * 2 + 1:
        return std::get<bool>(a) ? std::get<std::string>(b) : "";
    case 3 * 2 + 2:
        return (double)std::get<bool>(a) * (double)std::get<bool>(b);
    default:
        throw std::logic_error("Invalid multiplication");
    }
}

/**
 * @brief division of two DataTypes
 * @param a The first operand
 * @param b The second operand
 * @return The result of the division
 */
DataType operator/(DataType a, DataType b)
{
    int code = a.index() * 3 + b.index();
    switch (code)
    {
    case 3 * 0 + 0:
        if (std::get<double>(b) < FLT_EPSILON)
            throw std::logic_error("Can't divide by 0");
        return std::get<double>(a) / std::get<double>(b);
    case 3 * 0 + 2:
        if (!std::get<bool>(b))
            throw std::logic_error("Can't divide by 0");
        return std::get<double>(a);
    case 3 * 2 + 0:
        if (std::get<double>(b) < FLT_EPSILON)
            throw std::logic_error("Can't divide by 0");
        return (double)std::get<bool>(a) / std::get<double>(b);
    case 3 * 2 + 2:
        if (!std::get<bool>(b))
            throw std::logic_error("Can't divide by 0");
        return std::get<bool>(a);
    default:
        throw std::logic_error("Invalid division");
    }
}
} // namespace expreval