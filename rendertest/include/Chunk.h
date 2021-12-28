#pragma once

#include <vector>
#include "Geometry/Vertex.h"



/*
Chunk structure example:
x   x   x   x  
  x   x   x   x
x   x   x   x  
  x   x   x   x
x   x   x   x  
  x   x   x   x

Multiple chunks therefore look like this:
x   x   x   x  |x   x   x   x  |x   x   x   x  
  x   x   x   x|  x   x   x   x|  x   x   x   x
x   x   x   x  |x   x   x   x  |x   x   x   x  
  x   x   x   x|  x   x   x   x|  x   x   x   x
x   x   x   x  |x   x   x   x  |x   x   x   x  
  x   x   x   x|  x   x   x   x|  x   x   x   x
-----------------------------------------------
x   x   x   x  |x   x   x   x  |x   x   x   x  
  x   x   x   x|  x   x   x   x|  x   x   x   x
x   x   x   x  |x   x   x   x  |x   x   x   x  
  x   x   x   x|  x   x   x   x|  x   x   x   x
x   x   x   x  |x   x   x   x  |x   x   x   x  
  x   x   x   x|  x   x   x   x|  x   x   x   x
-----------------------------------------------
x   x   x   x  |x   x   x   x  |x   x   x   x  
  x   x   x   x|  x   x   x   x|  x   x   x   x
x   x   x   x  |x   x   x   x  |x   x   x   x  
  x   x   x   x|  x   x   x   x|  x   x   x   x
x   x   x   x  |x   x   x   x  |x   x   x   x  
  x   x   x   x|  x   x   x   x|  x   x   x   x

Indices work like this:
[03]          [23]
       [13]          [33]
[02]          [22]
       [12]          [32]
[01]          [21]
       [11]          [31]
[00]          [20]
       [10]          [30]

Combined with chunk indexing with format [chunkX chunkY vertexX vertexY]:
[-1 -1 0 3]   [-1 -1 2 3]        | [0  -1 0 3]   [0  -1 2 3]       
       [-1 -1 1 3]   [-1 -1 3 3] |        [0  -1 1 3]   [0  -1 3 3]
[-1 -1 0 2]   [-1 -1 2 2]        | [0  -1 0 2]   [0  -1 2 2]       
       [-1 -1 1 2]   [-1 -1 3 2] |        [0  -1 1 2]   [0  -1 3 2]
[-1 -1 0 1]   [-1 -1 2 1]        | [0  -1 0 1]   [0  -1 2 1]       
       [-1 -1 1 1]   [-1 -1 3 1] |        [0  -1 1 1]   [0  -1 3 1]
[-1 -1 0 0]   [-1 -1 2 0]        | [0  -1 0 0]   [0  -1 2 0]       
       [-1 -1 1 0]   [-1 -1 3 0] |        [0  -1 1 0]   [0  -1 3 0]
-----------------------------------------------------------------
[-1 0  0 3]   [-1 0  2 3]        | [0  0  0 3]   [0  0  2 3]       
       [-1 0  1 3]   [-1 0  3 3] |        [0  0  1 3]   [0  0  3 3]
[-1 0  0 2]   [-1 0  2 2]        | [0  0  0 2]   [0  0  2 2]       
       [-1 0  1 2]   [-1 0  3 2] |        [0  0  1 2]   [0  0  3 2]
[-1 0  0 1]   [-1 0  2 1]        | [0  0  0 1]   [0  0  2 1]       
       [-1 0  1 1]   [-1 0  3 1] |        [0  0  1 1]   [0  0  3 1]
[-1 0  0 0]   [-1 0  2 0]        | [0  0  0 0]   [0  0  2 0]       
       [-1 0  1 0]   [-1 0  3 0] |        [0  0  1 0]   [0  0  3 0]
*/

class Chunk {
private:
    std::vector<std::vector<Vertex>> vertices;

public:
    static const int CHUNK_SIZE;
    
    Chunk() = default;
    Chunk(const std::vector<std::vector<Vertex>> &initialVertices);

    void SetColor(glm::vec4 &color) {
        for (std::vector<Vertex> &vertexVector : vertices) {
            for (Vertex &vertex : vertexVector) {
                vertex.color = color;
            }
        }
    }

    std::vector<Vertex> GetVertices();
};
