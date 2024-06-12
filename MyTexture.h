#pragma once
#include "Component.h"

namespace MyProject
{
	class MyTexture : public Component
	{
	private:
		ComPtr<ID3D11ShaderResourceView>	mSRV;
		ComPtr<ID3D11Resource>				mTexture;

	private:
		bool CreateTexure(const wstringV _textureName);

	public:
		MyTexture(const wstringV _textureName);
		~MyTexture();


		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
		virtual void ReleaseComponent() override;
	};
}

