#pragma once
#include "Component.h"
#include "MyTransformer2D.h"

namespace MyProject
{
	enum class MeshShape
	{
		CUSTOM = 0,
		BOX = 1,
		SPEHERE = 2
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
		std::vector<vec2>		mVertices;
		std::vector<size_t>		mIndices;
		std::vector<vec4>		mColors;
		std::vector<vec2>		mUV;
		std::vector<MyVertex2D>	mRenderVertices;

		ComPtr<ID3D11Buffer>	mVertexBuffer;
		MeshShape	mMeshShape;

	protected:
		inline static D3Device& mDevice = D3Device::GetInstance();
		inline static MyWindow& mWindow = MyWindow::GetInstance();

	protected:
		MyMesh2D(const MeshShape _meshShape);

		void ReserveVertexSize(size_t _vertexCount);
		void AddVertexAndColorAndUV(const vec2 _vertex, const vec4 _color, const vec2 _uv);
		void AddVertexIndex(std::initializer_list<size_t> _index);
		void SetIAVertexBuffer();
		bool CreateVertexBuffer();

	public:
		void UpdateRenderVertices(mat3x3 & _matrix);
		void SetVertexColor(const size_t _colorIdx, const vec4 _color); 
		void SetVertexUV(const size_t _uvIdx, const vec2 _uv);
		void MoveVertex(const size_t _vertexIdx, const vec2 _pos);
		void MoveAllVertices(const vec2 _pos);
		void RotateVertex(const size_t _vertexIdx, const float _angle);
		void RotateAllVertices(const float _angle);

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
		virtual bool IsMeshCollision(MyMesh2D& _mesh) { return true; } // 순수 가상함수로 전환 예정
		virtual bool IsRectCollision(RECT_F _rect) { return true; } // 순수 가상함수로 전환 예정
		virtual bool IsSphereCollision(vec2 _center, float _radius) { return true; } // 순수 가상함수로 전환 예정
	};
}
