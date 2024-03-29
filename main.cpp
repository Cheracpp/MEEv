#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// default precision if no precision argument is provided;
int defaultPrecision = 6;

// This function sets the precision of the answer, it prioritizes the
// precision set by the user if there was any, or it uses the defaultPrecision.
int getPrecision(string s);

// This function finds the last index of the current math expression
int expressionLastIndexFinder(string s);

// This function finds the amount of characters left before The closing
// parenthesis
int closingParenthesisFinder(string s);

// This function finds the  amount of characters left before the opening
// parenthesis
int openingParenthesisFinder(string s);

// This function checks if a character is an int by making use of "stoi()"
bool isInt(string c);

// This function uses recursion to calculate a math expression, if
// successful it returns the answer, if not it throws an invalid argument
// exception.
// Inputs: s is a string that represents the possible math
// expression.
// shouldFirstNumberBeNegative is a boolean that is false by default
// and in most function calls, except when we try to perform a (-)
// operation.
double calculate(string s, bool shouldFirstNumberBeNegative);

////////// main function///////////////
int main(int argc, char *argv[]) {
  if (argc == 3) {
    string mathExpression = argv[1];
    string precisionArgument = argv[2];
    if (mathExpression.length() == 0) {
      throw invalid_argument(
          "Invalid expression: The expression cannot be empty. Please provide "
          "a valid mathematical expression.");
    }
    cout << setprecision(getPrecision(precisionArgument));
    cout << "Answer: " << calculate(mathExpression, false) << endl;
  } else if (argc == 2) {
    cout << setprecision(defaultPrecision);
    string mathExpression = argv[1];

    cout << "Answer: " << calculate(mathExpression, false) << endl;
  } else {
    throw invalid_argument(
        "You need to provide at least a valid math expression");
  }
  return 0;
}
///////////////////////////////////////

