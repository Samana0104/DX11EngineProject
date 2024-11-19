#pragma once

#include "Object3D.h"

namespace HBSoft
{
    class Test3DObj : public Object3D
    {
    private:


    public:
        Test3DObj();

        virtual void Render() override;
    };
}  // namespace HBSoft
