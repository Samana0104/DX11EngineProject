#include "pch.h"
#include "MyShader.h"
#include "MyMesh2D.h"
using namespace MyProject;

MyShader::MyShader(const ShaderDesc& _desc) : 
	mShaderDesc(_desc)
{
}

const ShaderDesc& MyShader::GetShaderDesc() const
{
	return mShaderDesc;
}
