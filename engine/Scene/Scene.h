#pragma once
#include "pch.h"

namespace HBSoft
{
    class Scene
    {
    private:
        Scene(Scene&&)                 = delete;
        Scene& operator=(const Scene&) = delete;
        Scene& operator=(Scene&&)      = delete;

    public:
        Scene() = default;

        virtual void Init()                  = 0;
        virtual void Render()                = 0;
        virtual void Release()               = 0;
        virtual void Reset()                 = 0;
        virtual void Start()                 = 0;
        virtual void End()                   = 0;
        virtual void Update(float deltaTime) = 0;
    };
}  // namespace HBSoft
