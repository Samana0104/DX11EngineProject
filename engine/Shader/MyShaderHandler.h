#pragma once
#include "ResourceHandler.h"
#include "MyVertexShader.h"
#include "MyPixelShader.h"

namespace MyProject
{
	class MyShaderHandler : public ResourceHandler<MyShader, SHADER_KEY>
	{
	private:
		bool CreateVertexShader(const MESH_KEY& _key, const ShaderDesc& _desc);
		bool CreatePixelShader(const MESH_KEY& _key, const ShaderDesc& _desc);

	public:
		bool CreateShaderResource(const ShaderDesc _desc);
	};
}

