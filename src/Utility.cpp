#include "Utility.h"
#include <cctype>
#include <stdexcept>

int Utility::findLastIndexExpression(std::string s) {
  int index = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '(') {
      int k = closingParenthesisFinder(s.substr(i)) + 1;
      index += k + 1;
      i += k;
      if (i < (s.length() - 1)) {
        k = firstCharacterIndexFinder(s.substr(i + 1));
        i += k;
        if (s[i + 1] != '^') {
          index += k;
          return index;
        }
      }
    } else if (isdigit(s[i])) {
      index++;
      if (i < (s.length() - 1)) {
        int k = firstCharacterIndexFinder(s.substr(i + 1));
        i += k;
        if (s[i + 1] != '^' && !isdigit(s[i + 1])) {
          index += k;
          return index;
        }
      }
    } else {
      index++;
    }
  }

  return index;
}

int Utility::firstCharacterIndexFinder(std::string s) {
  int i = 0;
  while (i < s.length() && s[i] == ' ') {
    i++;
  }
  return i;
}

int Utility::openingParenthesisFinder(std::string s) {
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

int Utility::expressionLastIndexFinder(std::string s) {
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

int Utility::closingParenthesisFinder(std::string s) {
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
    throw std::invalid_argument(
        "Invalid expression: Every opening parenthesis '(' must be paired "
        "with "
        "a corresponding closing parenthesis ')'. Please ensure that all "
        "parentheses are properly closed and matched");
  }
  return index - 1;
}

bool Utility::isInt(std::string c) {
  try {
    int var = stoi(c);
    return true;
  } catch (const std::invalid_argument &) {
    return false;
  }
}
