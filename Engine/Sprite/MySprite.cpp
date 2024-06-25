#include "pch.h"
#include "MySprite.h"
using namespace MyProject;

MySprite::MySprite(SpriteType _spriteType) :
	mSpriteType(_spriteType)
{
}

void MySprite::AddShaderKey(SHADER_KEY _shaderKey)
{
	mShaderKeys.push_back(_shaderKey);
}
