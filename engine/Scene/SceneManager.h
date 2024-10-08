#pragma once
#include "Scene.h"
#include "ResourceHandler.h"

namespace HBSoft
{
    class SceneManager : public ResourceHandler<Scene, SCENE_KEY>
    {
    private:
        std::shared_ptr<Scene>             mCurrentScene;
        std::queue<std::shared_ptr<Scene>> mQueueForWaiting;

    private:
        void AddScene(std::shared_ptr<Scene> _scene, SCENE_KEY _key);

    public:
        void SetCurrentScene(SCENE_KEY _key);
        void SetCurrentScene(std::shared_ptr<Scene> _scene);

        void Init();
        void Update(const float _deltaTime);
        void Render();
        void Release();
    };
}  // namespace HBSoft
