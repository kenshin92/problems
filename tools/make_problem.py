import os
import sys

problem_basedir = "problems"

build_content_template = """package(default_visibility = ["//visibility:public"])

cc_test(
    name = "{problem_name}_test",
    srcs = ["{problem_name}_test.cc"],
    linkstatic = True,
    deps = ["@com_google_googletest//:gtest_main"],
)
"""

test_cc_content_template = """#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace problems {
namespace {
void {problem_name}() {}
}  // namespace

TEST({problem_name}Test, {problem_name}) { EXPECT_TRUE(true); }
}  // namespace problems
"""


def snake_case_to_camel_case(str):
  words = str.split('_')
  new_str = ""
  for w in words:
    new_str += w.capitalize()
  return new_str


def make_problem(problem_name):
  words = problem_name.lower().split()
  problem_name = '_'.join(words)
  dirname = os.path.join(problem_basedir, problem_name)
  if os.path.exists(dirname):
    print(f"{problem_name} already exists!")
    return
  os.makedirs(dirname)

  build_f = open(os.path.join(dirname, 'BUILD'), 'wt')
  build_f.write(build_content_template.replace('{problem_name}', problem_name))
  build_f.close()

  cc_test_file = os.path.join(dirname, problem_name + "_test.cc")
  test_f = open(cc_test_file, 'wt')
  test_f.write(
      test_cc_content_template.replace('{problem_name}',
                                       snake_case_to_camel_case(problem_name)))
  test_f.close()


if __name__ == '__main__':
  if len(sys.argv) != 2:
    print("Invalid arguments")
    print("Usage: %s problem_name" % sys.argv[0])
    exit(1)
  problem_name = sys.argv[1]
  make_problem(problem_name)
