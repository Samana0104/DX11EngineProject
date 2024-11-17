#pragma once

#include "Mesh/Mesh.h"
#include "Mesh/Box3D.h"

namespace HBSoft
{
    class CubeMap : public Mesh
    {
    private:
        bool CreateVertex(std::shared_ptr<D3Device>& device);
        bool CreateIndex(std::shared_ptr<D3Device>& device);

    public:
        CubeMap(std::shared_ptr<D3Device>& device);
        ~CubeMap() = default;
    };
}  // namespace HBSoft
