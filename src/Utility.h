#ifndef UTILITY_H
#define UTILITY_H

#include <string>

class Utility {

public:
  // This function finds the last index of the current math expression
  static int expressionLastIndexFinder(std::string s);

  // This function finds the amount of characters left before The closing
  // parenthesis
  static int closingParenthesisFinder(std::string s);

  // This function finds the  amount of characters left before the opening
  // parenthesis
  static int openingParenthesisFinder(std::string s);

  // This function checks if a character is an int by making use of "stoi()"
  static bool isInt(std::string c);
};

#endif // !UTILITY_H
