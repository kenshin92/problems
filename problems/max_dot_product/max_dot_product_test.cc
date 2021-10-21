
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace problems {
namespace {
// https://leetcode.com/problems/max-dot-product-of-two-subsequences/
int MaxDotProduct(const std::vector<int>& nums1,
                  const std::vector<int>& nums2) {
  std::vector<int> row;
  row.resize(nums2.size());
  std::vector<std::vector<int>> matrix;
  matrix.resize(nums1.size(), row);
  matrix[0][0] = nums1[0] * nums2[0];
  for (int i = 1; i < nums1.size(); i++) {
    matrix[i][0] = std::max(nums1[i] * nums2[0], matrix[i - 1][0]);
  }
  for (int i = 1; i < nums2.size(); i++) {
    matrix[0][i] = std::max(nums1[0] * nums2[i], matrix[0][i - 1]);
  }
  int max_dot_product = 0;
  for (int i = 1; i < nums1.size(); i++) {
    for (int j = 1; j < nums2.size(); j++) {
      const int old_value = matrix[i - 1][j - 1];
      const int new_value = nums1[i] * nums2[j];
      const int value =
          std::max(old_value + (new_value > 0 ? new_value : 0), new_value);
      const int max_value = std::max(matrix[i][j - 1], matrix[i - 1][j]);
      max_dot_product = std::max(value, max_value);
      matrix[i][j] = max_dot_product;
    }
  }
  return max_dot_product;
}
}  // namespace

TEST(MaxDotProductTest, MaxDotProduct) {
  EXPECT_EQ(MaxDotProduct({2, 1, -2, 5}, {3, 0, -6}), 18);
  EXPECT_EQ(MaxDotProduct({-5, 3, -5, -3, 1}, {-2, 4, 2, 5, -5}), 50);
  EXPECT_EQ(MaxDotProduct({-3, -8, 3, -10, 1, 3, 9},
                          {9, 2, 3, 7, -9, 1, -8, 5, -1, -1}),
            200);
}
}  // namespace problems
