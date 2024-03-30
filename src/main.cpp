#include "Calculator.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

int DefaultPrecision = 6;

////////// main function///////////////
int main(int argc, char *argv[]) {
  Calculator calculator{DefaultPrecision};
  if (argc == 3) {
    string mathExpression = argv[1];
    string precisionArgument = argv[2];
    if (mathExpression.length() == 0) {
      throw invalid_argument(
          "Invalid expression: The expression cannot be empty. Please provide "
          "a valid mathematical expression.");
    }
    cout << setprecision(calculator.setPrecision(precisionArgument));
    cout << "Answer: " << calculator.calculate(mathExpression, false) << endl;
  } else if (argc == 2) {
    string mathExpression = argv[1];
    cout << setprecision(DefaultPrecision);
    cout << "Answer: " << calculator.calculate(mathExpression, false) << endl;
  } else {
    throw invalid_argument(
        "You need to provide at least a valid math expression");
  }
  return 0;
}
///////////////////////////////////////
