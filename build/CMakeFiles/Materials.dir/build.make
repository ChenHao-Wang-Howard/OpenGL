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
include CMakeFiles/Materials.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Materials.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Materials.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Materials.dir/flags.make

CMakeFiles/Materials.dir/src/Materials/main.cpp.obj: CMakeFiles/Materials.dir/flags.make
CMakeFiles/Materials.dir/src/Materials/main.cpp.obj: CMakeFiles/Materials.dir/includes_CXX.rsp
CMakeFiles/Materials.dir/src/Materials/main.cpp.obj: C:/Users/RTX2070/source/repos/OpenGL/src/Materials/main.cpp
CMakeFiles/Materials.dir/src/Materials/main.cpp.obj: CMakeFiles/Materials.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\RTX2070\source\repos\OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Materials.dir/src/Materials/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Materials.dir/src/Materials/main.cpp.obj -MF CMakeFiles\Materials.dir\src\Materials\main.cpp.obj.d -o CMakeFiles\Materials.dir\src\Materials\main.cpp.obj -c C:\Users\RTX2070\source\repos\OpenGL\src\Materials\main.cpp

CMakeFiles/Materials.dir/src/Materials/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Materials.dir/src/Materials/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\RTX2070\source\repos\OpenGL\src\Materials\main.cpp > CMakeFiles\Materials.dir\src\Materials\main.cpp.i

CMakeFiles/Materials.dir/src/Materials/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Materials.dir/src/Materials/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\RTX2070\source\repos\OpenGL\src\Materials\main.cpp -o CMakeFiles\Materials.dir\src\Materials\main.cpp.s

CMakeFiles/Materials.dir/external/glad/src/glad.c.obj: CMakeFiles/Materials.dir/flags.make
CMakeFiles/Materials.dir/external/glad/src/glad.c.obj: CMakeFiles/Materials.dir/includes_C.rsp
CMakeFiles/Materials.dir/external/glad/src/glad.c.obj: C:/Users/RTX2070/source/repos/OpenGL/external/glad/src/glad.c
CMakeFiles/Materials.dir/external/glad/src/glad.c.obj: CMakeFiles/Materials.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\RTX2070\source\repos\OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Materials.dir/external/glad/src/glad.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Materials.dir/external/glad/src/glad.c.obj -MF CMakeFiles\Materials.dir\external\glad\src\glad.c.obj.d -o CMakeFiles\Materials.dir\external\glad\src\glad.c.obj -c C:\Users\RTX2070\source\repos\OpenGL\external\glad\src\glad.c

CMakeFiles/Materials.dir/external/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Materials.dir/external/glad/src/glad.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\RTX2070\source\repos\OpenGL\external\glad\src\glad.c > CMakeFiles\Materials.dir\external\glad\src\glad.c.i

CMakeFiles/Materials.dir/external/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Materials.dir/external/glad/src/glad.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\RTX2070\source\repos\OpenGL\external\glad\src\glad.c -o CMakeFiles\Materials.dir\external\glad\src\glad.c.s

# Object files for target Materials
Materials_OBJECTS = \
"CMakeFiles/Materials.dir/src/Materials/main.cpp.obj" \
"CMakeFiles/Materials.dir/external/glad/src/glad.c.obj"

# External object files for target Materials
Materials_EXTERNAL_OBJECTS =

Materials.exe: CMakeFiles/Materials.dir/src/Materials/main.cpp.obj
Materials.exe: CMakeFiles/Materials.dir/external/glad/src/glad.c.obj
Materials.exe: CMakeFiles/Materials.dir/build.make
Materials.exe: external/glfw/src/libglfw3.a
Materials.exe: CMakeFiles/Materials.dir/linkLibs.rsp
Materials.exe: CMakeFiles/Materials.dir/objects1.rsp
Materials.exe: CMakeFiles/Materials.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\RTX2070\source\repos\OpenGL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Materials.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Materials.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Materials.dir/build: Materials.exe
.PHONY : CMakeFiles/Materials.dir/build

CMakeFiles/Materials.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Materials.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Materials.dir/clean

CMakeFiles/Materials.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\RTX2070\source\repos\OpenGL C:\Users\RTX2070\source\repos\OpenGL C:\Users\RTX2070\source\repos\OpenGL\build C:\Users\RTX2070\source\repos\OpenGL\build C:\Users\RTX2070\source\repos\OpenGL\build\CMakeFiles\Materials.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Materials.dir/depend

