set(CMAKE_C_COMPILER "mysys64/mingw64/bin/gcc")

project(graphing_calculator)
add_executable(graphing_calculator -c -DBUILD dll.c)
add_executable(graphing_calculator main.c)
add_executable(python line.py)
