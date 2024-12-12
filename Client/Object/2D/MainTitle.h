#pragma once

#include "2D/Object2D.h"

namespace HBSoft
{
    class MainTitle : public Object2D
    {
    private:
        std::shared_ptr<Texture> m_titleTexture;
        std::shared_ptr<Mesh>    m_boxMesh;

    public:
        MainTitle();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init() override;
        virtual void Release() override;
    };
}  // namespace HBSoft
