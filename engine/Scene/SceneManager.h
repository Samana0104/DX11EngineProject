/*
author : ���Ѻ�
description : �� ��ü�� �����ϱ� ���� ���� �������

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
        // �ش� ������ ���� ������ �� Update���� �ٲ�� �� �����ϵ��� �ϱ� ���� ������

    public:
        void SetCurrentScene(SCENE_KEY key);
        void Update(const float deltaTime);
        void Render();
        void Release();
    };
}  // namespace HBSoft
