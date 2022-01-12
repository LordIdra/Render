#pragma once

#include <vector>
#include "units.h"
#include "Vertex.h"



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
    std::vector<std::vector<Vertex>> vertices_;

public:
    static const int VERTEX_COUNT = 8;
    static constexpr float VERTEX_SPACING = 0.6;
    static constexpr float SIZE = VERTEX_COUNT * VERTEX_SPACING;
    
    Chunk() = default;
    Chunk(const std::vector<std::vector<Vertex>> &initialVertices);

    static auto GenerateChunkVertices(const ChunkCoord &coord, Color color) -> std::vector<std::vector<Vertex>>;

    auto SetColor(Color color) -> void;
    [[nodiscard]] auto GetVertices() const ->  std::vector<Vertex>;
};
