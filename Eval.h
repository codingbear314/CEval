/**
 * Eval.h & Eval.cpp
 *
 * Continued project from CEval.h v 3.0
 * The goal is to make the code as simple as possible, since the last version
 * was over-complicated
 *
 * This library would NOT support string maniplications; use the CEval.h v3.0 to
 * do string maniplications
 *
 * Code written by Jaewook Jung, 2023
 *
 * visit by blog! bit.ly/codingbear314
 *
 * @version 1.0
 * @author Jaewook Jung
 * @date 2023/08/14
 */

#ifndef __Eval__
#define __Eval__

#include <deque>
#include <map>
#include <stdexcept>
#include <string>

/**
 * @class Eval
 * @brief A C++ Evaluation class
 */
class Eval
{
  private:
    std::map<std::string, double> Variables;
    void Tokenize(const std::string &, std::deque<double> &,
                  std::deque<char> &) const;
    void CalculatePriority(std::deque<double> &, std::deque<char> &,
                           std::deque<double> &, std::deque<char> &) const;
    double CalculatePlusMinus(std::deque<double> &, std::deque<char> &) const;

  public:
    Eval(void);
    Eval(std::map<std::string, double>);

    void AddVariable(std::string, double);

    const std::map<std::string, double> &GetVariableList(void) const;

    double Evaluate(std::string) const;

    double &operator[](std::string);      // Get Variable Reference
    double operator()(std::string) const; // Evaluate
};
#include "eval.cpp"
#endif