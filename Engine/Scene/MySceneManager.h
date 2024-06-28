#pragma once
#include "MyScene.h"
#include "ResourceHandler.h"

namespace MyProject
{
	class MySceneManager : public ResourceHandler<MyScene, SCENE_KEY>
	{
	private:
		std::shared_ptr<MyScene> mCurrentScene;
		
	private:
		void AddScene(std::shared_ptr<MyScene> _scene, SCENE_KEY _key);

	public:
		void SetCurrentScene(SCENE_KEY _key);

		void Init();
		void Update(const float _deltaTime);
		void Render();
		void Release();
	};
}
