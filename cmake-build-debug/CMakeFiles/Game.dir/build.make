﻿# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\School\7th_semester\Graphics\Assignments\BasicEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\School\7th_semester\Graphics\Assignments\BasicEngine\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\Game.dir\depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles\Game.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\Game.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Game.dir\flags.make

CMakeFiles\Game.dir\Game\game.cpp.obj: CMakeFiles\Game.dir\flags.make
CMakeFiles\Game.dir\Game\game.cpp.obj: ..\Game\game.cpp
CMakeFiles\Game.dir\Game\game.cpp.obj: CMakeFiles\Game.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\School\7th_semester\Graphics\Assignments\BasicEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Game.dir/Game/game.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\Game.dir\Game\game.cpp.obj.d --working-dir=D:\School\7th_semester\Graphics\Assignments\BasicEngine\cmake-build-debug --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2017\PROFES~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\Game.dir\Game\game.cpp.obj /FdCMakeFiles\Game.dir\ /FS -c D:\School\7th_semester\Graphics\Assignments\BasicEngine\Game\game.cpp
<<

CMakeFiles\Game.dir\Game\game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game.dir/Game/game.cpp.i"
	C:\PROGRA~2\MICROS~2\2017\PROFES~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\Game.dir\Game\game.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\School\7th_semester\Graphics\Assignments\BasicEngine\Game\game.cpp
<<

CMakeFiles\Game.dir\Game\game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game.dir/Game/game.cpp.s"
	C:\PROGRA~2\MICROS~2\2017\PROFES~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Game.dir\Game\game.cpp.s /c D:\School\7th_semester\Graphics\Assignments\BasicEngine\Game\game.cpp
<<

CMakeFiles\Game.dir\Game\main.cpp.obj: CMakeFiles\Game.dir\flags.make
CMakeFiles\Game.dir\Game\main.cpp.obj: ..\Game\main.cpp
CMakeFiles\Game.dir\Game\main.cpp.obj: CMakeFiles\Game.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\School\7th_semester\Graphics\Assignments\BasicEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Game.dir/Game/main.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\Game.dir\Game\main.cpp.obj.d --working-dir=D:\School\7th_semester\Graphics\Assignments\BasicEngine\cmake-build-debug --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~2\2017\PROFES~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\Game.dir\Game\main.cpp.obj /FdCMakeFiles\Game.dir\ /FS -c D:\School\7th_semester\Graphics\Assignments\BasicEngine\Game\main.cpp
<<

CMakeFiles\Game.dir\Game\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game.dir/Game/main.cpp.i"
	C:\PROGRA~2\MICROS~2\2017\PROFES~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe > CMakeFiles\Game.dir\Game\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\School\7th_semester\Graphics\Assignments\BasicEngine\Game\main.cpp
<<

CMakeFiles\Game.dir\Game\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game.dir/Game/main.cpp.s"
	C:\PROGRA~2\MICROS~2\2017\PROFES~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Game.dir\Game\main.cpp.s /c D:\School\7th_semester\Graphics\Assignments\BasicEngine\Game\main.cpp
<<

# Object files for target Game
Game_OBJECTS = \
"CMakeFiles\Game.dir\Game\game.cpp.obj" \
"CMakeFiles\Game.dir\Game\main.cpp.obj"

# External object files for target Game
Game_EXTERNAL_OBJECTS =

Game.exe: CMakeFiles\Game.dir\Game\game.cpp.obj
Game.exe: CMakeFiles\Game.dir\Game\main.cpp.obj
Game.exe: CMakeFiles\Game.dir\build.make
Game.exe: Engine.lib
Game.exe: Display.lib
Game.exe: res\includes\glfw\src\glfw3.lib
Game.exe: res\includes\glad\glad.lib
Game.exe: CMakeFiles\Game.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\School\7th_semester\Graphics\Assignments\BasicEngine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Game.exe"
	"C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Game.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~2\2017\PROFES~1\VC\Tools\MSVC\1416~1.270\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Game.dir\objects1.rsp @<<
 /out:Game.exe /implib:Game.lib /pdb:D:\School\7th_semester\Graphics\Assignments\BasicEngine\cmake-build-debug\Game.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  Engine.lib Display.lib res\includes\glfw\src\glfw3.lib res\includes\glad\glad.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Game.dir\build: Game.exe
.PHONY : CMakeFiles\Game.dir\build

CMakeFiles\Game.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Game.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Game.dir\clean

CMakeFiles\Game.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\School\7th_semester\Graphics\Assignments\BasicEngine D:\School\7th_semester\Graphics\Assignments\BasicEngine D:\School\7th_semester\Graphics\Assignments\BasicEngine\cmake-build-debug D:\School\7th_semester\Graphics\Assignments\BasicEngine\cmake-build-debug D:\School\7th_semester\Graphics\Assignments\BasicEngine\cmake-build-debug\CMakeFiles\Game.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Game.dir\depend

