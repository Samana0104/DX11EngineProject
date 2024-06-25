#pragma once
#include "MyCoreAPI.h"

namespace MyProject
{
	enum class SpriteType
	{
		RECT_UV = 0,
		IMAGE = 1,
	};

	class MySprite
	{
	private:
		SpriteType				 mSpriteType;
		std::vector<SHADER_KEY>  mShaderKeys;

	public:
		MySprite(SpriteType _spriteType);
		
		void AddShaderKey(SHADER_KEY _shaderKey);

		virtual void Update(float _deltaTime) = 0;
		virtual void Render() = 0;
	};
}

