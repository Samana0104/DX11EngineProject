#pragma once
#include "Object2D.h"
#include "Camera.h"

namespace HBSoft
{
    class Actor : public Object2D
    {
    protected:
        Camera* mCamera = nullptr;

    private:
        virtual void OnCollision(RECT_F& _self, RECT_F& _target, Actor& _targetObj) = 0;

    protected:
        Actor();

    public:
        void SetViewedCamera(Camera* _camera);

        // virtual void Front(vec2 _move) = 0;
        // virtual void Back(vec2 _move) = 0;
        // virtual void Right(vec2 _move) = 0;
        // virtual void Left(vec2 _move) = 0;

        virtual void Update(const float _deltaTime) override;
        virtual void Render() override;
    };
}  // namespace HBSoft
