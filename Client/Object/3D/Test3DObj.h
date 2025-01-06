#pragma once

#include "3D/Object3D.h"
#include "3D/Transform3D.h"

namespace HBSoft
{
    class Test3DObj : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;

    public:
        Test3DObj();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        virtual void Release();
    };
}  // namespace HBSoft
