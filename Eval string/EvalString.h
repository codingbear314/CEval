/**
 * EvalString.h & EvalString.cpp
 *
 * A simple way of evaluating expression
 * This library supports string & functions
 *
 * Code written by Jaewook Jung, 2023
 *
 * visit by blog! bit.ly/codingbear314
 *
 * @version 2.0
 * @author Jaewook Jung
 * @date 2023/09/05
 */

#ifndef __Eval__
#define __Eval__

#include <cfloat>
#include <deque>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace expreval
{

using DataType = std::variant<double, std::string, bool>;

inline auto constexpr IndexDouble = 0;
inline auto constexpr IndexString = 1;
inline auto constexpr IndexBooleen = 2;

bool isint(double);
std::string operator*(std::string, int);

DataType operator+(DataType, DataType);
DataType operator-(DataType, DataType);
DataType operator*(DataType, DataType);
DataType operator/(DataType, DataType);

/**
 * @class Eval
 * @brief A C++ Evaluation class
 */
class Eval
{
  public:
    std::map<std::string, DataType> Variables;
    std::map<
        std::string,
        std::pair<std::function<DataType(const std::vector<DataType> &)>, int>>
        Functions;
    void Tokenize(const std::string &, std::deque<DataType> &,
                  std::deque<char> &) const;
    void CalculatePriority(std::deque<DataType> &, std::deque<char> &,
                           std::deque<DataType> &, std::deque<char> &) const;
    DataType CalculatePlusMinus(std::deque<DataType> &,
                                std::deque<char> &) const;

    DataType RunFunction(std::string, std::string) const;
    void TokenizeArgs(std::string, std::vector<DataType> &) const;
    DataType TestAndRunFunction(std::string,
                                const std::vector<DataType> &) const;

  public:
    Eval(void);
    Eval(std::map<std::string, DataType>);
    Eval(std::map<
         std::string,
         std::pair<std::function<DataType(const std::vector<DataType> &)>,
                   int>>);
    Eval(std::map<std::string, DataType>,
         std::map<
             std::string,
             std::pair<std::function<DataType(const std::vector<DataType> &)>,
                       int>>);
    Eval(const Eval &);

    void AddVariable(std::string, DataType);
    void AddFunction(std::string,
                     std::function<DataType(const std::vector<DataType> &)>,
                     int);
    // Functions do not allow to be changed, so there are no member functions
    // to change them like variables

    const std::map<std::string, DataType> &GetVariableList(void) const;

    DataType Evaluate(std::string) const;

    DataType &operator[](std::string);      // Get Variable Reference
    DataType operator()(std::string) const; // Evaluate
};
} // namespace expreval
#include "DatatypeImplementations.cpp"
#include "EvalString.cpp"
#include "EvalStringImplement.cpp"

#endif