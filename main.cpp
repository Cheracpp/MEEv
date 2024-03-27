#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int indexFinder(string s) {
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

int secondParentheseFinder(string s) {
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
double calculate(string s, bool shouldFirstNumberBeNegative) {
  double ans = 0;
  string bufferString;
  for (size_t i = 0; i < s.length(); i++) {
    if (s[i] == '+') {
      if (shouldFirstNumberBeNegative) {
        ans *= -1;
      }
      ans += calculate(s.substr(++i), false);
      return ans;
    } else if (s[i] == '-') {
      ans += calculate(s.substr(++i), true);
      return ans;
    } else if (s[i] == '*') {
      if (shouldFirstNumberBeNegative) {
        ans *= -1;
      }
      int j = 0;
      string character = s.substr(i + 1, 1);
      if (isInt(character)) {
        j = indexFinder(s.substr(i + 1));
      } else if (character == "-") {
        j = indexFinder(s.substr(i + 2));
      } else {
        j = secondParentheseFinder(s.substr(i + 1)) + 2;
        if (s[i + j + 1] == '^') {
          j += indexFinder(s.substr(i + j + 1));
        }
      }
      double instant = calculate(s.substr(i + 1, j), false);
      i = i + j;
      ans *= instant;
    } else if (s[i] == '/') {
      if (shouldFirstNumberBeNegative) {
        ans *= -1;
      }
      int j = 0;
      string character = s.substr(i + 1, 1);
      if (isInt(character)) {
        j = indexFinder(s.substr(i + 1));
      } else if (character == "-") {
        j = indexFinder(s.substr(i + 2));
      } else {
        j = secondParentheseFinder(s.substr(i + 1)) + 2;
        if (s[i + j + 1] == '^') {
          j += indexFinder(s.substr(i + j + 1));
        }
      }
      double instant = calculate(s.substr(i + 1, j), false);
      i = i + j;
      ans /= instant;
    } else if (s[i] == '^') {
      int j = 0;
      string character = s.substr(i + 1, 1);
      if (isInt(character)) {
        j = indexFinder(s.substr(i + 1));
      } else if (character == "-") {
        j = indexFinder(s.substr(i + 2)) + 1;
      } else {
        j = secondParentheseFinder(s.substr(i + 1)) + 2;
      }
      if (shouldFirstNumberBeNegative) {
        ans *= -1;
      }
      double exponent = calculate(s.substr(i + 1, j), false);
      i = i + j;
      ans = pow(ans, exponent);
    } else if (s[i] == '(') {
      if (i == 0) {
        int k = secondParentheseFinder(s.substr(i));
        ans = calculate(s.substr(i + 1, k), false);
        if (shouldFirstNumberBeNegative) {
          ans *= -1;
        }
        i = k + 1;
      } else {
        if (i == 3) {
          string fun = s.substr(0, 3);
          if (fun == "tan") {
            int k = secondParentheseFinder(s.substr(i));
            ans = tan(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              ans *= -1;
            }
            i = i + k + 1;
          } else if (fun == "cos") {
            int k = secondParentheseFinder(s.substr(i));
            ans = cos(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              ans *= -1;
            }
            i = i + k + 1;
          } else if (fun == "sin") {
            int k = secondParentheseFinder(s.substr(i));
            ans = sin(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              ans *= -1;
            }
            i = i + k + 1;
          }

        } else if (i == 4) {

          string fun = s.substr(0, 4);
          if (fun == "sqrt") {
            int k = secondParentheseFinder(s.substr(i));
            ans = sqrt(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              ans *= -1;
            }
            i = i + k + 1;
          } else if (fun == "atan") {
            int k = secondParentheseFinder(s.substr(i));
            ans = atan(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              ans *= -1;
            }
            i = i + k + 1;
          } else if (fun == "acos") {
            int k = secondParentheseFinder(s.substr(i));
            ans = acos(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              ans *= -1;
            }
            i = i + k + 1;
          } else if (fun == "asin") {
            int k = secondParentheseFinder(s.substr(i));
            ans = asin(calculate(s.substr(i + 1, k), false));
            if (shouldFirstNumberBeNegative) {
              ans *= -1;
            }
            i = i + k + 1;
          }
        }
      }
    } else {
      string character = s.substr(i, 1);
      if (isInt(character)) {
        bufferString += character;
        ans = stod(bufferString);
      } else if (character == ".") {
        bufferString += character;
      }
    }
  }
  if (shouldFirstNumberBeNegative) {
    ans *= -1;
  }
  return ans;
}

int main(int argc, char *argv[]) {

  cout << "Answer is: " << calculate(argv[1], false) << endl;
  return 0;
}
