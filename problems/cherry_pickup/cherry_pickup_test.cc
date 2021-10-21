
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace problems {
namespace {
// https://leetcode.com/problems/cherry-pickup/
int CherryPickup(const std::vector<std::vector<int>>& grid) {
  if (grid.empty() || grid[0].empty()) {
    return 0;
  }
  const int m = grid.size();
  const int n = grid[0].size();
  std::vector<int> tmp;
  tmp.resize(n);
  std::vector<std::vector<int>> dp;
  dp.resize(n, tmp);
  std::vector<std::vector<int>> prev_dp = dp;
  for (int row = m - 1; row >= 0; row--) {
    for (int col1 = 0; col1 < n; col1++) {
      for (int col2 = 0; col2 < n; col2++) {
        const int result =
            grid[row][col1] + (col1 == col2 ? 0 : grid[row][col2]);
        if (row == m - 1) {
          // current row
          dp[col1][col2] = result;
          continue;
        }
        int max = 0;
        for (int new_col1 = col1 - 1; new_col1 <= col1 + 1; new_col1++) {
          for (int new_col2 = col2 - 1; new_col2 <= col2 + 1; new_col2++) {
            if (new_col1 < 0 || new_col1 >= n || new_col2 < 0 ||
                new_col2 >= n) {
              continue;
            }
            if (prev_dp[new_col1][new_col2] > max) {
              max = prev_dp[new_col1][new_col2];
            }
          }
        }
        dp[col1][col2] = max + result;
      }
    }
    prev_dp = dp;
  }
  return dp[0][n - 1];
}
}  // namespace

TEST(CherryPickupTest, CherryPickup) {
  std::vector<std::vector<int>> grid{{1, 0, 0, 0, 0, 0, 1},
                                     {2, 0, 0, 0, 0, 3, 0},
                                     {2, 0, 9, 0, 0, 0, 0},
                                     {0, 3, 0, 5, 4, 0, 0},
                                     {1, 0, 2, 3, 0, 0, 6}};
  EXPECT_EQ(CherryPickup(grid), 28);
}
}  // namespace problems
