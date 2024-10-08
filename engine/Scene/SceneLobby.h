#pragma once
#include "SceneManager.h"
#include "Input.h"
#include "Camera.h"
#include "Button.h"

namespace HBSoft
{
    class SceneLobby : public Scene
    {
    public:
        Object2D test;
        using Scene::Scene;


        virtual void Init() override;
        virtual void Update(float _deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Reset() override;
        virtual void Start() override;
        virtual void End() override;
    };
}  // namespace HBSoft
