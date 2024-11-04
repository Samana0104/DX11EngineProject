/*
author : 변한빛
description : 씬 전체를 관리하기 위해 만든 헤더파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Scene.h"
#include "MgrTemplate.h"

namespace HBSoft
{
    class SceneManager : public MgrTemplate<Scene, SCENE_KEY>
    {
    private:
        const std::unique_ptr<Scene>*             m_currentScene;
        std::queue<const std::unique_ptr<Scene>*> m_queueForWaiting;
        // 해당 변수는 신이 삭제될 때 Update에서 바뀌는 걸 보장하도록 하기 위해 선언함

    public:
        void SetCurrentScene(SCENE_KEY key);
        void Update(const float deltaTime);
        void Render();
        void Release();
    };
}  // namespace HBSoft
