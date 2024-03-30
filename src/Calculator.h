#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

class Calculator {

  int defaultPrecision;

public:

  Calculator(int defaultPrecision);

  // This function uses recursion to calculate a math expression, if
  // successful it returns the answer, if not it throws an invalid argument
  // exception.
  // Inputs:
  // s is a string that represents the possible math
  // expression.
  // shouldFirstNumberBeNegative is a boolean that is false by default
  // and in most function calls, except when we try to perform a (-)
  // operation.
  static double calculate(std::string s, bool shouldFirstNumberBeNegative);

  // This function sets the precision of the answer, it prioritizes a valid
  // precision set by the user if there was any, or it uses the
  // defaultPrecision.
  int setPrecision(std::string s);

  // this function returns the defaultPrecision
  int getPrecision();
};

#endif // CALCULATOR_H
