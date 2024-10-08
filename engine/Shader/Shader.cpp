#include "pch.h"
#include "Shader.h"
#include "Mesh2D.h"
using namespace HBSoft;

Shader::Shader(const ShaderDesc& _desc) : 
	mShaderDesc(_desc)
{
}

const ShaderDesc& Shader::GetShaderDesc() const
{
	return mShaderDesc;
}
