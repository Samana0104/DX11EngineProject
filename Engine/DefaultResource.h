#pragma once
#include "MyWriterFont.h"
#include "MyMesh2D.h"

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
		{ "DEBUG_FONT", {L"¸¼Àº °íµñ", L"ko-kr", 25.f, DWRITE_FONT_WEIGHT_THIN, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL}}
	};

/*
	enum class MeshShape
	{
		CUSTOM = 0,
		BOX = 1,
		SPEHERE = 2
	};
*/
	inline static const std::map<MESH_KEY, std::pair<MeshShape, POINT_F>> gDefaultMeshes = {
		{ "BOX2D_MESH", { MeshShape::BOX2D, {10.f, 10.f}}}
	};


	inline static const std::map<TEXTURE_KEY, std::wstring> gDeafultTextures = {
		{ "KGCA_01", L"KGCA01"}
	};
}
