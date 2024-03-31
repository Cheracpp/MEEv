#include "Calculator.h"
#include "Utility.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

Calculator::Calculator(int DefaultPrecision)
    : defaultPrecision{DefaultPrecision} {}

double Calculator::calculate(string s, bool shouldFirstNumberBeNegative) {
  double answer = 0;
  string bufferString = ""; // holds a soon-to-be int or a
                            // possible soon-to-be double
  bool isCharacterValid =
      false; // used to mark a string of characters valid up to '('.
  int emptyCharactersCount = 0; // used to count empty characters.
  bool isFirstDecimal = true;   // used to allow only one decimal per double;
  for (size_t i = 0; i < s.length(); i++) {
    switch (s[i]) {

    case ' ':
      emptyCharactersCount++;
      continue;
    case '+': {
      if (i == (s.length() - 1) || i == 0 || (i - emptyCharactersCount) == 0) {
        throw invalid_argument("Invalid expression: addition operator '+' "
                               "cannot be at the beginning, end or "
                               "immediately before a ')'.");
      }
      char nextChar = s[i + 1];
      if (nextChar == '-' || nextChar == '+' || nextChar == '*' ||
          nextChar == '/' || nextChar == '^') {
        throw invalid_argument(
            "Invalid expression: Two consecutive arithmetic operators or an "
            "arithmetic operator followed by '^' are not allowed. For example, "
            "'7++2' or '5+^3' are invalid.");
      }
      if (shouldFirstNumberBeNegative) {
        answer *= -1;
        shouldFirstNumberBeNegative = false;
      }
      answer += calculate(s.substr(++i), false);
      return answer;
    }
    case '-': {
      if (i == (s.length() - 1)) {
        throw invalid_argument(
            "Invalid expression: subtraction operator '-' cannot be at the end "
            "or immediately before a ')'.");
      }
      char nextChar = s[i + 1];
      if (nextChar == '-' || nextChar == '+' || nextChar == '*' ||
          nextChar == '/' || nextChar == '^') {

        throw invalid_argument(
            "Invalid expression: Two consecutive arithmetic operators or an "
            "arithmetic operator followed by '^' are not allowed. For example, "
            "'7--2' or '5-^3' are invalid.");
      }
      answer += calculate(s.substr(++i), true);
      return answer;
    }
    case '*': {
      // find the next non-space char
      int k = 0;
      if (i < s.length() - 1) {
        k = Utility::firstCharacterIndexFinder(s.substr(i + 1));
      }
      if ((i + k) == (s.length() - 1) || i == 0 ||
          (i - emptyCharactersCount) == 0) {
        throw invalid_argument("Invalid expression: multiplication operator "
                               "'*' cannot be at the beginning, end or "
                               "immediately before a ')'.");
      }
      i = i + k;
      char nextChar = s[i + 1];
      if (nextChar == '+' || nextChar == '*' || nextChar == '/' ||
          nextChar == '^') {

        throw invalid_argument(
            "Invalid expression: Consecutive arithmetic operators are not "
            "allowed, except for a minus sign following an operator to "
            "indicate a negative number. Also, an arithmetic operator "
            "followed "
            "by '^' is not permitted. For example, '7*+2' is invalid, but "
            "'7*-2' is valid.");
      }

      if (shouldFirstNumberBeNegative) {
        answer *= -1;
        shouldFirstNumberBeNegative = false;
      }
      int j = Utility::findLastIndexExpression(s.substr(i+1));
      double answerButWithConnections = calculate(s.substr(i + 1, j), false);
      i = i + j;
      answer *= answerButWithConnections;
      break;
    }
    case '/': {
      // find the next non-space char
      int k = 0;
      if (i < s.length() - 1) {
        k = Utility::firstCharacterIndexFinder(s.substr(i + 1));
      }
      if ((i + k) == (s.length() - 1) || i == 0 ||
          (i - emptyCharactersCount) == 0) {
        throw invalid_argument("Invalid expression: division operator "
                               "'/' cannot be at the beginning, end or "
                               "immediately before a ')'.");
      }
      i += k;
      char nextChar = s[i + 1];
      if (nextChar == '+' || nextChar == '*' || nextChar == '/' ||
          nextChar == '^') {

        throw invalid_argument(
            "Invalid expression: Consecutive arithmetic operators are not "
            "allowed, except for a minus sign following an operator to "
            "indicate a negative number. Also, an arithmetic operator "
            "followed "
            "by '^' is not permitted. For example, '7/+2' is invalid, but "
            "'7/-2' is valid.");
      }
      if (shouldFirstNumberBeNegative) {
        answer *= -1;
        shouldFirstNumberBeNegative = false;
      }
      int j = Utility::findLastIndexExpression(s.substr(i+1));
      double answerButWithConnections = calculate(s.substr(i + 1, j), false);
      if (answerButWithConnections == 0) {
        throw invalid_argument(
            "Invalid expression: Division by zero is not allowed. Please "
            "revise the expression to avoid dividing by zero.");
      }
      i = i + j;
      answer /= answerButWithConnections;
      break;
    }
    case '^': {
      // find the next non-space char
      int k = 0;
      if (i < s.length() - 1) {
        k = Utility::firstCharacterIndexFinder(s.substr(i + 1));
      }
      if ((i + k) == (s.length() - 1) || i == 0 ||
          (i - emptyCharactersCount) == 0) {
        throw invalid_argument("Invalid expression: exponent operator "
                               "'^' cannot be at the beginning, end or "
                               "immediately before a ')'.");
      }
      i = i + k;
      char nextChar = s[i + 1];
      if (nextChar == '+' || nextChar == '*' || nextChar == '/' ||
          nextChar == '^') {

        throw invalid_argument(
            "Invalid expression: Consecutive exponent operators ('^') are not "
            "allowed, e.g., '7^^2' is invalid. Also, an exponent operator "
            "cannot be immediately followed by an arithmetic operator, except "
            "for a minus sign to denote a negative value. For example, '^+' or "
            "'^*' is invalid, but '^-' to indicate a negative exponent is "
            "valid.");
      }
      if (shouldFirstNumberBeNegative) {
        answer *= -1;
        shouldFirstNumberBeNegative = false;
      }
      int j = Utility::findLastIndexExpression(s.substr(i+1));
      double exponent = calculate(s.substr(i + 1, j), false);
      if (answer == 0 && exponent < 0)
        throw invalid_argument(
            "Invalid expression: 0^-x is undefined for positive values of x as "
            "it implies division by zero.");
      i = i + j;
      answer = pow(answer, exponent);
      break;
    }
    case '(': {
      if (i == (s.length() - 1)) {
        throw invalid_argument(
            "Invalid expression: Opening parenthesis '(' cannot be placed at "
            "the end of the expression.");
      }
      char nextChar = s[i + 1];
      if (nextChar == '+' || nextChar == '*' || nextChar == '/' ||
          nextChar == '^') {

        throw invalid_argument(
            "Invalid expression: An opening parenthesis '(' should not be "
            "immediately followed by an arithmetic operator or the exponent "
            "operator '^', except for a minus sign '-' to denote a negative "
            "number. For example, '(*', '(+', and '(^' are invalid, while "
            "'(-' "
            "is valid.");
      }
      int k = Utility::closingParenthesisFinder(s.substr(i));
      if (k == 0) {
        throw invalid_argument("Invalid expression: Empty parentheses '()' are "
                               "not allowed. Please include a valid expression "
                               "or value between the parentheses.");
      }
      isCharacterValid = false; // resetting the validation;
      double x =
          calculate(s.substr(i + 1, k), false); // x is what's inside the '()'.
      if (i == 0 || (i > 0 && s[i - 1] == ' ')) {
        answer = x;
      } else {
        if (i == 3 || (i > 3 && s[i - 4] == ' ')) {
          string function =
              s.substr(i - 3, 3); // holds the name of a possible function
          if (function == "tan") {
            answer = tan(x);
          } else if (function == "cos") {
            answer = cos(x);
          } else if (function == "sin") {
            answer = sin(x);
          } else {
            throw invalid_argument(
                "Invalid expression: Unrecognized function detected. "
                "Please "
                "ensure you are using standard mathematical function "
                "names "
                "in lowercase, such as 'sin(x)', 'cos(x)', 'tan(x)', etc. "
                "Function names must be in lowercase to be recognized "
                "correctly.");
          }

        } else if (i == 4 || (i > 4 && s[i - 5] == ' ')) {
          string function = s.substr(i - 4, 4);
          if (function == "sqrt") {
            if (x < 0)
              throw invalid_argument(
                  "Invalid input for sqrt: The square root of a negative "
                  "number is "
                  "not defined in the set of real numbers. Please adjust the "
                  "expression to avoid taking the square root of negative "
                  "values.");
            answer = sqrt(x);
          } else if (function == "atan") {
            answer = atan(x);
          } else if (function == "acos") {
            if (x < -1 || x > 1)
              throw invalid_argument(
                  "Invalid input for acos: Value must be within [-1, 1].");
            answer = acos(x);
          } else if (function == "asin") {
            if (x < -1 || x > 1)
              throw invalid_argument(
                  "Invalid input for asin: Value must be within [-1, 1].");
            answer = asin(x);
          } else {
            throw invalid_argument(
                "Invalid expression: Unrecognized function detected. Please "
                "ensure you are using standard mathematical function names in "
                "lowercase, such as 'asin(x)', 'acos(x)', 'atan(x)', 'sqrt(x)' "
                "etc. Function names must be in lowercase to be recognized "
                "correctly.");
          }
        }
      }
      i = i + k + 1;
      if (i < (s.length() - 1)) {
          i += Utility::firstCharacterIndexFinder(s.substr(i+1));
        char possibleInt = s[i+1];
        if (isdigit(possibleInt)) {
          throw invalid_argument(
              "Invalid expression: Ambiguous multiplication detected. Please "
              "explicitly state multiplication with an asterisk '*' between "
              "a "
              "closing parenthesis and a number. For example, use '(1+2)*2' "
              "instead of '(1+2)32'.");
        }
      }

      if (shouldFirstNumberBeNegative) {
        answer *= -1;
        shouldFirstNumberBeNegative = false;
      }
      break;
    }
    case ')': {
      throw invalid_argument(
          "Invalid expression: Every opening parenthesis '(' must be paired "
          "with a corresponding closing parenthesis ')'. Please ensure that "
          "all "
          "parentheses are properly closed and matched");
    }
    default: {
      char character = s[i];
      if (isdigit(character)) {
        bufferString += character;
        answer = stod(bufferString);
      } else if (character == '.') {
        if (isFirstDecimal) {
          isFirstDecimal = false;
          if (i == (s.length() - 1) || i == 0) {
            throw invalid_argument(
                "Invalid expression: Decimal '.' cannot be placed at "
                "the beginning or the end of the expression.");
          }
          string possibleInt = s.substr(i - 1, 3);
          if (!Utility::isInt(possibleInt)) {
            throw invalid_argument(
                "Invalid expression: Decimal points must be preceded and "
                "followed by digits. Ensure that each decimal is part of a "
                "valid number. For example, use '0.1' instead of '.1' and "
                "'1.0' instead of '1.'.");
          }
          bufferString += character;
        } else {
          throw invalid_argument(
              "Invalid expression: Numbers can only have one decimal point. "
              "Please correct the numerical values to ensure each has only a "
              "single decimal point. For example, '1.1.1' and '2...3' are "
              "not "
              "valid");
        }
      } else {
        int k = Utility::openingParenthesisFinder(s.substr(i));
        if (k != 3 && k != 4 && isCharacterValid == false) {
          throw invalid_argument(
              "Invalid expression: Unrecognized characters detected. Please "
              "ensure the expression only includes valid numbers, operators, "
              "and known function names.");
        } else {
          isCharacterValid = true;
        }
      }
    }
    }
  }
  if (shouldFirstNumberBeNegative) {
    answer *= -1;
  }
  if (emptyCharactersCount == s.length()) {
    throw invalid_argument(
        "Invalid expression: The expression cannot be empty, incomplete, or "
        "contain only "
        "spaces. Please provide a valid mathematical expression.");
  }
  return answer;
}

int Calculator::setPrecision(string s) {
  try {
    int precision = stoi(s);
    if (precision <= 15 && precision >= 0) {
      return precision;
    } else {
      cout << "precision shouldn't exceed 15, using the default precision: "
           << defaultPrecision << endl;
      return defaultPrecision;
    }
  } catch (const invalid_argument &) {
    cout << "precison should be a positive int between 1-15, using the default "
            "precision: "
         << defaultPrecision << endl;
    return defaultPrecision;
  }
}

int Calculator::getPrecision() { return defaultPrecision; }
