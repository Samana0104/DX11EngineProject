#include "pch.h"
#include "Tile.h"
using namespace HBSoft;

Tile::Tile()
{
	SetObjectCode(ObjectCode::TILE);
}

void Tile::SetUVRect(const RECT_F _uv)
{
	mUV = _uv;
}

void Tile::SetRow(const int _row)
{
	mRow = _row;
}

void Tile::SetColumn(const int _column)
{
	mColumn = _column;
}

int Tile::GetRow() const
{
	return mRow;
}

int Tile::GetColumn() const
{
	return mColumn;
}

const RECT_F& Tile::GetUVRect() const
{
	return mUV;
}

void Tile::OnCollision(RECT_F& _self, RECT_F& _target, Actor& _targetObj)
{
	// 고정형 블럭
	return;
}

void Tile::Update(const float _deltaTime)
{
	
}

void Tile::Render()
{
	vec2 imageSize = m_manager.m_texture[m_textureKey]->GetTextureSizeVec2();
	m_manager.m_shader[m_shaderKey]->SetUpConfiguration();
	m_manager.m_texture[m_textureKey]->Render();
	m_manager.m_mesh[m_meshKey]->SetUVVertexAsRect(mUV, imageSize);
	m_manager.m_mesh[m_meshKey]->Draw(m_transform.GetModelMat(), m_color);
}
