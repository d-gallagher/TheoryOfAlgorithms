# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion-2019.3.2.win\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion-2019.3.2.win\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\UnionsInSHA256.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\UnionsInSHA256.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\UnionsInSHA256.dir\flags.make

CMakeFiles\UnionsInSHA256.dir\unions.c.obj: CMakeFiles\UnionsInSHA256.dir\flags.make
CMakeFiles\UnionsInSHA256.dir\unions.c.obj: ..\unions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/UnionsInSHA256.dir/unions.c.obj"
	C:\PROGRA~2\MICROS~1\2019\Preview\VC\Tools\MSVC\1425~1.285\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\UnionsInSHA256.dir\unions.c.obj /FdCMakeFiles\UnionsInSHA256.dir\ /FS -c C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256\unions.c
<<

CMakeFiles\UnionsInSHA256.dir\unions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnionsInSHA256.dir/unions.c.i"
	C:\PROGRA~2\MICROS~1\2019\Preview\VC\Tools\MSVC\1425~1.285\bin\Hostx86\x86\cl.exe > CMakeFiles\UnionsInSHA256.dir\unions.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256\unions.c
<<

CMakeFiles\UnionsInSHA256.dir\unions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnionsInSHA256.dir/unions.c.s"
	C:\PROGRA~2\MICROS~1\2019\Preview\VC\Tools\MSVC\1425~1.285\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\UnionsInSHA256.dir\unions.c.s /c C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256\unions.c
<<

# Object files for target UnionsInSHA256
UnionsInSHA256_OBJECTS = \
"CMakeFiles\UnionsInSHA256.dir\unions.c.obj"

# External object files for target UnionsInSHA256
UnionsInSHA256_EXTERNAL_OBJECTS =

UnionsInSHA256.exe: CMakeFiles\UnionsInSHA256.dir\unions.c.obj
UnionsInSHA256.exe: CMakeFiles\UnionsInSHA256.dir\build.make
UnionsInSHA256.exe: CMakeFiles\UnionsInSHA256.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable UnionsInSHA256.exe"
	"C:\Program Files\JetBrains\CLion-2019.3.2.win\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\UnionsInSHA256.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\Preview\VC\Tools\MSVC\1425~1.285\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\UnionsInSHA256.dir\objects1.rsp @<<
 /out:UnionsInSHA256.exe /implib:UnionsInSHA256.lib /pdb:C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256\cmake-build-debug\UnionsInSHA256.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\UnionsInSHA256.dir\build: UnionsInSHA256.exe

.PHONY : CMakeFiles\UnionsInSHA256.dir\build

CMakeFiles\UnionsInSHA256.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\UnionsInSHA256.dir\cmake_clean.cmake
.PHONY : CMakeFiles\UnionsInSHA256.dir\clean

CMakeFiles\UnionsInSHA256.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256 C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256 C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256\cmake-build-debug C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256\cmake-build-debug C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\UnionsInSHA256\cmake-build-debug\CMakeFiles\UnionsInSHA256.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\UnionsInSHA256.dir\depend
