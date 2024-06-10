#include "MyMesh2D.h"
using namespace MyProject;

MyMesh2D::MyMesh2D(MeshShape _meshShape, const std::wstring& _textureName)
	: mMeshShape(_meshShape)
{
	_ASSERT(CreateTexure(_textureName));
	//InitTransformer();
}

void MyMesh2D::ReserveVertexSize(size_t _size)
{
	if (_size <= 2)
		_size = 3;

	mVertices.reserve(_size);
	mColors.reserve(_size);
	mUV.reserve(_size);
	mRenderVertices.reserve((_size-2)*3); // -> 삼각형 갯수 
	mIndices.reserve((_size-2)*3);
}

void MyMesh2D::AddVertexAndColorAndUV(const vec2 _vertex, const vec4 _color, const vec2 _uv)
{
	mVertices.push_back(_vertex);
	mColors.push_back(_color);
	mUV.push_back(_uv);
}

void MyMesh2D::AddVertexIndex(std::initializer_list<size_t> _index)
{
	for (auto idx : _index)
	{
		mIndices.push_back(idx);
		mRenderVertices.push_back({ mVertices[idx], mColors[idx], mUV[idx] });
	}
}

bool MyMesh2D::CreateVertexBuffer()
{
	// 버퍼 할당 크기를 세팅한다.
	D3D11_BUFFER_DESC  bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(MyVertex2D) * mRenderVertices.size();
	// 연결에 용도가 뭐냐? 
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;


	// 할당된 버퍼에 
	// 시스템메모리가 ->GPU메모리로 체워지는 데이터
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &mRenderVertices.at(0);

	HRESULT hr = mDevice.mD3dDevice->CreateBuffer(
		&bd,
		&sd,
		mVertexBuffer.GetAddressOf());

	return !FAILED(hr);
}

void MyMesh2D::CalculateTransform()
{
	vec2 windowSize = mWindow.GetWindowSizeVec2();
	std::vector<vec2> copyVertices(mVertices);

	for (size_t i = 0; i < mVertices.size(); i++)
	{
		copyVertices[i] = mTransfomer.CalculateTRS(mVertices[i], windowSize);
	}

	for (size_t i = 0; i < mIndices.size(); i++)
	{
		mRenderVertices[i] = { 
			MyTransformer2D::PixelToNDC(copyVertices[mIndices[i]], windowSize),
			mColors[mIndices[i]],
			mUV[mIndices[i]]
		};
	}

	mDevice.mContext->UpdateSubresource(mVertexBuffer.Get(),0, NULL, &mRenderVertices.at(0), 0, 0);
}

bool MyMesh2D::CreateTexure(const std::wstring& _textureName)
{
	HRESULT hr =
		DirectX::CreateWICTextureFromFile(
			mDevice.mD3dDevice.Get(),
			_textureName.c_str(),
			mTexture.GetAddressOf(),//&m_pTexture
			mSRV.GetAddressOf());

	return !FAILED(hr);
}

void MyMesh2D::InitTransformer()
{
	mTransfomer.mLocation = { 0.f, 0.f };
	mTransfomer.mAngle = 0.f;
	mTransfomer.mScale = { 1.f, 1.f };
}

void MyMesh2D::Move(const vec2 _pos)
{
	SetPosition(mTransfomer.mLocation + _pos);
}

void MyMesh2D::Rotate(const float _angle)
{
	SetRotation(mTransfomer.mAngle + _angle);
}

void MyMesh2D::Scale(const vec2 _scale)
{
	SetScale(mTransfomer.mScale+ _scale);
}

void MyMesh2D::SetPosition(const vec2 _pos)
{
	mTransfomer.mLocation = _pos;
	CalculateTransform();
}

void MyMesh2D::SetRotation(const float _angle)
{
	if (_angle >= 360.f)
	{
		const int angleDivison = static_cast<int>(_angle / 360.f);
		mTransfomer.mAngle = _angle - static_cast<float>(angleDivison);
	}

	mTransfomer.mAngle = _angle;
	CalculateTransform();
}

void MyMesh2D::SetScale(const vec2 _scale)
{
	mTransfomer.mScale = _scale;
	CalculateTransform();
}

void MyMesh2D::InitComponent()
{
}

void MyMesh2D::UpdateComponent()
{
}

void MyMesh2D::RenderComponent()
{
	UINT StartSlot = 0;
	UINT NumBuffers = 1;
	UINT pStrides = sizeof(MyVertex2D); // 1개의 정점 크기
	UINT pOffsets = 0; // 버퍼에 시작 인덱스
	mDevice.mContext->IASetVertexBuffers(StartSlot, NumBuffers, mVertexBuffer.GetAddressOf(), &pStrides, &pOffsets);
	mDevice.mContext->PSSetShaderResources(0, 1, mSRV.GetAddressOf());
	mDevice.mContext->Draw(mRenderVertices.size(), 0);
}

void MyMesh2D::ReleaseComponent()
{
}
