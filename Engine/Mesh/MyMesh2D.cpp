#include "pch.h"
#include "MyMesh2D.h"
using namespace MyProject;

MyMesh2D::MyMesh2D(MeshShape _meshShape) : 
	mMeshShape(_meshShape)
{
}

void MyMesh2D::ReserveVertexSize(size_t _vertexCount)
{
	if (_vertexCount <= 2)
		_vertexCount = 3;

	mVertices.reserve(_vertexCount);
	mUV.reserve(_vertexCount);
	mUV.reserve(_vertexCount);
	mRenderVertices.reserve((_vertexCount-2)*3); // -> 삼각형 갯수 
	mIndices.reserve((_vertexCount-2)*3);
}

void MyMesh2D::AddVertexAndUV(const vec2 _vertex, const vec2 _uv)
{
	mVertices.emplace_back(_vertex);
	mUV.emplace_back(_uv);
}

void MyMesh2D::AddVertexIndex(std::initializer_list<size_t> _index)
{
	for (auto idx : _index)
	{
		mIndices.emplace_back(idx);
		mRenderVertices.push_back({ MyTransformer2D::CartesianToNDC(mVertices[idx]), {1.f,1.f,1.f,1.f}, mUV[idx]});
	}

	mTempUV = mUV;
}

void MyMesh2D::CreateMesh(const POINT_F _meshCom)
{
#ifdef _DEBUG
	_ASSERT(CreateVertexBuffer());
#else
	CreateVertexBuffer();
#endif
	mMeshCom = _meshCom;
}

void MyMesh2D::SetUVVertex(const size_t _uvVertex, const vec2 _uv)
{
	try
	{
		mTempUV.at(_uvVertex) = _uv;
	}
	catch (std::out_of_range e)
	{
		MessageBoxA(NULL, e.what(), "UV indexing error[Mesh2D]", MB_OK);
	}
}

POINT_F MyMesh2D::GetMeshCom() const
{
	return mMeshCom;
}

bool MyMesh2D::CreateVertexBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC		bd = { };
	D3D11_SUBRESOURCE_DATA	sd = { };

	bd.ByteWidth = sizeof(MyVertex2D) * static_cast<UINT>(mRenderVertices.size());
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	sd.pSysMem = mRenderVertices.data();

	hr = mDevice.mD3dDevice->CreateBuffer(&bd, &sd, mVertexBuffer.GetAddressOf());

	return SUCCEEDED(hr);
}

void MyMesh2D::SetIAVertexBuffer()
{
	UINT StartSlot = 0;
	UINT NumBuffers = 1;
	UINT pStrides = sizeof(MyVertex2D); // 1개의 정점 크기
	UINT pOffsets = 0; // 버퍼에 시작 인덱스

	mDevice.mContext->IASetVertexBuffers(StartSlot, NumBuffers, mVertexBuffer.GetAddressOf(), &pStrides, &pOffsets);
}

void MyMesh2D::UpdateRenderVertices(const mat3& _matrix, const vec4& _color)
{
	vec3 dim2ToDim3;
	std::vector<vec2> copyVertices(mVertices.size());

	for (size_t i = 0; i < mVertices.size(); i++)
	{
		dim2ToDim3 = vec3({ mVertices[i], 1.f });
		copyVertices[i] = _matrix * dim2ToDim3;
	}

	for (size_t i = 0; i < mIndices.size(); i++)
	{
		mRenderVertices[i] = { 
			MyTransformer2D::CartesianToNDC(copyVertices[mIndices[i]]),
			_color, 
			mTempUV[mIndices[i]] 
		};
	}

	mDevice.mContext->UpdateSubresource(mVertexBuffer.Get(),0, NULL, mRenderVertices.data(), 0, 0);
}

void MyMesh2D::Draw(const mat3& _matrix, const vec4 _color)
{
	UpdateRenderVertices(_matrix, _color);
	SetIAVertexBuffer();
	mDevice.mContext->Draw(static_cast<UINT>(mRenderVertices.size()), 0);
	PostRender();
}

void MyMesh2D::PostRender()
{
	mTempUV = mUV; // 원본 UV 복귀
}
