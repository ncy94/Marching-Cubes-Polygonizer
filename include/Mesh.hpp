//
// Created by Daniel on 2019-07-10.
//

#ifndef CPP_PROJECT_MESH_HPP
#define CPP_PROJECT_MESH_HPP

#include "MarchingCubes.hpp"
#include <vector>
#include <iostream>
#include <cassert>
#include <ostream>


class Mesh{
public:
    Mesh() = default;

    void addFace(Face face){
        faces_.push_back(face);

        //add the 3 vertices of a face
        for(int i=0; i<3; ++i){
            //new vertex will be added at index vertices_size()
            faces_index.push_back(vertices_.size());
            vertices_.push_back(face.vertex_[i]);
        }
    }

    //output the mesh as obj format
    friend ostream& operator<<(ostream& out, const Mesh& mesh){
        if(mesh.faces_index.size() == 0){
            assert(mesh.faces_.size() == 0);
            return;
        }

        //output the vertices
        while(mesh.vertices_.size() > 0){
            out << 'v ' << mesh.vertices_[0] << ' ' << mesh.vertices_[1] << ' ' << mesh.vertices_[2] << '\n';
        }

        //output the face indices
        while(mesh.vertices_ > 0){
            out << 'f ' << mesh.faces_index[0] << ' '<< mesh.faces_index[1] <<' '<<mesh.faces_index[2] <<'\n';
        }
    }


private:
    std::vector<Point> vertices_; // stores the vertices
    std::vector<Face> faces_; // stores the faces
    std::vector<int> faces_index; // stores the vertex indices of the faces.


};

#endif //CPP_PROJECT_MESH_HPP
