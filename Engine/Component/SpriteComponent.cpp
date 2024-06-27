#include "pch.h"
#include "SpriteComponent.h"
using namespace MyProject;

SpriteComponent::SpriteComponent(MyObject& _obj) :
	mObj(_obj)
{
}

void SpriteComponent::Render(const mat3& _viewMat)
{
}
