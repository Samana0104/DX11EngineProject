#pragma once
#include "CoreAPI.h"
#include "Input.h"
#include "ResourceManger.h"
#include "ObjectManager.h"

namespace HBSoft
{
    class SceneManager;

    class Scene
    {
    protected:
        SceneManager& m_sceneManager;

        Input&           m_input   = Input::GetInstance();
        ResourceManager& m_manager = ResourceManager::GetInstance();

        ObjectManager m_objManager;

        // SCENE_KEY		mSceneID;
        //  필요하면 추가함

    public:
        Scene(SceneManager& sceneManager)
            : m_sceneManager(sceneManager)
        {}

        // const SCENE_KEY& GetSceneID() const { return mSceneID; }
        // void SetSceneID(SCENE_KEY _sceneID) { mSceneID = _sceneID;  }

        virtual void Init()                  = 0;
        virtual void Render()                = 0;
        virtual void Release()               = 0;
        virtual void Reset()                 = 0;
        virtual void Start()                 = 0;
        virtual void End()                   = 0;
        virtual void Update(float deltaTime) = 0;
    };
}  // namespace HBSoft
