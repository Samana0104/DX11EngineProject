/*
author : ���Ѻ�
description : 3D������ �׷��� ������Ʈ�� �����ϱ� ���� ��� ����

version: 1.0.7
date: 2024-11-12
*/

#pragma once
#include "Core.h"
#include "Renderable.h"
#include "Transform3D.h"
#include "Shader/ConstantBuffers.h"

namespace HBSoft
{
    class Camera;

    class Object3D : public Renderable
    {
    protected:
        Camera* m_camera;

        std::shared_ptr<Mesh>    m_mesh;
        std::shared_ptr<Texture> m_texture;
        std::shared_ptr<Shader>  m_vsShader;
        std::shared_ptr<Shader>  m_psShader;

        Transform3D m_transform;
        DefaultCB0  m_cb0;

    public:
        Object3D();
        virtual ~Object3D() = default;

        void SetTextureKey(const TEXTURE_KEY key);
        void SetMeshKey(const MESH_KEY key);
        void SetVSShaderKey(const SHADER_KEY key);
        void SetPSShaderKey(const SHADER_KEY key);
        void SetCamera(Camera* camera);

        virtual void Init() override;
        virtual void Release() override;
        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
    };
}  // namespace HBSoft