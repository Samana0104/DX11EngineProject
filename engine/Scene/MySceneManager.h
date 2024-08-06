#pragma once
#include "MyScene.h"
#include "ResourceHandler.h"

namespace MyProject
{
	class MySceneManager : public ResourceHandler<MyScene, SCENE_KEY>
	{
	private:
		std::shared_ptr<MyScene> mCurrentScene;
		std::queue<std::shared_ptr<MyScene>> mQueueForWaiting;
		
	private:
		void AddScene(std::shared_ptr<MyScene> _scene, SCENE_KEY _key);

	public:
		void SetCurrentScene(SCENE_KEY _key);
		void SetCurrentScene(std::shared_ptr<MyScene> _scene);

		void Init();
		void Update(const float _deltaTime);
		void Render();
		void Release();
	};
}
