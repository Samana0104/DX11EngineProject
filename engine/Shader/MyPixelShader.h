#pragma once
#include "MyShader.h"

namespace MyProject
{
	class MyPixelShader : public MyShader
	{
	private:
		ComPtr<ID3D11PixelShader>	mPixelShader;

	private:
		bool CreatePixelShader();

	public:
		MyPixelShader(const ShaderDesc& _desc);

		virtual bool CreateShader() override;
		virtual void SetUpConfiguration() const override;
	};
}

