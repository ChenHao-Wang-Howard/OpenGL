# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\RTX2070\source\repos\OpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\RTX2070\source\repos\OpenGL\build

# Include any dependencies generated for this target.
include CMakeFiles/Hello_Triangle.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Hello_Triangle.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Hello_Triangle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Hello_Triangle.dir/flags.make

CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.obj: CMakeFiles/Hello_Triangle.dir/flags.make
CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.obj: CMakeFiles/Hello_Triangle.dir/includes_CXX.rsp
CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.obj: C:/Users/RTX2070/source/repos/OpenGL/src/Hello_Triangle/main.cpp
CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.obj: CMakeFiles/Hello_Triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\RTX2070\source\repos\OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.obj -MF CMakeFiles\Hello_Triangle.dir\src\Hello_Triangle\main.cpp.obj.d -o CMakeFiles\Hello_Triangle.dir\src\Hello_Triangle\main.cpp.obj -c C:\Users\RTX2070\source\repos\OpenGL\src\Hello_Triangle\main.cpp

CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\RTX2070\source\repos\OpenGL\src\Hello_Triangle\main.cpp > CMakeFiles\Hello_Triangle.dir\src\Hello_Triangle\main.cpp.i

CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\RTX2070\source\repos\OpenGL\src\Hello_Triangle\main.cpp -o CMakeFiles\Hello_Triangle.dir\src\Hello_Triangle\main.cpp.s

CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.obj: CMakeFiles/Hello_Triangle.dir/flags.make
CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.obj: CMakeFiles/Hello_Triangle.dir/includes_C.rsp
CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.obj: C:/Users/RTX2070/source/repos/OpenGL/external/glad/src/glad.c
CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.obj: CMakeFiles/Hello_Triangle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\RTX2070\source\repos\OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.obj -MF CMakeFiles\Hello_Triangle.dir\external\glad\src\glad.c.obj.d -o CMakeFiles\Hello_Triangle.dir\external\glad\src\glad.c.obj -c C:\Users\RTX2070\source\repos\OpenGL\external\glad\src\glad.c

CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\RTX2070\source\repos\OpenGL\external\glad\src\glad.c > CMakeFiles\Hello_Triangle.dir\external\glad\src\glad.c.i

CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\RTX2070\source\repos\OpenGL\external\glad\src\glad.c -o CMakeFiles\Hello_Triangle.dir\external\glad\src\glad.c.s

# Object files for target Hello_Triangle
Hello_Triangle_OBJECTS = \
"CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.obj" \
"CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.obj"

# External object files for target Hello_Triangle
Hello_Triangle_EXTERNAL_OBJECTS =

Hello_Triangle.exe: CMakeFiles/Hello_Triangle.dir/src/Hello_Triangle/main.cpp.obj
Hello_Triangle.exe: CMakeFiles/Hello_Triangle.dir/external/glad/src/glad.c.obj
Hello_Triangle.exe: CMakeFiles/Hello_Triangle.dir/build.make
Hello_Triangle.exe: external/glfw/src/libglfw3.a
Hello_Triangle.exe: CMakeFiles/Hello_Triangle.dir/linkLibs.rsp
Hello_Triangle.exe: CMakeFiles/Hello_Triangle.dir/objects1.rsp
Hello_Triangle.exe: CMakeFiles/Hello_Triangle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\RTX2070\source\repos\OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Hello_Triangle.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Hello_Triangle.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Hello_Triangle.dir/build: Hello_Triangle.exe
.PHONY : CMakeFiles/Hello_Triangle.dir/build

CMakeFiles/Hello_Triangle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Hello_Triangle.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Hello_Triangle.dir/clean

CMakeFiles/Hello_Triangle.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\RTX2070\source\repos\OpenGL C:\Users\RTX2070\source\repos\OpenGL C:\Users\RTX2070\source\repos\OpenGL\build C:\Users\RTX2070\source\repos\OpenGL\build C:\Users\RTX2070\source\repos\OpenGL\build\CMakeFiles\Hello_Triangle.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Hello_Triangle.dir/depend

