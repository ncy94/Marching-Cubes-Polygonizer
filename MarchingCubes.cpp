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
            break;
            //throw std::runtime_error("point not valid");
        }
        max = std::max({x,y,z});
        min = std::min({x,y,z});

        Points.emplace_back(Point(x,y,z));

    }

    //all points will be shifted by offset_ towards (0,0,0)
    //and then align to the grid of the specific resolution
    size_ = (max - min)/res_;
    offset_ = min;

    return Points;

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
                    if(glm::distance(Point(i,j,k),point) < isoLevel_) {
                        vertices_(i, j, k, 1);
                    }

                }
            }
        }
    }

}

Point MarchingCubes::VertexInterp(const Vertex &v1, const Vertex &v2) {
    if(abs(isoLevel_ - v1.getValue()) < 0.00001)
        return v1.getPoint();

    if(abs(isoLevel_ - v2.getValue()) < 0.00001)
        return v2.getPoint();

    if(abs(v1.getValue() - v2.getValue()) < 0.00001)
        return v1.getPoint();

    float tmp;
    Point p;

    tmp = (isoLevel_ - v1.getValue())/(v2.getValue() - v1.getValue());
    p = v1.getPoint() + tmp * (v2.getPoint() - v1.getPoint());

    return p;
}

void MarchingCubes::generateMesh() {
    int faceindex = 0;

    //iterator each voxel
    for(int i=0; i<res_; ++i)
        for(int j=0; j<res_; ++j)
            for(int k=0; k<res_; ++k){
                unsigned int cubeindex = 0;
                Vertex voxelPivot = vertices_.get(i,j,k);
                Point vertList[12];

                //determine the index of edgeTable for each voxel
                for(unsigned int m=0; m<8; ++m){
                    if(vertices_(voxelPivot.getPoint(m)).getValue() < isoLevel_)
                        cubeindex |= 1 >> i;
                }

                if(edgeTable[cubeindex] & 1)
                    vertList[0] = VertexInterp(voxelPivot, vertices_(voxelPivot.getPoint(1)));

                if(edgeTable[cubeindex] & 2)
                    vertList[1] = VertexInterp(vertices_(voxelPivot.getPoint(1)),
                            vertices_(voxelPivot.getPoint(2)));

                if(edgeTable[cubeindex] & 4)
                    vertList[2] = VertexInterp(vertices_(voxelPivot.getPoint(2)),
                            vertices_(voxelPivot.getPoint(3)));

                if(edgeTable[cubeindex] & 8)
                    vertList[3] = VertexInterp(vertices_(voxelPivot.getPoint(3)),voxelPivot);

                if(edgeTable[cubeindex] & 16)
                    vertList[4] = VertexInterp(vertices_(voxelPivot.getPoint(4)),
                            vertices_(voxelPivot.getPoint(5)));

                if(edgeTable[cubeindex] & 32)
                    vertList[5] = VertexInterp(vertices_(voxelPivot.getPoint(5)),
                            vertices_(voxelPivot.getPoint(6)));

                if(edgeTable[cubeindex] & 64)
                    vertList[6] = VertexInterp(vertices_(voxelPivot.getPoint(6)),
                            vertices_(voxelPivot.getPoint(7)));

                if(edgeTable[cubeindex] & 128)
                    vertList[7] = VertexInterp(vertices_(voxelPivot.getPoint(7)),
                            vertices_(voxelPivot.getPoint(4)));

                if(edgeTable[cubeindex] & 256)
                    vertList[8] = VertexInterp(vertices_(voxelPivot.getPoint(0)),
                            vertices_(voxelPivot.getPoint(4)));

                if(edgeTable[cubeindex] & 512)
                    vertList[9] = VertexInterp(vertices_(voxelPivot.getPoint(1)),
                            vertices_(voxelPivot.getPoint(5)));

                if(edgeTable[cubeindex] & 1024)
                    vertList[10] = VertexInterp(vertices_(voxelPivot.getPoint(2)),
                            vertices_(voxelPivot.getPoint(6)));

                if(edgeTable[cubeindex] & 2048)
                    vertList[11] = VertexInterp(vertices_(voxelPivot.getPoint(3)),
                                               vertices_(voxelPivot.getPoint(7)));

                //get the triangle from the vertList
                int trinum = 0;
                for(int n=0; triTable[cubeindex][n] != -1; n+=3 ){
                    // add the three points in the mesh
                    mesh_.addPoint(vertList[triTable[cubeindex][n]]);
                    mesh_.addPoint(vertList[triTable[cubeindex][n+1]]);
                    mesh_.addPoint(vertList[triTable[cubeindex][n+3]]);

                    // add the triangle index in the mesh.
                    mesh_.addFace(faceindex);
                    faceindex += 3;
                }

            }


}

// This function returns the vertex value (1 or 0) of a grid voxel
// given the least significant vertex and the index of vertex
//double MarchingCubes::getGridValue(unsigned int n, const Vertices &vertex)
//{
//    assert(n < 8);
//
//    // the coordinate of the vertex is the binary representation of n
//    // where i,j,k are the binary bits
//    int i,j,k = 0;
//    k = n % 2;
//    n >>= 1;
//    j = n % 2;
//    n >>= 1;
//    i = n;
//
//    return vertex(i,j,k);
//
//}

