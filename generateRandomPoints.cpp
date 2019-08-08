//
// Created by ncy on 8/7/19.
//

#include "MarchingCubes.hpp"
#include <random>
#include <iostream>
#include <getopt.h>

using Point = glm::vec3;

std::vector<Point> generateRandomPoints(int number, int maxabsval) {
    std::vector<Point> res;
    std::default_random_engine e;
    std::uniform_real_distribution<float> z(-maxabsval,maxabsval),x(-maxabsval,maxabsval),y(-maxabsval,maxabsval);


    for(int i=0; i<number; ++i) {
        float t1 = x(e), t2 = y(e), t3 = z(e);
        res.emplace_back(Point(t1,t2,t3));
    }

    return res;

}

int main(int argc, char **argv){
    int opt, n=10000 , m=1 ; //default value for number of points and max absolute value

    while((opt = getopt(argc, argv, "n:m:")) != -1){
        switch(opt)
        {
            case 'n':
                n = atoi(optarg); //number of points
                break;
            case 'm':
                m = atoi(optarg); //maximum absolute value of points
                break;
            case '?':
            default:
                abort();
        }

    }
    auto points = generateRandomPoints(n,m);

    for(auto point: points){
        std::cout << point.x << ' ' << point.y << ' ' << point.z << '\n';
    }
}
