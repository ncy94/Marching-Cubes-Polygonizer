## Introduction

Marching cubes is a computer graphics algorithm that extracts a polygonal mesh of an isosurface from an 3D space. First proposed in 1987, this algorithm has had numerous applications in computer graphics, such as medical visualization, physics simulation. The algorithm itself is quite intuitive thus easy to implement. In this project, I will use C++ to implement the algorithm which takes a set of points and outputs a polygonal mesh. I will use GLM library to represent the points, and use a share vertex representation as the data structure of mesh, and output the extracted mesh to an obj file.


## Build

This program use cmake to build. Open an console, change to the top directory of this project, and try building with cmake like with the following lines:

```
cmake -H. -Btmp_cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
cmake --build tmp_cmake --clean-first --target install
```

## Dependencies
This project only uses GLM, which is a header-only library. For conviveince, I included glm library in this project too, so that you can build the project from scratch.

## Input and Output

The program is command-line based and has no graphical user interface. Two executables are provided, the names are: `generate_mesh` and `generate_random_point_cloud`.

The first executable `generate_mesh` reads point cloud (the format of which is specified below) from standard input stream, and output the mesh to standard output stream in OFF <sup>[1](#madams)</sup> format. After the point cloud is fed to input stream, the program will immediately start extracting the mesh. The time of the mesh extracting process varies depends on the size of the point cloud. Unless an error occurs, in which case the program will throw a standard exception, the program will continue until the mesh is written into the output stream. Then the the program terminates.

The second executable `generate_random_point_cloud` takes two parameters from command line option. The first parameter followed by command line option `-n` means the number of points to be generated. The second parameter followed by command line option `-m` means the maximum absolute value of the x,y,z coordinate of each point. The default values of the input parameters are 1000 1. An example of the input format in the command line is shown below:
```
./generate_random_point_cloud -n 1000 -m 1
```
This executable `generate_random_point_cloud` output a point cloud to standard output stream, in the same format as the input point cloud of `generate_mesh`. This executable provides the user with a random generated point cloud to test the algorithm without having to prepare a point cloud themselves.

The input format is specified as this: Each line has three numbers separated by a single space, which represents the X, Y and Z coordinate of that point. An example of the first three lines from the stanford bunny is shown as follows: 
```
-0.037830 0.127940 0.004475 
-0.044779 0.128887 0.001905 
-0.068010 0.151244 0.037195 
```

The mesh output from the program is in OFF format. 


## test cases

A test case is provided. It is a xyz file which contains the point cloud in the same format as this project. A script demo is provided to run this program.

more test cases can be found at https://www.cc.gatech.edu/projects/large_models/

## related work
Marching cubes was developed by William E.Lorensen and Harvey E. Cline<sup>[2](#Lorenson)</sup> in 1987, published in SIGGRAPH. The application was to visualize data from CT and MRI devices. The first published version built the look up table with the most fundamental 15 unique cases. The work achieved great performance except for some minor setbacks. Because of some interpolation ambiguities, the mesh that was extracted shows some discontinuities and topological faults. Nevertheless, it had been the most practical way to extract a polygonal mesh over the years.

Afterwards, with Marching cubes applied and studied by numerous researchers and engineers, The algorithm has been improved greatly. Durst<sup>[3](#Durst)</sup> in 1988 firstly noted that the original look up table was not complete, which allowed for multiple triangulations in certain cases. In 1991, Nielson and Hamann<sup>[4](#Neil)</sup> discovered the existence of some interpolation ambiguities on the face of the cube. They proposed a test called Asymptotic Decider to check the correctness of the cube faces. This problem was further put forward by Natarajan<sup>[5](#Natarajan1994)</sup> in 1994, which added four new cases to the look up table. Until this time, although revised and improved multiple times, the algorithm was still not perfect.

In 1995, Chernyaev<sup>[6](#che)</sup> proposed the Marching Cubes 33, which is one of the first iossurface extraction algorithms that preserved the topology of the trilinear interpolant. He extended the cases to 33 which fixed the interior ambiguities. This algorithm was later proved by Nielson to be complete.

## Problem Statement
To elaborate the Marching cubes algorithm, each voxel has eight vertices, and each vertex is marked with a boolean value: which indicated if the vertex is inside or outside the object. So, theoretically, each voxel holds `2^8 = 256` cases, which sounds like a lot of work to do. Luckily, it was discovered that a total of 15 cases could contour the surface in most cases, as shown below. 

![](https://www.researchgate.net/profile/Howard_Hamilton/publication/228454597/figure/fig2/AS:301996478353409@1449012979196/Look-up-table-for-the-Marching-Cubes-algorithm-13.png)


By keeping a look up table, we can easily find the corresponding triangulation that corresponds to the certain case.

The program will take a set of points which represents an isosurface. These points represent the shape of a particular object. To decide whether a voxel vertex is inside the points-represented-object, we will measure the distance between that voxel to its nearest point. If the distance is less than a certain iosvalue, we can consider the vertex is inside the object; otherwise, it's outside the object. After running the marching cubes algorithm, we will get a mesh which contains all the faces (triangles) and vertices. The program will output this mesh as an obj format file.

## Solutions
The main data structure that will be used is: glm::vec3 which provides 3D Cartesian coordinates of a point. This data structure is the most basic data structure in OpenGL geometry computing which supports all the necessary arithmetic. Also, std::vector will be the most constantly used container which holds the vertices.

To represent the faces, I will use a simple data structure which is an 3-sized integer array that stores the index of each vertex. The mesh therefore contains a vector for vertices, and a vector for faces. This data structure omit the orientation of the faces, and is not efficient for traversal, but it's enough to show the contour of the mesh, and can be output to an obj formatted file. The choice of this data structure is simply to reduce the complexity of this project. 

To implement the voxel, I will use a 8-bit boolean to correspond different cases of where triangles are represented in the voxel. The 8-bit boolean can be represented with an integer range from 0 to 255. As is explained above, these 255 cases will be put into 15 different buckets where each represents one or more triangles . A std::vector is a perfect candidate to hold these voxels and their corresponding triangles.

## References
<a name="madams">1</a>: Michael D. Adams. 2019. (02 2019), 1695. [Lecture slides for programming in C++](https://books.google.ca/books?id=1rmIDwAAQBAJ&printsec=frontcover&source=gbs_ge_summary_r&cad=0#v=onepage&q&f=false)

<a name="Lorenson">2</a>: William E. Lorensen and Harvey E. Cline. 1987. Marching Cubes: A High Resolution 3D Surface Construction Algorithm. In Proceedings of the 14th Annual Conference on Computer Graphics and Interactive Techniques (SIGGRAPH ’87). ACM, New York, NY, USA, 163–169. [https://doi.org/10.1145/37401.37422](https://doi.org/10.1145/37401.37422)

<a name="Durst">3</a>: Martin J. Dürst. 1988. Re: Additional Reference to ”Marching Cubes”. SIGGRAPH Comput. Graph. 22, 5 (Oct. 1988), 243–. [https: //doi.org/10.1145/378267.378271](https://doi.org/10.1145/378267.378271)

<a name="Neil">4</a>:  G. M. Nielson and B. Hamann. 1991. The asymptotic decider: resolving the ambiguity in marching cubes. In Proceeding Visualization’91.83–91. [https://doi.org/10.1109/VISUAL.1991.175782](https://doi.org/10.1109/VISUAL.1991.175782)

<a name="Natarajan1994">5</a>: B. K. Natarajan. 1994. On generating topologically consistent isosurfaces from uniform samples. The Visual Computer 11, 1 (01 Jan 1994), 52–62. [https://doi.org/10.1007/BF01900699](https://doi.org/10.1109/VISUAL.1991.175782)

<a name="che">6</a>: Evgueni Tcherniaev. 1996. Marching Cubes 33: Construction of Topologically Correct Isosurfaces. (01 1996).
