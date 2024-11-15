#pragma once

#include "Object3D.h"
#include "ConstantBuffers.h"

namespace HBSoft
{
    class LineObj : public Object3D
    {
    private:
        LineVSCB m_vsConstant;

    public:
        LineObj();

        void         Draw(vec3 start, vec3 end, vec4 color);
        virtual void SetMatrix(mat4 viewMat, mat4 projMat) override;
    };

}  // namespace HBSoft
