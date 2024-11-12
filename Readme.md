The project uses the vcpkg and Ninja build system
You must install it before trying to build the project.
Also you must create a CMakeUserPresets.json, where you 
specify the pas to C++ compiler, C compiler, recourse compiler(because we use ninja), linker, and vcpkg folder.
Then you can execute the command:
1) cmake --preset=default
2) cmake --build build

Then in the Debug folder you will get the .exe, which you can use