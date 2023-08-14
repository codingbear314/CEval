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

#ifndef __Eval__
#define __Eval__

#include <deque>
#include <string>
#include <map>
using std::string;
using std::deque;
using std::map;

class Eval
{
private:
    map<string, double> Variables;
public:
    Eval(void);
    Eval(map<string,double>);

    void AddVariable(string, double);

    const map<string, double>& GetVariableList(void);

    double Evaluate(string);

    double& operator[](string); //Get Variable Reference
    double operator()(string); //Evaluate
};
#include "eval.cpp"
#endif