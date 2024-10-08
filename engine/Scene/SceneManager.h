#pragma once
#include "Scene.h"
#include "ResourceHandler.h"

namespace HBSoft
{
    class SceneManager : public ResourceHandler<Scene, SCENE_KEY>
    {
    private:
        std::shared_ptr<Scene>             m_currentScene;
        std::queue<std::shared_ptr<Scene>> m_queueForWaiting;

    private:
        void AddScene(std::shared_ptr<Scene> scene, SCENE_KEY key);

    public:
        void SetCurrentScene(SCENE_KEY key);
        void SetCurrentScene(std::shared_ptr<Scene> scene);

        void Init();
        void Update(const float deltaTime);
        void Render();
        void Release();
    };
}  // namespace HBSoft
