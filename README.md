template common
================

some useful utils for C++.

CMake:
```cmake
# if need mathlib
# find_library(quadmath NAMES quadmath.a)
target_link_libraries(project template_common)
```

compile (with test)
```bash
mkdir build && cd build;
cmake -DTEMPLATE_COMMON_TEST=ON ..;
make
```

Test:
```bash
./test/test_mathlib
./test/test_type_identity
```
