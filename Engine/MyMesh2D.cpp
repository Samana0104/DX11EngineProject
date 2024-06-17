#include "pch.h"
#include "MyMesh2D.h"
using namespace MyProject;

MyMesh2D::MyMesh2D(MeshShape _meshShape)
	: mMeshShape(_meshShape)
{
}

void MyMesh2D::ReserveVertexSize(size_t _vertexCount)
{
	if (_vertexCount <= 2)
		_vertexCount = 3;

	mVertices.reserve(_vertexCount);
	mColors.reserve(_vertexCount);
	mUV.reserve(_vertexCount);
	mRenderVertices.reserve((_vertexCount-2)*3); // -> �ﰢ�� ���� 
	mIndices.reserve((_vertexCount-2)*3);
}

void MyMesh2D::AddVertexAndColorAndUV(const vec2 _vertex, const vec4 _color, const vec2 _uv)
{
	mVertices.emplace_back(_vertex);
	mColors.emplace_back(_color);
	mUV.emplace_back(_uv);
}

void MyMesh2D::AddVertexIndex(std::initializer_list<size_t> _index)
{
	for (auto idx : _index)
	{
		mIndices.emplace_back(idx);

		mRenderVertices.push_back({ MyTransformer2D::CartesianToNDC(mVertices[idx]), mColors[idx], mUV[idx] });
	}
}

void MyMesh2D::CreateMesh(const POINT_F _meshCom)
{
	_ASSERT(CreateVertexBuffer());
	mMeshCom = _meshCom;
}

void MyMesh2D::SetIAVertexBuffer()
{
	UINT StartSlot = 0;
	UINT NumBuffers = 1;
	UINT pStrides = sizeof(MyVertex2D); // 1���� ���� ũ��
	UINT pOffsets = 0; // ���ۿ� ���� �ε���
	mDevice.mContext->IASetVertexBuffers(StartSlot, NumBuffers, mVertexBuffer.GetAddressOf(), &pStrides, &pOffsets);
}

MyMesh2D& MyMesh2D::SetVertexColor(const size_t _colorIdx, const vec4 _color)
{
	try
	{
		mColors.at(_colorIdx) = _color;
		mRenderVertices[mIndices[_colorIdx]].color = mColors[_colorIdx];
	}
	catch (std::out_of_range e)
	{
		MessageBoxA(mWindow.GetWindowHandle(), e.what(), "Color indexing error[Mesh2D]", MB_OK);
	}

	return *this;
}

POINT_F MyMesh2D::GetMeshCom() const
{
	return mMeshCom;
}

bool MyMesh2D::CreateVertexBuffer()
{
	D3D11_BUFFER_DESC  bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(MyVertex2D) * mRenderVertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &mRenderVertices.at(0);

	HRESULT hr = mDevice.mD3dDevice->CreateBuffer(
		&bd,
		&sd,
		mVertexBuffer.GetAddressOf());

	return !FAILED(hr);
}

void MyMesh2D::UpdateRenderVertices(const mat3 _matrix)
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
			mColors[mIndices[i]],
			mUV[mIndices[i]]
		};
	}

	mDevice.mContext->UpdateSubresource(mVertexBuffer.Get(),0, NULL, &mRenderVertices.at(0), 0, 0);
}

void MyMesh2D::UpdateComponent()
{
}

void MyMesh2D::RenderComponent()
{
	SetIAVertexBuffer();
	mDevice.mContext->Draw(mRenderVertices.size(), 0);
}
