//
// Created by Daniel on 2019-07-10.
//

#ifndef CPP_PROJECT_MESH_HPP
#define CPP_PROJECT_MESH_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <ostream>
#include <iostream>
#include <array>
#include "glm/vec3.hpp"

using Point = glm::vec3;

struct Face{
    Face(Point a, Point b, Point c){
        vertex_[0] = a;
        vertex_[1] = b;
        vertex_[2] = c;
    }
    Point vertex_[3];
};


class Mesh{
public:
    void addPoint(const Point& point){
        point_.push_back(point);
    }

    void addFace(int i){
        std::array<int,3> tmp({i,i+1,i+2});
        faces_.push_back(tmp);
    }

    int getSize() const{ return point_.size();}


    //output the mesh as OFF format
    friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh){
        if(mesh.faces_.empty()){
            return out;
        }

        out << "OFF \n" << mesh.point_.size() << ' ' << mesh.faces_.size() << " 0\n";

        //output the vertices
        for(auto& point: mesh.point_){
            out << point.x << ' ' << point.y << ' ' << point.z << '\n';
        }

        //output the face indices
        for(auto& face: mesh.faces_){
            out << "3 " << face[0] << ' '<< face[1] <<' '<< face[2] <<'\n';
        }

        return out;
    }


private:
    std::vector<Point> point_; // stores the vertices
    std::vector<std::array<int,3>> faces_; // stores the faces



};

#endif //CPP_PROJECT_MESH_HPP
