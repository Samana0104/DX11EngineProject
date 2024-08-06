#pragma once
#include "MyCoreAPI.h"
#include "MyTransformer2D.h"
#include "MyTexture.h"

namespace MyProject
{
	enum class MeshShape
	{
		CUSTOM = 0,
		BOX2D = 1,
		CIRCLE2D = 2
	};

	struct MyVertex2D
	{
		vec2 position;
		vec4 color;
		vec2 uv;
	};

	class MyMesh2D	
	{
	private:
		std::vector<vec2>		mVertices;
		std::vector<vec2>		mUV;
		std::vector<vec2>		mTempUV; // UV 좌표 관리를 위해서 억지로 넣음
		std::vector<size_t>		mIndices;
		std::vector<MyVertex2D>	mRenderVertices;

		ComPtr<ID3D11Buffer>	mVertexBuffer;
		MeshShape	mMeshShape;
		POINT_F		mMeshCom; // 무게중심

	protected:
		D3Device& mDevice = D3Device::GetInstance();
		MyWindow& mWindow = MyWindow::GetInstance();

	private:
		bool CreateVertexBuffer();
		void SetIAVertexBuffer();
		void UpdateRenderVertices(const mat3& _matrix, const vec4 &_color);

		void PostRender();

	protected:
		MyMesh2D(MeshShape _meshShape);

		void ReserveVertexSize(size_t _vertexCount);
		void AddVertexAndUV(const vec2 _vertex, const vec2 _uv);
		void AddVertexIndex(std::initializer_list<size_t> _index);
		void CreateMesh(const POINT_F _meshCom = { 0.f, 0.f });
		void SetUVVertex(const size_t _uvVertex, const vec2 _uv); 

	public:
		POINT_F	GetMeshCom() const;

		void Draw(const mat3& _matrix, const vec4 _color = { 1.f, 1.f, 1.f, 1.f });

		virtual void SetUVVertexAsRect(const RECT_F& _rect, const vec2& _imageSize) = 0;
	};
}
