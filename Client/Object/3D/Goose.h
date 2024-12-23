#pragma once

#include "Core.h"
#include "3D/Object3D.h"
#include "3D/Transform3D.h"
#include "Shader/ConstantBuffers.h"
#include "HeightMapObj.h"

namespace HBSoft
{
    class Goose : public Object3D
    {
    private:
        std::shared_ptr<Mesh>                       m_mesh;
        std::vector<std::shared_ptr<AnimationClip>> m_gooseAnis;

        float                         m_speed1 = 0.7f;
        std::vector<mat4>             anim;
        std::shared_ptr<HeightMapObj> m_mapObj;

    public:
        Goose();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Init() override;

        float GetLocationX();
        float GetLocationZ();

        vec3 GetGooseTransform();

        void SetHeightMap(std::shared_ptr<HeightMapObj> mapObj);
    };


}  // namespace HBSoft