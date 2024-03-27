#include <cmath>
#include <iostream>
#include <string>

using namespace std;

// This function finds the last index of the current math expression
int expressionLastIndexFinder(string s);

// This function finds the last index before The closing parenthesis
int closingParenthesisFinder(string s);

// This function checks if a character is an int by making use of "stoi()"
bool isInt(string c);

// This function tries to calculate a math expression, if successful it
// returns the answer (using recursion), if not it throws an invalid argument
// exception.
// Inputs: s is a string that represents the possible math
// expression.
// shouldFirstNumberBeNegative is a boolean that is false by default
// and in most function calls, except when we try to perform a (-) operation.
double calculate(string s, bool shouldFirstNumberBeNegative);

////////// main function///////////////
int main(int argc, char *argv[]) {

  cout << "Answer is: " << calculate(argv[1], false) << endl;
  return 0;
}
///////////////////////////////////////

double calculate(string s, bool shouldFirstNumberBeNegative) {
  double answer = 0;
  string bufferString; // a string that holds a soon-to-be int or a possible
                       // soon-to-be double
  for (size_t i = 0; i < s.length(); i++) {
    if (s[i] == '+') {
      if (shouldFirstNumberBeNegative) {
        answer *= -1;
      }
      answer += calculate(s.substr(++i), false);
      return answer;
    } else if (s[i] == '-') {
      answer += calculate(s.substr(++i), true);
      return answer;
    } else if (s[i] == '*') {
      if (shouldFirstNumberBeNegative) {
        answer *= -1;
      }
      int j = 0;
      string character = s.substr(i + 1, 1);
      if (isInt(character)) {
        j = expressionLastIndexFinder(s.substr(i + 1));
      } else if (character == "-") {
        j = expressionLastIndexFinder(s.substr(i + 2));
      } else {
        j = closingParenthesisFinder(s.substr(i + 1)) + 2;
        if (s[i + j + 1] == '^') {
          j += expressionLastIndexFinder(s.substr(i + j + 1));
        }
      }
      double instant = calculate(s.substr(i + 1, j), false);
      i = i + j;
      answer *= instant;
    } else if (s[i] == '/') {
      if (shouldFirstNumberBeNegative) {
        answer *= -1;
      }
      int j = 0;
      string character = s.substr(i + 1, 1);
      if (isInt(character)) {
        j = expressionLastIndexFinder(s.substr(i + 1));
      } else if (character == "-") {
        j = expressionLastIndexFinder(s.substr(i + 2));
      } else {
        j = closingParenthesisFinder(s.substr(i + 1)) + 2;
        if (s[i + j + 1] == '^') {
          j += expressionLastIndexFinder(s.substr(i + j + 1));
        }
      }
      double instant = calculate(s.substr(i + 1, j), false);
      i = i + j;
      answer /= instant;
    } else if (s[i] == '^') {
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
      }
      double exponent = calculate(s.substr(i + 1, j), false);
      i = i + j;
      answer = pow(answer, exponent);
    } else if (s[i] == '(') {
      if (i == 0 || (i > 0 && s[i - 1] == ' ')) {
        int k = closingParenthesisFinder(s.substr(i));
        answer = calculate(s.substr(i + 1, k), false);
        if (shouldFirstNumberBeNegative) {
          answer *= -1;
        }
        i = i + k + 1;
      } else {
        if (i == 3 || (i > 3 && s[i - 4] == ' ')) {
          string fun = s.substr(i - 3, i);
          if (fun == "tan") {
            int k = closingParenthesisFinder(s.substr(i));
            answer = tan(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              answer *= -1;
            }
            i = i + k + 1;
          } else if (fun == "cos") {
            int k = closingParenthesisFinder(s.substr(i));
            answer = cos(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              answer *= -1;
            }
            i = i + k + 1;
          } else if (fun == "sin") {
            int k = closingParenthesisFinder(s.substr(i));
            answer = sin(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              answer *= -1;
            }
            i = i + k + 1;
          } else {
            throw invalid_argument(
                "Malformed expression; Make sure that all the standard math "
                "functions are correctly written and in lowercase.");
          }

        } else if (i == 4 || (i > 4 && s[i - 5] == ' ')) {

          string fun = s.substr(i - 4, i);
          if (fun == "sqrt") {
            int k = closingParenthesisFinder(s.substr(i));
            answer = sqrt(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              answer *= -1;
            }
            i = i + k + 1;
          } else if (fun == "atan") {
            int k = closingParenthesisFinder(s.substr(i));
            answer = atan(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              answer *= -1;
            }
            i = i + k + 1;
          } else if (fun == "acos") {
            int k = closingParenthesisFinder(s.substr(i));
            answer = acos(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              answer *= -1;
            }
            i = i + k + 1;
          } else if (fun == "asin") {
            int k = closingParenthesisFinder(s.substr(i));
            answer = asin(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              answer *= -1;
            }
            i = i + k + 1;
          } else {
            throw invalid_argument(
                "Malformed expression; Make sure that all the standard math "
                "functions are correctly written and in lowercase.");
          }
        }
      }
    } else {
      string character = s.substr(i, 1);
      if (isInt(character)) {
        bufferString += character;
        answer = stod(bufferString);
      } else if (character == ".") {
        bufferString += character;
      }
    }
  }
  if (shouldFirstNumberBeNegative) {
    answer *= -1;
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
  return index - 1;
}

bool isInt(string c) {
  try {
    int var = stoi(c);
    return true;
  } catch (const std::invalid_argument &) {
    return false;
  }
}
