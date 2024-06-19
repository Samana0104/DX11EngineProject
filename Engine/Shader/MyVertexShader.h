#pragma once
#include "MyShader.h"

namespace MyProject
{
	class MyVertexShader : public MyShader
	{
	private:
		ComPtr<ID3D11VertexShader>	mVertexShader;
		ComPtr<ID3D11InputLayout>	mVertexLayout;

	private:
		bool CreateVertexShader();
		bool CreateIALayout();

	public:
		MyVertexShader(const ShaderDesc& _desc);

		virtual bool CreateShader() override;
		virtual void SetUpConfiguration() const override;
	};
}

