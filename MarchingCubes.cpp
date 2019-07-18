#include <cmath>
#include "MarchingCubes.hpp"


std::vector<Point> MarchingCubes::ProcessPoints(std::istream & in)
{
    std::vector<Point> Points;
    double max = 0, min = 0; //record the largest value
    while(in)
    {
        double x,y,z;
        if(!(in >> x >> y >> z)){
            throw std::runtime_error("point not valid");
        }
        max = std::max(x,y,z);
        min = std::min(x,y,z);

        Points.emplace_back(Points);

    }

    //all points will be shifted by offset_ towards (0,0,0)
    //and then align to the grid of the specific resolution
    size_ = (max - min)/res_;
    offset_ = min;

}

void MarchingCubes::constructGrid(const std::vector<Point>& points)
{
    // align the point to the grid starting from (0,0,0) with the resolution
    for(auto point: points){
        double x = (point.x - offset_) / size_;
        double y = (point.y - offset_) / size_;
        double z = (point.z - offset_) / size_;

        //find the neighbor gird voxel of the point. For each vertice
        //if it's within isolevel, set the vertice to value 1
        for(int i = floor(x); i< ceil(x); ++i){
            for(int j = floor(y) ; j< ceil(y); ++j){
                for(int k = floor(z); k< ceil(z); ++k){
                    if(glm::distance(Point(i,j,k),point) < isoLevel_)
                        vertices_(i,j,k,1);
                }
            }
        }
    }

//    for(int i=0; i<res_; ++i){
//        for(int j=0; j<res_; ++j){
//            for(int k=0; k<res_; ++k){
//                (*voxels_)[i * res_*res_ + j*res_ + k] = vertices_(i,j,k);
//            }
//        }
//    }

}

// This function returns the vertex value (1 or 0) of a grid voxel
// given the least significant vertex and the index of vertex
double MarchingCubes::getGridValue(unsigned int n, const Vertices &vertex)
{
    assert(n < 8);

    // the coordinate of the vertex is the binary representation of n
    // where i,j,k are the binary bits
    int i,j,k = 0;
    k = n % 2;
    n >>= 1;
    j = n % 2;
    n >>= 1;
    i = n;

    return vertex(i,j,k);

}

