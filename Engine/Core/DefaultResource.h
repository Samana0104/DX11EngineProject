#pragma once
#include "MyWriterFont.h"
#include "MyMesh2D.h"
#include "MyShader.h"

namespace MyProject
{
/*
	struct FontDesc
	{
		std::wstring mFontName;
		std::wstring mFontLocalName;
		FLOAT		 mFontSize;
		
		DWRITE_FONT_WEIGHT	mFontWeight;
		DWRITE_FONT_STYLE	mFontStyle;
		DWRITE_FONT_STRETCH mFontStretch;
	};
*/

	inline static const std::map<FONT_KEY, FontDesc> gDefaultFonts = {
		{ L"DEBUG_FONT", {L"¸¼Àº °íµñ", L"ko-kr", 20.f, DWRITE_FONT_WEIGHT_THIN, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL}}
	};

/*
	enum class MeshShape
	{
		CUSTOM = 0,
		BOX = 1,
		SPEHERE = 2
	};
*/
	inline static const std::map<MESH_KEY, MeshShape> gDefaultMeshes = {
		{ L"BOX2D_MESH", { MeshShape::BOX2D }}
	};


	using TexturePath = std::wstring;
	inline static const std::vector<TexturePath> gDefaultTextures = {
		{ L"../data/KGCA1.png"}
	};

/*
	struct ShaderDesc
	{
		ShaderType		mShaderType;
		std::wstring	mShaderPath;
		std::string		mShaderEntry;
	};
*/

	inline static const std::vector<ShaderDesc> gDefaultShaders = {
		{ ShaderType::VERTEX, L"../data/shaders/VertexShader.hlsl", "VSMain"},
		{ ShaderType::PIXEL, L"../data/shaders/PixelShader.hlsl", "PSMain"}
	};
}
