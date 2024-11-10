/*
author : ���Ѻ�
description : ī�޶� �����ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Object3D.h"

namespace HBSoft
{
    class Camera : public Object3D
    {
    private:
        float m_fov;
        float m_projNear;
        float m_projFar; // near�� �� ������ �ɷ��ִ°ž�

        // ���� ī�޶� ������ �� �ִ� ��ģ ��� ������?
        // ���� �ܾƿ� ���� ��������� ������ �������� ���ÿ�

    public:
        Camera(float fov, float projNear, float projFar);
        const mat4 GetViewMat() const;
        const mat4 GetProjMat() const;

        void ZoomIn(const float scale);
        void ZoomOut(const float scale);

        void LookAtObject(Object3D& obj);
    };
}  // namespace HBSoft
