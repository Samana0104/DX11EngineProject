#pragma once
#include "SceneManager.h"
#include "Camera.h"

namespace HBSoft
{
    class SceneLobby : public Scene
    {
    public:
        Object2D test;
        
        SceneLobby() { Init(); }

        virtual void Init() override;
        virtual void Update(float _deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Reset() override;
        virtual void Start() override;
        virtual void End() override;
    };
}  // namespace HBSoft
