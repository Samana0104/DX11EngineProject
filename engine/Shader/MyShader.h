#pragma once
#include "MyCoreAPI.h"
namespace MyProject
{
	enum class ShaderType
	{
		VERTEX = 0,
		PIXEL,
	};

	struct ShaderDesc
	{
		ShaderType		mShaderType;
		std::wstring	mShaderPath;
		std::string		mShaderEntry;
	};

	class MyShader 	
	{
	protected:
		ComPtr<ID3DBlob> mShaderByteCode;
		ShaderDesc		 mShaderDesc;
		
	protected:
		inline static D3Device& mDevice = D3Device::GetInstance();
	
	protected:
		MyShader(const ShaderDesc& _desc);

	public:
		const ShaderDesc& GetShaderDesc() const;

		virtual bool CreateShader() = 0;
		virtual void SetUpConfiguration() const = 0;
	};
}
