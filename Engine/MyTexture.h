#pragma once
#include "Component.h"

namespace MyProject
{
	class MyTexture : public Component
	{
	private:
		ComPtr<ID3D11ShaderResourceView>	mSRV;
		ComPtr<ID3D11Resource>				mTexture;

		std::wstring	mTexturePath;

	protected:
		inline static D3Device& mDevice = D3Device::GetInstance();

	private:
		bool CreateTexure();
		void SetTextureResource() const;

	public:
		MyTexture(const wstringV _textureName);

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
	};
}
