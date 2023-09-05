#ifndef DisableDebugTools
#include "EvalString.h"
#include <iostream>
/**
 * This is actually just a debug tool
 * You could disable this by defineing DisableDebugTools macro before including
 * the header
 */
namespace expreval
{
void print(DataType a)
{
    switch (a.index())
    {
    case IndexDouble:
        std::cout << std::get<double>(a);
        break;
    case IndexString:
        std::cout << std::get<std::string>(a);
        break;
    case IndexBooleen:
        std::cout << std::get<bool>(a) ? "true" : "false";
        break;
    }
}
void print(std::deque<DataType> dq)
{
    for (DataType i : dq)
    {
        print(i);
        std::cout << ", ";
    }
    std::cout << std::endl;
}
template <class type> void print(std::deque<type> dq)
{
    for (type i : dq)
        std::cout << i << ", ";
    std::cout << std::endl;
}
} // namespace expreval
#endif