//
// Created by Daniel on 2019-07-10.
//

#ifndef CPP_PROJECT_NCY94_MARCHINGCUBES_HPP
#define CPP_PROJECT_NCY94_MARCHINGCUBES_HPP

#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include <vector>
#include <iostream>

//data structure to represent 3d point
using Point = glm::vec3;

struct Face{
    Face(Point a, Point b, Point c){
        vertex_[0] = a;
        vertex_[1] = b;
        vertex_[2] = c;
    }
    Point vertex_[3];
};

struct Voxel{
    Point vertex[8];
    double value[8];
};

//an array to store the vertices
class Vertices{
public:
    Vertices(int resX, int resY, int resZ):resX_(resX),resY_(resY),resZ_(resZ){
        vertex_ = new double[resX*resY*resZ];
    }
    ~Vertices(){delete[] vertex_;}

    //assign val to index a,b,c
    void operator()(int a, int b, int c, int val){
        vertex_[a*resY_*resZ_ + b*resZ_ + c] = val;
    }

    //return the value at this index
    float operator()(int a, int b, int c) const{
        return vertex_[a*resY_*resZ_ + b*resZ_ + c];
    }
private:
    //vertex array stores the value of each vertex
    double* vertex_;
    int resX_;
    int resY_;
    int resZ_;
};

class MarchingCubes{
public:
    //default resolution: 100*100*100, default isovalue is 0.5
    MarchingCubes(int resolution=100, double isovalue = 0.5):
        //the number of vertices is 1 more than the resolution
        res_(resolution), isoLevel_(isovalue), vertices_(Vertices(res_+1, res_+1, res_+1)){
        voxels_ = new Voxel[res_ * res_ * res_];
        size_ = 1. / resolution;
        offset_ = 0;
    };

    ~MarchingCubes(){
        delete[] voxels_;
    }

    // process and store the input point cloud
    std::vector<Point> ProcessPoints(std::istream&);

    // random generate a set of points to represent the object
    std::vector<Point> genrateRandomPoints(int number);

    // decide the value of each vertex using
    void constructGrid(const std::vector<Point>& points);

    // get the value of the n-th index vertex of the grid
    // whose most significant vertex is the parameter vertex
    double getGridValue(unsigned int n, const Vertices& vertex);


private:
    int res_; //resolution of the object: res * res * res
    double isoLevel_;
    double size_; // the size of each voxel
    double offset_;
    Vertices vertices_ ;
    // the index of the voxel is marked by its nearest vertice towards (0,0,0)
    Voxel* voxels_;
};


#endif //CPP_PROJECT_NCY94_MARCHINGCUBES_HPP