double calculate(string s, bool shouldFirstNumberBeNegative) {
  double answer = 0;
  string bufferString = ""; // holds a soon-to-be int or a
                            // possible soon-to-be double
  bool isCharacterValid =
      false; // used to mark a string of characters valid up to '('.
  int emptyCharactersCount = 0; // used to count empty characters.
  bool isFirstDecimal = true; // used to allow only one decimal per double;
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
      if (i == (s.length() - 1) || i == 0 || (i - emptyCharactersCount) == 0) {
        throw invalid_argument("Invalid expression: multiplication operator "
                               "'*' cannot be at the beginning, end or "
                               "immediately before a ')'.");
      }
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
      int j = 0;
      string character = s.substr(i + 1, 1);
      if (isInt(character)) {
        j = expressionLastIndexFinder(s.substr(i + 1));
      } else if (character == "-") {
        j = expressionLastIndexFinder(s.substr(i + 2)) + 1;
      } else {
        j = closingParenthesisFinder(s.substr(i + 1)) + 2;
        if ((i + j + 1) < s.length()) {
          char possibleCaretSymbol = s[i + j + 1];
          if (possibleCaretSymbol == '^') {
            j += expressionLastIndexFinder(s.substr(i + j + 1));
          }
        }
      }
      double answerButWithConnections = calculate(s.substr(i + 1, j), false);
      i = i + j;
      answer *= answerButWithConnections;
      break;
    }
    case '/': {
      if (i == (s.length() - 1) || i == 0 || (i - emptyCharactersCount) == 0) {
        throw invalid_argument("Invalid expression: Division operator '/' "
                               "cannot be at the beginning, end or "
                               "immediately before a ')'.");
      }
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
      int j = 0;
      string character = s.substr(i + 1, 1);
      if (isInt(character)) {
        j = expressionLastIndexFinder(s.substr(i + 1));
      } else if (character == "-") {
        j = expressionLastIndexFinder(s.substr(i + 2)) + 1;
      } else {
        j = closingParenthesisFinder(s.substr(i + 1)) + 2;
        if ((i + j + 1) < s.length()) {
          char possibleCaretSymbol = s[i + j + 1];
          if (possibleCaretSymbol == '^') {
            j += expressionLastIndexFinder(s.substr(i + j + 1));
          }
        }
      }
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
      if (i == (s.length() - 1) || i == 0 || (i - emptyCharactersCount) == 0) {
        throw invalid_argument("invalid expression: The exponent operator '^' "
                               "cannot be at the beginning, end or "
                               "immediately before a ')'.");
      }
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
      int j = 0;
      string character = s.substr(i + 1, 1);
      if (isInt(character)) {
        j = expressionLastIndexFinder(s.substr(i + 1));
      } else if (character == "-") {
        j = expressionLastIndexFinder(s.substr(i + 2)) + 1;
      } else {
        j = closingParenthesisFinder(s.substr(i + 1)) + 2;
      }
      if (shouldFirstNumberBeNegative) {
        answer *= -1;
        shouldFirstNumberBeNegative = false;
      }
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
      int k = closingParenthesisFinder(s.substr(i));
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
        i++;
        while (s[i] == ' ') {
          i++;
        }
        string possibleInt = s.substr(i, 1);
        if (isInt(possibleInt)) {
          throw invalid_argument(
              "Invalid expression: Ambiguous multiplication detected. Please "
              "explicitly state multiplication with an asterisk '*' between "
              "a "
              "closing parenthesis and a number. For example, use '(1+2)*2' "
              "instead of '(1+2)32'.");
        }
        i--;
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
      string character = s.substr(i, 1);
      if (isInt(character)) {
        bufferString += character;
        answer = stod(bufferString);
      } else if (character == ".") {
        if (isFirstDecimal) {
          isFirstDecimal = false;
          if (i == (s.length() - 1) || i == 0) {
            throw invalid_argument(
                "Invalid expression: Decimal '.' cannot be placed at "
                "the beginning or the end of the expression.");
          }
          string nextChar = s.substr(i - 1, 3);
          if (!isInt(nextChar)) {
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
        int k = openingParenthesisFinder(s.substr(i));
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
        "Invalid expression: The expression cannot be empty, incomplete, or contain only "
        "spaces. Please provide a valid mathematical expression.");
  }
  return answer;
}

int expressionLastIndexFinder(string s) {
  int index = 0;
  for (char c : s) {
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      return index;
    } else {
      index++;
    }
  }
  return s.length();
}

int closingParenthesisFinder(string s) {
  bool areWeInsideParentheses = false;
  int count = 0;
  int index = 0;
  for (char c : s) {
    if (c == '(') {
      areWeInsideParentheses = true;
      count--;
    } else if (c == ')') {
      count++;
    }
    if ((count == 0) && (areWeInsideParentheses == true)) {
      break;
    }
    index++;
  }
  if (count != 0) {
    throw invalid_argument(
        "Invalid expression: Every opening parenthesis '(' must be paired "
        "with "
        "a corresponding closing parenthesis ')'. Please ensure that all "
        "parentheses are properly closed and matched");
  }
  return index - 1;
}

bool isInt(string c) {
  try {
    int var = stoi(c);
    return true;
  } catch (const invalid_argument &) {
    return false;
  }
}

int getPrecision(string s) {
  try {
    int precision = stoi(s);
    if (precision <= 15 && precision >= 0) {
      return precision;
    } else {
      cout << "precision shouldn't exceed 15, using the default precision: 6"
           << endl;
      return defaultPrecision;
    }
  } catch (const invalid_argument &) {
    cout << "precison should be a positive int between 1-15, using the default "
            "precision: 6"
         << endl;
    return defaultPrecision;
  }
}

int openingParenthesisFinder(string s) {
  int count = 0;
  for (char c : s) {
    if (c == '(') {
      return count;
    } else {
      count++;
      if (count > 4) {
        return count;
      }
    }
  }
  return 100;
}
