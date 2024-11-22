#pragma once

#include "Object3D.h"

namespace HBSoft
{
    class CubeMapObj : public Object3D
    {
    private:

    public:
        CubeMapObj();

        virtual void Render() override;
    };

}  // namespace HBSoft
