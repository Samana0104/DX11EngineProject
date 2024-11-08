#pragma once

#include "pch.h"
#include "Mesh\Mesh.h"

namespace HBSoft
{
    class Box3D : public Mesh
    {
    private:
        bool CreateVertex(std::shared_ptr<D3Device>& device);
        bool CreateIndex(std::shared_ptr<D3Device>& device);

    public:
        Box3D(std::shared_ptr<D3Device>& device);
    };
}  // namespace HBSoft
