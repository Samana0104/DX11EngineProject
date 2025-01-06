
#pragma once
#include "pch.h"
#include "Mesh\Mesh.h"

namespace HBSoft
{

    class Grid : public Mesh
    {
    public:
        bool CreateVertices(std::shared_ptr<D3Device> device);
        bool CreateIndices(std::shared_ptr<D3Device> device);

        float width     = 92.16f;
        float height    = 92.16f;
        int   numSlices = 80;
        int   numStacks = 80;


    public:
        Grid(std::shared_ptr<D3Device> device);
        ~Grid() = default;
    };
}  // namespace HBSoft