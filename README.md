If the output from running cmake appears to have picked up the wrong ROOT install, try manually adding the path to the FindROOT.cmake file in your ROOT install to CMAKE_MODULE_PATH like so -DCMAKE_MODULE_PATH=${ROOTSYS}/etc/cmake. This shouldn't be a problem for more recent versions of ROOT6 where the ROOT developers have taken care to expose modern, conventional CMake.