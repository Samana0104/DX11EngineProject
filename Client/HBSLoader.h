#pragma once

#include "3D/Static3DObj.h"

namespace HBSoft
{
    class HBSLoader
    {
    public:
        std::vector<Static3DObj> objects;  // Static3DObj ��ü�� ����

        // �������� .hbs ���� �о�� ��ü ���� �� �ʱ�ȭ
        void LoadFromFolder(const std::string& folderPath);

        // Ư�� �̸����� ��ü �˻�
        Static3DObj* FindByName(const std::wstring& name);
    };
}  // namespace HBSoft