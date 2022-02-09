#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace problems {
namespace {
// https://leetcode.com/problems/longest-valid-parentheses/
int LongestValidParentheses(const std::string& parentheses) {
  int level = 0;
  int right_index = -1;
  std::vector<int> begins, ends;
  for (int i = 0; i < parentheses.size(); i++) {
    const auto& ch = parentheses[i];
    if (level == 0 && ch == ')') {
      // ingore right parenthesis
      continue;
    }
    if (ch == '(') {
      level++;
      begins.push_back(i);
      ends.push_back(-1);
      right_index = ends.size() - 1;
    } else {
      level--;
      ends[right_index] = i;
      right_index--;
      while (true) {
        if (begins.size() > 1 && begins.back() == ends[ends.size() - 2] + 1) {
          begins.resize(begins.size() - 1);
          ends[ends.size() - 2] = ends.back();
          ends.resize(ends.size() - 1);
          right_index = ends.size() - 2;
        } else if (begins.size() > 1 && ends.back() < ends[ends.size() - 2]) {
          begins.resize(begins.size() - 1);
          ends.resize(ends.size() - 1);
          right_index = ends.size() - 2;
        } else {
          break;
        }
      }
    }
  }
  int max_len = 0;
  for (int i = 0; i < begins.size(); i++) {
    if (ends[i] < 0) {
      continue;
    }
    const int len = ends[i] - begins[i] + 1;
    if (len > max_len) {
      max_len = len;
    }
  }
  return max_len;
}

int LongestValidParenthesesV2(const std::string& parentheses) {
  int max_len = 0;
  std::stack<int> stack;
  stack.push(-1);
  for (int i = 0; i < parentheses.size(); i++) {
    const auto& ch = parentheses[i];
    if (ch == '(') {
      stack.push(i);
    } else {
      stack.pop();
      if (stack.empty()) {
        stack.push(i);
      }
      const int len = i - stack.top();
      if (len > max_len) {
        max_len = len;
      }
    }
  }
  return max_len;
}

}  // namespace

TEST(LongestValidParenthesesTest, LongestValidParentheses) {
  EXPECT_EQ(LongestValidParentheses(""), 0);
  EXPECT_EQ(LongestValidParentheses("(()"), 2);
  EXPECT_EQ(LongestValidParentheses(")()())"), 4);
  EXPECT_EQ(LongestValidParentheses("()(())"), 6);
  EXPECT_EQ(LongestValidParentheses(")((()()"), 4);
  EXPECT_EQ(LongestValidParentheses(")((()())()())"), 12);
  EXPECT_EQ(LongestValidParentheses(")((()()()())"), 10);
  EXPECT_EQ(LongestValidParentheses(")((((()))))"), 10);
}

TEST(LongestValidParenthesesTest, LongestValidParenthesesV2) {
  EXPECT_EQ(LongestValidParenthesesV2("))))"), 0);
  EXPECT_EQ(LongestValidParenthesesV2("(()"), 2);
  EXPECT_EQ(LongestValidParenthesesV2(")()())"), 4);
  EXPECT_EQ(LongestValidParenthesesV2("()(())"), 6);
  EXPECT_EQ(LongestValidParenthesesV2(")((()()"), 4);
  EXPECT_EQ(LongestValidParenthesesV2(")((()())()())"), 12);
  EXPECT_EQ(LongestValidParenthesesV2(")((()()()())"), 10);
  EXPECT_EQ(LongestValidParenthesesV2(")((((()))))"), 10);
}
}  // namespace problems
