#pragma once
#include "pch.h"

namespace MyProject
{
	using namespace Microsoft::WRL;
	using namespace glm;

	using COLOR_F	= D2D1_COLOR_F;

	using RECT_L		= D2D1_RECT_L;
	using RECT_F		= D2D1_RECT_F;
	using RECT_U		= D2D1_RECT_U;
	using POINT_L		= D2D1_POINT_2L; 
	using POINT_F		= D2D1_POINT_2F;
	using POINT_U		= D2D1_POINT_2U;
	
	using stringV		= std::string_view;
	using wstringV		= std::wstring_view;

	using MESH_KEY		= std::wstring;
	using FONT_KEY		= std::wstring;
	using SCENE_KEY		= std::wstring;

	// 파일 이름으로 키 값을 받아오기에 이 4개는 wstring으로 선언 안하면 큰일 
	using SHADER_KEY	= std::wstring;
	using TEXTURE_KEY	= std::wstring;
	using SOUND_KEY		= std::wstring;
	using SPRITE_KEY	= std::wstring;

	static inline const float TOLERANCE = 1e-4f;
	class MyCoreAPI
	{
	public:
		static std::wstring to_mw(const stringV _src)
		{
			USES_CONVERSION;
			return std::wstring(A2W(_src.data()));
		}

		static std::string to_wm(const wstringV _src)
		{
			USES_CONVERSION;
			return std::string(W2A(_src.data()));
		}

		static std::pair<std::wstring, std::wstring> GetFileNameAndExt(const wstringV _filePath) 
		{
			wchar_t  szDrive[MAX_PATH] = { 0, };
			wchar_t  szDir[MAX_PATH] = { 0, };
			wchar_t  szFileName[MAX_PATH] = { 0, };
			wchar_t  szFileExt[MAX_PATH] = { 0, };
			_tsplitpath_s(_filePath.data(), szDrive, szDir, szFileName, szFileExt);
			//fileNameKey = szFileName;
			//fileNameKey += szFileExt;

			return std::make_pair(szFileName, szFileExt);
		}

	};
}