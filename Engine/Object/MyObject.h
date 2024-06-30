#pragma once
#include "MyResourceManger.h"
#include "MyInput.h"

namespace MyProject
{
	class MyObject
	{
	protected:
		MyTransformer2D		mTransform;
		TEXTURE_KEY			mTextureKey;
		MESH_KEY			mMeshKey;
		vec4				mColor;

		MyResourceManager&	mManager = MyResourceManager::GetInstance();
		MyInput& mInput = MyInput::GetInstance();

	protected:
		MyObject();

	public:
		void SetColor(vec4 _color);
		void SetTextureKey(TEXTURE_KEY _key);
		void SetMeshKey(MESH_KEY _key);

		const MyTransformer2D& GetTransform() const;
		const vec4&			GetColor() const;
		const MESH_KEY&		GetMeshKey() const;
		const TEXTURE_KEY&  GetTextureKey() const;

		MyTransformer2D* operator->(); // 위치 변환 편하게 하려고 오버로딩 함
		
		virtual void Update(const float _deltaTime);
		virtual void Render();
	};
}
