#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace problems {
namespace {

int GetNumber(const int value) {
  for (int i = 1; i < 10; i++) {
    if (0x3ff == (value | (1 << i))) {
      return i;
    }
  }
  return 0;
}

// https://leetcode.com/problems/sudoku-solver/
std::vector<std::vector<int>> SudokuSolver(
    const std::vector<std::vector<int>>& sudoku) {
  std::vector<std::vector<int>> result = sudoku;
  std::unordered_map<int, int> candidates;
  // row
  for (int i = 0; i < 9; i++) {
    const auto& row = sudoku[i];
    int num_bit = 0;
    for (int j = 0; j < 9; j++) {
      num_bit |= (1 << row[j]);
    }
    for (int j = 0; j < 9; j++) {
      if (row[j] == 0) {
        candidates[i * 9 + j] |= num_bit;
      }
    }
  }
  // col
  for (int j = 0; j < 9; j++) {
    int num_bit = 0;
    for (int i = 0; i < 9; i++) {
      num_bit |= (1 << sudoku[i][j]);
    }
    for (int i = 0; i < 9; i++) {
      if (sudoku[i][j] == 0) {
        candidates[i * 9 + j] |= num_bit;
      }
    }
  }
  // block
  for (int i = 0; i < 9; i++) {
    int num_bit = 0;
    for (int j = 0; j < 9; j++) {
      int row = (i / 3) * 3 + j / 3;
      int col = (i * 3) % 9 + j % 3;
      num_bit |= (1 << sudoku[row][col]);
    }
    for (int j = 0; j < 9; j++) {
      int row = (i / 3) * 3 + j / 3;
      int col = (i * 3) % 9 + j % 3;
      if (sudoku[row][col] == 0) {
        candidates[row * 9 + col] |= num_bit;
      }
    }
  }

  std::unordered_map<int, int> fill_number;
  while (candidates.size() != fill_number.size()) {
    bool find = false;
    for (const auto& pair : candidates) {
      if (pair.second == 0x3ff) {
        continue;
      }
      const int num = GetNumber(pair.second);
      if (num == 0) {
        continue;
      }
      int row = pair.first / 9;
      int col = pair.first % 9;
      int block_offset = (row / 3) * 3 * 9 + (col / 3) * 3;
      for (int i = 0; i < 9; i++) {
        int row_index = row * 9 + i;
        int col_index = i * 9 + col;
        int block_index = block_offset + (i / 3) * 9 + i % 3;
        if (candidates.find(row_index) != candidates.end()) {
          candidates[row_index] |= (1 << num);
        }
        if (candidates.find(col_index) != candidates.end()) {
          candidates[col_index] |= (1 << num);
        }
        if (candidates.find(block_index) != candidates.end()) {
          candidates[block_index] |= (1 << num);
        }
      }
      fill_number[pair.first] = num;
      find = true;
      break;
    }
    if (!find) {
      break;
    }
  }
  for (const auto& pair : fill_number) {
    int row = pair.first / 9;
    int col = pair.first % 9;
    result[row][col] = pair.second;
  }
  return result;
}
}  // namespace

TEST(SudokuSolverTest, SudokuSolver) {
  const std::vector<std::vector<int>> sudoku{
      {5, 3, 0, 0, 7, 0, 0, 0, 0}, {6, 0, 0, 1, 9, 5, 0, 0, 0},
      {0, 9, 8, 0, 0, 0, 0, 6, 0}, {8, 0, 0, 0, 6, 0, 0, 0, 3},
      {4, 0, 0, 8, 0, 3, 0, 0, 1}, {7, 0, 0, 0, 2, 0, 0, 0, 6},
      {0, 6, 0, 0, 0, 0, 2, 8, 0}, {0, 0, 0, 4, 1, 9, 0, 0, 5},
      {0, 0, 0, 0, 8, 0, 0, 7, 9}};

  const std::vector<std::vector<int>> want_sudoku{
      {5, 3, 4, 6, 7, 8, 9, 1, 2}, {6, 7, 2, 1, 9, 5, 3, 4, 8},
      {1, 9, 8, 3, 4, 2, 5, 6, 7}, {8, 5, 9, 7, 6, 1, 4, 2, 3},
      {4, 2, 6, 8, 5, 3, 7, 9, 1}, {7, 1, 3, 9, 2, 4, 8, 5, 6},
      {9, 6, 1, 5, 3, 7, 2, 8, 4}, {2, 8, 7, 4, 1, 9, 6, 3, 5},
      {3, 4, 5, 2, 8, 6, 1, 7, 9}};

  EXPECT_EQ(SudokuSolver(sudoku), want_sudoku);
}
}  // namespace problems
