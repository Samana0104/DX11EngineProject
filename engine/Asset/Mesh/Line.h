#pragma once

#include "Mesh.h"

namespace HBSoft
{
    class Line : public Mesh
    {
    private:
        bool CreateVertex(std::shared_ptr<D3Device>& device);
        bool CreateIndex(std::shared_ptr<D3Device>& device);

    public:
        Line(std::shared_ptr<D3Device>& device);
        ~Line() = default;
    };
}  // namespace HBSoft
