#pragma once

#include "pch.h"
#include "2D/Object2D.h"
#include "Texture/GeneralTexture.h"
#include "Font/Font.h"
#include "Observer.h"

namespace HBSoft
{
    class QuestGUI : public Object2D
    {
    private:
        std::shared_ptr<Texture> m_questTexture;
        std::shared_ptr<Font>    m_questFont;

    public:
    };
}  // namespace HBSoft
