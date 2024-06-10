#pragma once
#include "Component.h"
#include "MyTransformer2D.h"

namespace MyProject
{
	enum class MeshShape
	{
		BOX=1,
		SPEHERE=2
	};

	enum class MeshColor
	{
		
	};

	struct MyVertex2D
	{
		vec2 position;
		vec4 color;
		vec2 uv;
	};

	class MyMesh2D : public Component
	{
	private:
		void CalculateTransform();

	public:
		MyTransformer2D			mTransfomer;
		std::vector<vec2>		mVertices;
		std::vector<size_t>		mIndices;
		std::vector<vec4>		mColors;
		std::vector<vec2>		mUV;
		std::vector<MyVertex2D>	mRenderVertices;
		
		ComPtr<ID3D11ShaderResourceView>	mSRV;
		ComPtr<ID3D11Resource>				mTexture;
		ComPtr<ID3D11Buffer>				mVertexBuffer;

		MeshShape	mMeshShape;
		std::string	mSerialNumber;

	protected:
		MyMesh2D(const MeshShape _meshShape, const std::wstring& _textureName);

		void ReserveVertexSize(size_t _size);
		void AddVertexAndColorAndUV(const vec2 _vertex, const vec4 _color, const vec2 _uv);
		void AddVertexIndex(std::initializer_list<size_t> _index);
		bool CreateVertexBuffer();

	public:
		bool CreateTexure(const std::wstring& _textureName);
		void InitTransformer();
		void Move(const vec2 _pos);
		void Rotate(const float _angle);
		void Scale(const vec2 _scale);
		void SetPosition(const vec2 _pos);
		void SetRotation(const float _angle);
		void SetScale(const vec2 _scale);

		virtual void InitComponent() override;
		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
		virtual void ReleaseComponent() override;
		virtual bool IsMeshCollision(MyMesh2D& _mesh) { return true; } // 순수 가상함수로 전환 예정
		virtual bool IsRectCollision(RECT_F _rect) { return true; } // 순수 가상함수로 전환 예정
		virtual bool IsSphereCollision(vec2 _center, float _radius) { return true; } // 순수 가상함수로 전환 예정
	};
}
