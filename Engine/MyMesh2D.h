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
		POINT_F		mMeshSize;

	protected:
		inline static D3Device& mDevice = D3Device::GetInstance();
		inline static MyWindow& mWindow = MyWindow::GetInstance();

	protected:
		MyMesh2D(const MeshShape _meshShape, const POINT_F _meshSize);

		void ReserveVertexSize(size_t _vertexCount);
		void AddVertexAndColorAndUV(const vec2 _vertex, const vec4 _color, const vec2 _uv);
		void AddVertexIndex(std::initializer_list<size_t> _index);
		bool CreateVertexBuffer();

	public:
		void UpdateRenderVertices(mat3x3 & _matrix);
		void SetIAVertexBuffer();

		MyMesh2D& SetVertexColor(const size_t _colorIdx, const vec4 _color); 
		MyMesh2D& SetVertexUV(const size_t _uvIdx, const vec2 _uv);
		MyMesh2D& MoveVertex(const size_t _vertexIdx, const vec2 _pos);
		MyMesh2D& MoveAllVertices(const vec2 _pos);
		MyMesh2D& RotateVertex(const size_t _vertexIdx, const float _angle);
		MyMesh2D& RotateAllVertices(const float _angle);

		const std::vector<MyVertex2D>& GetRanderVertices();
		POINT_F	GetMeshSize() const;

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
	};
}
