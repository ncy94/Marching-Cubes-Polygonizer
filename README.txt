## Build

This program use cmake to build. Open an console, change to the top directory of this project, and try building with cmake like with the following lines:

```
cmake -H. -Btmp_cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
cmake --build tmp_cmake --clean-first --target install
```

## executables

There are two executables that will generate after it's built successfully:
- generate_mesh: This executable takes point cloud from standard input stream, and generate mesh in OFF format to standard output stream. The input format is very simple: each line represents the x,y,z coordinates of each point. One example could be shown as below:
0.1 0.2 0.3
0.4 0.5 0.6

- generate_random_point_cloud: This executable generates a random point cloud to standard output stream. The purpose of this executable is to provide random test cases for the other executable.
this executable takes options from console. for example, the following line in console:
```
./generate_random_point_cloud -n 1000 -m 1
```
means that this program will generate 1000 random points, with the max absolute value of each coordinates 1. If no options are provided, however, these two parameters will be set to 1000 and 1, as default paramter.


## test cases

A test case is provided. It is a xyz file which contains the point cloud in the same format as this project. A script demo is provided to run this program.

more test cases can be found at https://www.cc.gatech.edu/projects/large_models/