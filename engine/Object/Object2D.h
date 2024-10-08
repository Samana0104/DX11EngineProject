#pragma once
#include "ResourceManger.h"
#include "Input.h"
#include "ObjectCode.h"

namespace HBSoft
{
    using OBJECT_ID = UINT;

    class ObjectManager;

    class Object2D
    {
    private:
        OBJECT_ID  m_objectID;  // 오브젝트 매니저에서 생성한 아이디
        ObjectCode m_objectCode = ObjectCode::NOT;

    protected:
        TEXTURE_KEY m_textureKey = L"Default.jpg";
        MESH_KEY    m_meshKey    = L"DEFAULT_MESH";
        SHADER_KEY  m_shaderKey  = L"PixelShader.hlsl";
        vec4        m_color      = {1.f, 1.f, 1.f, 1.f};
        Transform2D m_transform;


        ResourceManager& m_manager = ResourceManager::GetInstance();
        Input&           m_input   = Input::GetInstance();

    private:

    protected:
        void SetObjectCode(const ObjectCode _objCode);

    public:
        Object2D() = default;

        void SetColor(const vec4 _color);
        void SetTextureKey(const TEXTURE_KEY _key);
        void SetMeshKey(const MESH_KEY _key);
        void SetShaderKey(const SHADER_KEY _key);
        void SetObjectID(const OBJECT_ID _objID);  // 오브젝트 매니저 말고는 건들기 금지

        // 이거는 오브젝트에 있어야 할 함수인가...
        void SetImageScale();

        const vec4&        GetColor() const;
        const MESH_KEY&    GetMeshKey() const;
        const TEXTURE_KEY& GetTextureKey() const;
        const SHADER_KEY&  GetShaderKey() const;
        const ObjectCode&  GetObjectCode() const;
        const OBJECT_ID&   GetObjectID() const;

        Transform2D& GetTransform();
        Transform2D* operator->();  // 위치 변환 편하게 하려고 오버로딩 함

        virtual void Update(const float deltaTime);
        virtual void Render();
    };
}  // namespace HBSoft
