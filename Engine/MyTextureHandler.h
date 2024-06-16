#pragma once
#include "ResourceHandler.h"
#include "MyTexture.h"

namespace MyProject
{
	class MyTextureHandler : public ResourceHandler<MyTexture>
	{
	public:
		void CreateTexture(const std::string _key, const wstringV _texturePath);
		void AddTexture(const std::string _key, std::shared_ptr<MyTexture>& _texture)
	};
}
