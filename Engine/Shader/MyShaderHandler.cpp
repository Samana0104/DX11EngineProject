#include "pch.h"
#include "MyShaderHandler.h"
using namespace MyProject;

bool MyShaderHandler::CreateVertexShader(const MESH_KEY& _key, const ShaderDesc& _desc)
{
	std::shared_ptr<MyShader> vertexShader = std::make_shared<MyVertexShader>(_desc);
	return AddResource(_key, vertexShader);
}


bool MyShaderHandler::CreatePixelShader(const MESH_KEY& _key, const ShaderDesc& _desc)
{
	std::shared_ptr<MyShader> pixelShader = std::make_shared<MyPixelShader>(_desc);
	return AddResource(_key, pixelShader);
}

bool MyShaderHandler::CreateShaderResource(const ShaderDesc _desc)
{
	auto fileInfo = MyCoreAPI::GetFileNameAndExt(_desc.mShaderPath);
	std::wstring key = fileInfo.first + fileInfo.second;

	switch (_desc.mShaderType)
	{
	case ShaderType::VERTEX:
		return CreateVertexShader(key, _desc);

	case ShaderType::PIXEL:
		return CreatePixelShader(key, _desc);
	}

	return false;
}
