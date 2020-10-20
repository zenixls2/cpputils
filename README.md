CPP UTILS
================

some useful utils for C++.

CMake:
```cmake
# if need mathlib
# find_library(quadmath NAMES quadmath.a)
target_link_libraries(project cpputils)
```

compile (with test)
```bash
mkdir build && cd build;
cmake -DCPPUTILS_TEST=ON ..;
make
```

Test:
```bash
./test/test_mathlib
./test/test_type_identity
```
