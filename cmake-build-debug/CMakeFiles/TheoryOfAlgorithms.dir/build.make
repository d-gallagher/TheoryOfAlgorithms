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
CMAKE_SOURCE_DIR = C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\TheoryOfAlgorithms.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\TheoryOfAlgorithms.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\TheoryOfAlgorithms.dir\flags.make

CMakeFiles\TheoryOfAlgorithms.dir\lookatbits.c.obj: CMakeFiles\TheoryOfAlgorithms.dir\flags.make
CMakeFiles\TheoryOfAlgorithms.dir\lookatbits.c.obj: ..\lookatbits.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TheoryOfAlgorithms.dir/lookatbits.c.obj"
	C:\PROGRA~2\MICROS~1\2019\Preview\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\TheoryOfAlgorithms.dir\lookatbits.c.obj /FdCMakeFiles\TheoryOfAlgorithms.dir\ /FS -c C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\lookatbits.c
<<

CMakeFiles\TheoryOfAlgorithms.dir\lookatbits.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TheoryOfAlgorithms.dir/lookatbits.c.i"
	C:\PROGRA~2\MICROS~1\2019\Preview\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe > CMakeFiles\TheoryOfAlgorithms.dir\lookatbits.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\lookatbits.c
<<

CMakeFiles\TheoryOfAlgorithms.dir\lookatbits.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TheoryOfAlgorithms.dir/lookatbits.c.s"
	C:\PROGRA~2\MICROS~1\2019\Preview\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\TheoryOfAlgorithms.dir\lookatbits.c.s /c C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\lookatbits.c
<<

# Object files for target TheoryOfAlgorithms
TheoryOfAlgorithms_OBJECTS = \
"CMakeFiles\TheoryOfAlgorithms.dir\lookatbits.c.obj"

# External object files for target TheoryOfAlgorithms
TheoryOfAlgorithms_EXTERNAL_OBJECTS =

TheoryOfAlgorithms.exe: CMakeFiles\TheoryOfAlgorithms.dir\lookatbits.c.obj
TheoryOfAlgorithms.exe: CMakeFiles\TheoryOfAlgorithms.dir\build.make
TheoryOfAlgorithms.exe: CMakeFiles\TheoryOfAlgorithms.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable TheoryOfAlgorithms.exe"
	"C:\Program Files\JetBrains\CLion-2019.3.2.win\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\TheoryOfAlgorithms.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\Preview\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\TheoryOfAlgorithms.dir\objects1.rsp @<<
 /out:TheoryOfAlgorithms.exe /implib:TheoryOfAlgorithms.lib /pdb:C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\cmake-build-debug\TheoryOfAlgorithms.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\TheoryOfAlgorithms.dir\build: TheoryOfAlgorithms.exe

.PHONY : CMakeFiles\TheoryOfAlgorithms.dir\build

CMakeFiles\TheoryOfAlgorithms.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TheoryOfAlgorithms.dir\cmake_clean.cmake
.PHONY : CMakeFiles\TheoryOfAlgorithms.dir\clean

CMakeFiles\TheoryOfAlgorithms.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\cmake-build-debug C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\cmake-build-debug C:\Users\jibis\Documents\College\ToA\TheoryOfAlgorithms\cmake-build-debug\CMakeFiles\TheoryOfAlgorithms.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\TheoryOfAlgorithms.dir\depend

