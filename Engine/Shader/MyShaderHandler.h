#pragma once
#include "ResourceHandler.h"
#include "MyShader.h"

namespace MyProject
{
	class MyShaderHandler : public ResourceHandler<MyShader, SHADER_KEY>
	{
	private:
		bool CreatePixelShader(const MESH_KEY _key);
		bool CreateVertexShader(const MESH_KEY _key);

	public:
		bool CreateShader(const ShaderDesc _desc);
	};
}

