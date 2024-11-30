#pragma once

#include "Core.h"
#include "Object3D.h"
#include "Transform3D.h"
#include "Shader/ConstantBuffers.h"

namespace HBSoft
{
    class Camera;

    class Goose : public Object3D
    {
    private:
        float m_speed1 = 5.0f;

    public:
        Goose();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Init() override;
    };


}  // namespace HBSoft