#pragma once
#include "Component.h"
#include "MyTransformer2D.h"

namespace MyProject
{
	enum class MeshShape
	{
		CUSTOM = 0,
		BOX2D = 1,
		SPEHERE = 2
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
		std::vector<vec2>		mVertices;
		std::vector<size_t>		mIndices;
		std::vector<vec4>		mColors;
		std::vector<vec2>		mUV;
		std::vector<MyVertex2D>	mRenderVertices;

		ComPtr<ID3D11Buffer>	mVertexBuffer;
		MeshShape	mMeshShape;
		POINT_F		mMeshCom; // 무게중심

	protected:
		inline static D3Device& mDevice = D3Device::GetInstance();
		inline static MyWindow& mWindow = MyWindow::GetInstance();

	private:
		bool CreateVertexBuffer();

	protected:
		MyMesh2D(MeshShape _meshShape);

		void ReserveVertexSize(size_t _vertexCount);
		void AddVertexAndColorAndUV(const vec2 _vertex, const vec4 _color, const vec2 _uv);
		void AddVertexIndex(std::initializer_list<size_t> _index);
		void CreateMesh(const POINT_F _meshCom);

	public:
		void UpdateRenderVertices(const mat3 _matrix);
		void SetIAVertexBuffer();

		MyMesh2D& SetVertexColor(const size_t _colorIdx, const vec4 _color); 

		POINT_F	GetMeshCom() const;

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
	};
}
