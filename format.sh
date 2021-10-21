# Format all BUILD files.
#
# You need to install buildifier, c.f.,
# https://github.com/bazelbuild/buildtools/tree/master/buildifier
buildifier WORKSPACE
# [field] = [
#    "//path/to/foo:bar",
# ],
# -->
# [field] = ["//path/to/foo:bar"],
find . -not -path './bazel-*' -name BUILD | xargs sed -i -r ':a;N;$!ba; s/= \[\n[ ]+([^,]*),\n[ ]+\],/= [\1],/g'
find . -not -path './bazel-*' -name BUILD | xargs buildifier
find . -not -path './bazel-*' -name *.bzl | xargs buildifier

# Format C, C++ and proto files.
#
# You need to install clang-format, c.f.,
# https://clang.llvm.org/docs/ClangFormat.html
find . -not -path './bazel-*' -name '*.proto' | xargs clang-format -i
find . -not -path './bazel-*' -name '*.h' | xargs clang-format -i
find . -not -path './bazel-*' -name '*.hpp' | xargs clang-format -i
find . -not -path './bazel-*' -name '*.c' | xargs clang-format -i
find . -not -path './bazel-*' -name '*.cc' | xargs clang-format -i
find . -not -path './bazel-*' -name '*.cpp' | xargs clang-format -i

# Format jsonnet files.
find . -not -path './bazel-*' -name "*.jsonnet" | xargs -n 1 jsonnetfmt -i

# Fix all python files.
#
# You need to install yapf, c.f., https://github.com/google/yapf
yapf -ir .
