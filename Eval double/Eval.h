/**
 * Eval.h & Eval.cpp
 *
 * A simple way of evaluating expressions
 * This library supports functions
 *
 * This library only support double types
 *
 * Code written by Jaewook Jung, 2023
 *
 * visit by blog! bit.ly/codingbear314
 *
 * @version 1.5
 * @author Jaewook Jung
 * @date 2023/09/04
 */

#ifndef __Eval__
#define __Eval__

#include <deque>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @class Eval
 * @brief A C++ Evaluation class
 */
class Eval
{
  private:
    std::map<std::string, double> Variables;
    std::map<std::string,
             std::pair<std::function<double(const std::vector<double> &)>, int>>
        Functions;
    void Tokenize(const std::string &, std::deque<double> &,
                  std::deque<char> &) const;
    void CalculatePriority(std::deque<double> &, std::deque<char> &,
                           std::deque<double> &, std::deque<char> &) const;
    double CalculatePlusMinus(std::deque<double> &, std::deque<char> &) const;

    double RunFunction(std::string, std::string) const;
    void TokenizeArgs(std::string, std::vector<double> &) const;
    double TestAndRunFunction(std::string, const std::vector<double> &) const;

  public:
    Eval(void);
    Eval(std::map<std::string, double>);
    Eval(std::map<
         std::string,
         std::pair<std::function<double(const std::vector<double> &)>, int>>);
    Eval(std::map<std::string, double>,
         std::map<std::string,
                  std::pair<std::function<double(const std::vector<double> &)>,
                            int>>);
    Eval(const Eval &);

    void AddVariable(std::string, double);
    void AddFunction(std::string,
                     std::function<double(const std::vector<double> &)>, int);
    // Functions do not allow to be changed, so there are no member functions
    // to change them like variables

    const std::map<std::string, double> &GetVariableList(void) const;

    double Evaluate(std::string) const;

    double &operator[](std::string);      // Get Variable Reference
    double operator()(std::string) const; // Evaluate
};
#include "Eval.cpp"
#endif