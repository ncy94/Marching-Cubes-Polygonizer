//
// Created by ncy on 8/7/19.
//

#include "MarchingCubes.cpp"

int main()
{
    MarchingCubes mc(200,1);

    mc.constructGrid(mc.processPoints(std::cin));

    mc.generateMesh();

    auto mesh = mc.getMesh();

    std::cout << mesh;
}