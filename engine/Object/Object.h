#pragma once
#include "ResourceManger.h"
#include "Input.h"
#include "ObjectCode.h"

namespace HBSoft
{
    using OBJECT_ID = UINT;

    class ObjectManager;

    class Object
    {
    private:
        OBJECT_ID  mObjectID;  // ������Ʈ �Ŵ������� ������ ���̵�
        ObjectCode mObjectCode = ObjectCode::NOT;

    protected:
        TEXTURE_KEY mTextureKey = L"Default.jpg";
        MESH_KEY    mMeshKey    = L"DEFAULT_MESH";
        SHADER_KEY  mShaderKey  = L"PixelShader.hlsl";
        vec4        mColor      = {1.f, 1.f, 1.f, 1.f};
        Transform2D mTransform;


        MyResourceManager& mManager = MyResourceManager::GetInstance();
        Input&             mInput   = Input::GetInstance();

    private:

    protected:
        void SetObjectCode(const ObjectCode _objCode);

    public:
        Object() = default;

        void SetColor(const vec4 _color);
        void SetTextureKey(const TEXTURE_KEY _key);
        void SetMeshKey(const MESH_KEY _key);
        void SetShaderKey(const SHADER_KEY _key);
        void SetObjectID(const OBJECT_ID _objID);  // ������Ʈ �Ŵ��� ����� �ǵ�� ����

        // �̰Ŵ� ������Ʈ�� �־�� �� �Լ��ΰ�...
        void SetImageScale();

        const vec4&        GetColor() const;
        const MESH_KEY&    GetMeshKey() const;
        const TEXTURE_KEY& GetTextureKey() const;
        const SHADER_KEY&  GetShaderKey() const;
        const ObjectCode&  GetObjectCode() const;
        const OBJECT_ID&   GetObjectID() const;

        Transform2D& GetTransform();
        Transform2D* operator->();  // ��ġ ��ȯ ���ϰ� �Ϸ��� �����ε� ��

        virtual void Update(const float _deltaTime);
        virtual void Render();
    };
}  // namespace HBSoft
